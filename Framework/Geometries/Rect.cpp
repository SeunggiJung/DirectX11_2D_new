#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // Vertices
    {
        // vertices 크기 재할당
        vertices.assign(4, VertexColor());

        // 좌 하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].color = color;

        // 우 상단
        vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
        vertices[1].color = color;

        // 우 하단
        vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
        vertices[2].color = color;

        // 좌 상단
        vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
        vertices[3].color = color;
    }

    // VertexBuffer
    {
        vb = new VertexBuffer();
        vb->Create(vertices, D3D11_USAGE_DYNAMIC);
    }

    // Indices // IndexBuffer
    {
        indices = { 0,1,2,0,3,1 };

        ib = new IndexBuffer();
        ib->Create(indices, D3D11_USAGE_IMMUTABLE);
    }

    // VertexShader
    {
        vs = new VertexShader();

        // 쉐이더 경로 + 파일 이름 , 실행할 쉐이더 함수 이름
        vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();

        // 쉐이더 경로 + 파일 이름 , 실행할 쉐이더 함수 이름
        ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();

        il->Create(VertexColor::descs, VertexColor::count,
            vs->GetBlob());
    }

    // WorldBuffer
    {
        wb = new WorldBuffer();
    }

    // Collision
    {
        collision = new BoundingBox();
        edge = new RectEdge();

        for (int i = 0; i < 4; i++)
            verticesPosition[i] = vertices[i].position;
    }
}

Rect::~Rect()
{
    SAFE_DELETE(edge);
    SAFE_DELETE(collision);

    SAFE_DELETE(wb);

    SAFE_DELETE(il);

    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void Rect::Update()
{
    // Update함수는 주료 이 객체가 매 프레임마다 할 행동을 적어둔다.
    // 여기에 적은 기능은 이 객체가 반드시 실행할 기능이란 뜻이다.

    UpdateWorld();  // 월드상에 이 객체를 배치시킨다.

}

void Rect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    // 삼각형을 어떻게 그릴지 정할 함수
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    // 그림을 그리는 함수
    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::GUI()
{
    // ImGui를 이용해 개발환경에 사용될 UI를 만드는 부분

    // ImGui를 만들기 위해 가장 먼저 실행되야하는 코드
    ImGui::Begin("Rect", &bOpen);
    {
        ImGui::Text(MakeLabel("Rect").c_str());
        ImGui::SliderFloat2(MakeLabel("Pos").c_str(), position,
            0, WinMaxWidth);
        ImGui::SliderFloat2(MakeLabel("Size").c_str(), size,
            0, WinMaxWidth);
        ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation,
            0, 360);

        // Gui기능에 if를 넣을경우 해당 Gui가 조작됐을때 이후의 함수를
        // 실행하는것이 가능하다.
        if (ImGui::ColorPicker3(MakeLabel("Color").c_str(), color))
            UpdateColor();
    }
    // ImGui에게 Gui코드가 끝났다는것을 알려줄 함수
    ImGui::End(); // 이거 안적으면 터짐
}

void Rect::UpdateColor()
{
    D3D11_MAPPED_SUBRESOURCE subRe;
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
    {
        for (VertexColor& v : vertices)
        {
            v.color = this->color;
        }

        memcpy(subRe.pData, vertices.data(),
            vb->GetCount() * vb->GetStride());
    }
    DC->Unmap(vb->GetResource(), 0);
}

void Rect::SetColor(Color color)
{
    this->color = color;
    UpdateColor();
}

string Rect::MakeLabel(string label)
{
    string Label = label + "##" + to_string((UINT)this);
    return Label;
}

void Rect::UpdateWorld()
{
    // 로컬 크기를 월드상 크기로 전환
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    // 로컬 회전값을 월드상 회전값으로 전환
    D3DXMatrixRotationZ(&R, rotation);
    // 로컬 위치를 월드상 위치로 전환
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    // SRT 순서가 아니면 정상적으로 출력이 안됨
    world = S * R * T;
    wb->SetWorld(world);

    collision->UpdateData(world, verticesPosition);
}

void Rect::Move()
{
    float mSpd = 100.0f;

    if (bJump) Jump();

    if (Keyboard::Get()->Press('W'))
    {
        // rect가 위쪽으로 이동되게
        position.y += mSpd * Time::Delta();
        if (Keyboard::Get()->Press('S') && moveD == false)
        {
            position.y -= (mSpd * 2) * Time::Delta();
        }
    }
    else if (Keyboard::Get()->Press('S'))
    {
        // rect가 아래쪽으로 이동되게
        position.y -= mSpd * Time::Delta();
        moveD = true;
    }

    if (Keyboard::Get()->Up('S')) moveD = false;

    if (Keyboard::Get()->Press('A'))
    {
        // rect가 왼쪽으로 이동되게s
        position.x -= mSpd * Time::Delta();
        if (Keyboard::Get()->Press('D') && !moveR)
        {
            position.x += (mSpd * 2) * Time::Delta();
        }
    }
    else if (Keyboard::Get()->Press('D'))
    {
        // rect가 오른쪽으로 이동되게
        position.x += mSpd * Time::Delta();
        moveR = true;
    }

    if (Keyboard::Get()->Up('D')) moveR = false;

    if (Keyboard::Get()->Down(VK_SPACE) && !bJump)
    {
        bJump = true;
        jumpStartY = position.y;
    }
}

void Rect::Jump()
{
    /*
    모든 점프는 기본적으로 bool값을 이용해 특정 키를 눌렀을 경우
    해당 bool값을 true로 바꾸며 해당 bool값이 true일때 점프 이동을
    실행하는 것을 기본으로 둔다.

    만약, 점프를 누르고있는동안 점프의 높이가 서서히 증가나는 방식의 점프를
    구현하고 싶다면 bool값을 사용하지 않아도 된다.

    점프를 만드는법 1. 점프 시간 이용하기
    // 일정한 시간의 점프 구현 가능
    1. 스페이스바를 눌렀을경우 경우 일정 시간 동안 위로 가게한다.
    (Time::Delta()를 계속 더하다가 1이 되면 1초가 지난것)
    2. 일정 시간이 지나면 다시 원래있던 곳으로 천천히 내려온다.
    (내려올때도 올라간 시간만큼 내려오면 된다.)

    점프를 만드는법 2. 중력 이용하기
    // 감속가속이 쉬운 점프 구현 가능
    1. 스페이스바를 눌렀을경우 특정 값만큼 이동을 시작하기
    2. 특정 값은 처음엔 +였다가 시간이 지날수록 지속적으로 값을 감소함
    3. 특정 값이 계속 감소하다 -까지 도달할경우 하락하기 시작

    점프 만드는법 3. 특정 거리까지 이동하기
    // 목적지 도달이 쉬운 점프 구현 가능
    1. 스페이스바를 눌렀을경우 현재 자신의 높이값에서 특정 높이 까지 이동
    2. 해당 높이 도달시 다시 처음 높이값으로 이동
    */

    // 상승중
    if (bFall == false)
    {
        // 현재 점프한 시간이 최대 시간을 넘었다면
        if (curJumpT >= maxJumpT) // 하강 준비
        {
            curJumpT = 0.0f;
            bFall = true;
        }
        else // 아직 상승중
        {
            curJumpSpd -= 10.0f * Time::Delta();

            position.y += curJumpSpd;

            // Time::Delta는 프레임 시간을 알려주기 때문에
            // 계속 더해지다 1이 된 순간은 1초가 지난 순간이다.
            curJumpT += Time::Delta();
        }
    }
    else // 하강 중
    {
        // 현재 점프한 시간이 최대 시간을 넘었다면
        if (curJumpT >= maxJumpT) // 점프 끝
        {
            curJumpT = 0.0f;

            curJumpSpd = maxJumpSpd;

            bJump = false;
            bFall = false;

            position.y = jumpStartY;
            jumpStartY = 0;
        }
        else // 아직 하강중
        {
            curJumpSpd += 10.0f * Time::Delta();

            position.y -= curJumpSpd;

            curJumpT += Time::Delta();
        }
    }
}
