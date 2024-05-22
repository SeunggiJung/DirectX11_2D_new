#pragma once

class VertexBuffer
{
public:
    ~VertexBuffer();

    // template<typename T>는 이 다음에 오는 함수에 들어가는 T를
    // 어떤게 들어가도 사용할수 있도록 해주는 기능이다.

    // Create를 템플릿으로 만드는 이유는 나중에 만들 사각형에 따라
    // 정점의 데이터를 다르게 건내줘야 하기 때문이다.
    template<typename T>
    void Create(const vector<T>& vertices,
        const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

    ID3D11Buffer* GetResource() { return buffer; }

    UINT GetStride() { return stride; }
    UINT GetOffset() { return offset; }
    UINT GetCount() { return count; }

    void SetIA();
private:
    ID3D11Buffer* buffer = nullptr;

    UINT stride = 0; // 버퍼에서 한 정점의 크기
    UINT offset = 0; // 버퍼에서 읽을 시작 위치
    UINT count = 0; // 버퍼에서 읽을 정점의 개수
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
    // 정점의 크기
    stride = sizeof(T);
    // 정점의 개수
    count = vertices.size();

    // DESC는 프로그래머가 원하는 목적에 맞게 사용할
    // DirectX 데이터들을 만들기 위한 일종의 설계도 & 요청서이다.
    D3D11_BUFFER_DESC desc;
    // desc는 구조체 이기 때문에, 내부의 데이터들을 초기화 하기
    // 위해서는 ZeroMemory를 사용해야 한다.
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

    /*
    Buffer는 CPU가 GPU에게 데이터를 전달해 주기 위해 사용되는
    변수이다.
    Buffer는 기본적으로 프로그래머가 만드는 것이 아닌 설계도를
    작성해 DirectX에게 만들어달라 요청하는 변수이며,
    이러한 Buffer는 CPU에서 GPU로 데이터를 전달하는 용도로만
    사용된다.
    이때 Buffer가 전달되고 난후 해당 Buffer의 전달 결과나
    사용된 버퍼의 위치등의 데이터가 보관되는 Blob이란 데이터도
    생겨난다.
    */

    // desc 설정
    {
        // Usage는 cpu와 gpu가 해당 데이터를 어떻게 사용할건지
        // 지정하는 사용 용도이다.
        desc.Usage = usage;

        // 사용 목적
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        // 버퍼 크기
        desc.ByteWidth = stride * count;

        // cpu설정
        // 기본적으로 cpu가 gpu로 건내주는 데이터이다 보니
        // gpu는 모든 데이터에 접근하는것은 가능하다.
        switch (usage)
        {
        case D3D11_USAGE_DEFAULT:
        {
            // CPU가 접근할 수 없고
            // GPU가 수정할 수 있는
        }
        case D3D11_USAGE_IMMUTABLE:
        {
            // CPU가 접근할 수 없고
            // GPU가 수정할 수 없는
        }
        break;
        case D3D11_USAGE_DYNAMIC:
        {
            // CPU가 접근하고 수정할수 있는
            // GPU가 수정할 수 없는
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            break;
        }
        case D3D11_USAGE_STAGING:
        {
            // CPU가 접근하고 수정할수 있는
            // GPU가 수정할 수 있는
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE |
                D3D11_CPU_ACCESS_READ;
            break;
        }
        }
    }

    // 버퍼 생성
    {
        // D3D11_SUBRESOURCE_DATA는 다양한 데이터를 임시로
        // 보관하는것이 가능한 구조체 이다.
        // D3D11_SUBRESOURCE_DATA를 만들었다는 것은 주로
        // 메모리상에 접근할일이 있다는 뜻이다.
        // D3D11_SUBRESOURCE_DATA또한 초기화를 ZeroMemory를
        // 이용한다.
        D3D11_SUBRESOURCE_DATA subData;
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

        // subData에 vertices 벡터 좌표를 건내줌
        subData.pSysMem = vertices.data();

        // HRESULT는 해당 작업이 정상적으로 진행 됐는지는 판단하는
        // 자료형이며, 작업이 끝난 변수를 CHECK에 집어넣어
        // 만약, 작업이 정상적으로 끝나지 않았다면
        // 프로그램을 폭파시키며 해당 CHECK의 위치를 알려준다.
        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,
            &buffer);
        CHECK(hr);
    }
}
