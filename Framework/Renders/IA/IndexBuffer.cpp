#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
    SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<UINT>& indices, const D3D11_USAGE& usage)
{
    // 정점의 크기
    stride = sizeof(UINT);
    // 정점의 개수
    count = indices.size();

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

    // desc 설정
    {
        desc.Usage = usage;
        // 사용 목적
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
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
        D3D11_SUBRESOURCE_DATA subData;
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

        // subData에 vertices 벡터 좌표를 건내줌
        subData.pSysMem = indices.data();

        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,
            &buffer);
        CHECK(hr);
    }
}

void IndexBuffer::SetIA()
{
    // 인풋 어셈블러에 버퍼를 넣어주는 함수
    DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
