#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // Vertices
    {
        // vertices 크기 재할당
        vertices.assign(4, VertexTexture());

        // 좌 하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].uv = Vector2(0, 1);

        // 우 상단
        vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
        vertices[1].uv = Vector2(1, 0);

        // 우 하단
        vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
        vertices[2].uv = Vector2(1, 1);

        // 좌 상단
        vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
        vertices[3].uv = Vector2(0, 0);
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
        vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();

        // 쉐이더 경로 + 파일 이름 , 실행할 쉐이더 함수 이름
        ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();

        il->Create(VertexTexture::descs, VertexTexture::count,
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

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
    : position(position), size(size), rotation(rotation)
{
    // Vertices
    {
        // vertices 크기 재할당
        vertices.assign(4, VertexTexture());

        // 좌 하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].uv = Vector2(0, 1);

        // 우 상단
        vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
        vertices[1].uv = Vector2(1, 0);

        // 우 하단
        vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
        vertices[2].uv = Vector2(1, 1);

        // 좌 상단
        vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
        vertices[3].uv = Vector2(0, 0);
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
        vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();

        // 쉐이더 경로 + 파일 이름 , 실행할 쉐이더 함수 이름
        ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();

        il->Create(VertexTexture::descs, VertexTexture::count,
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

    // Rasterizer State
    {
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

        // CullMode : 그리지 않을 부분 설정 // 자를 부분 설정
        // Cull_BACK == 뒷면 자르겠다.
        desc.CullMode = D3D11_CULL_BACK;

        // FillMode : 채우는 방식 설정
        // FILL_SOLID = 꽉 채우겠다.
        // FILL_WIREFRAME = 선만 그리겠다. // 2D에선 거의 안씀
        desc.FillMode = D3D11_FILL_SOLID;

        // 반시계 방향 설정 (false = 시계 방향 , true = 반시계 방향)
        desc.FrontCounterClockwise = false;

        HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
        CHECK(hr);
    }

    // SRV 추출 // 그림 데이터 추출
    {
        HRESULT hr = D3DX11CreateShaderResourceViewFromFile
        (
            DEVICE,
            path.c_str(),
            nullptr,
            nullptr,
            &srv,
            nullptr
        );
        CHECK(hr);
    }
}

TextureRect::~TextureRect()
{
    SAFE_RELEASE(srv);
    SAFE_RELEASE(rs);

    SAFE_DELETE(edge);
    SAFE_DELETE(collision);

    SAFE_DELETE(wb);

    SAFE_DELETE(il);

    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void TextureRect::Update()
{
    UpdateWorld();  // 월드상에 이 객체를 배치시킨다.
}

void TextureRect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    // 삼각형을 어떻게 그릴지 정할 함수
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    DC->PSSetShaderResources(0, 1, &srv);
    DC->RSSetState(rs);

    // 그림을 그리는 함수
    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
}

string TextureRect::MakeLabel(string label)
{
    return string();
}

void TextureRect::UpdateWorld()
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

void TextureRect::Move()
{
}

void TextureRect::Jump()
{
}

void TextureRect::SetShader(wstring shaderPath)
{
    vs->Clear();
    ps->Clear();

    vs->Create(shaderPath, "VS");
    ps->Create(shaderPath, "PS");
}

void TextureRect::SetImage(wstring imagePath)
{
    SAFE_RELEASE(srv);

    HRESULT hr = D3DX11CreateShaderResourceViewFromFile
    (
        DEVICE,
        imagePath.c_str(),
        nullptr,
        nullptr,
        &srv,
        nullptr
    );
    CHECK(hr);
}
