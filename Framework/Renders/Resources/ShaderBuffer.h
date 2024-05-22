#pragma once
#include "Framework.h"

// CPU가 GPU에게 정점이 아닌 데이터를 건내주기 위한 용도로 사용
class ShaderBuffer
{
public:
    void SetVSBuffer(UINT slot)
    {
        MapData();
        DC->VSSetConstantBuffers(slot, 1, &buffer);
    }

    void SetPSBuffer(UINT slot)
    {
        MapData();
        DC->PSSetConstantBuffers(slot, 1, &buffer);
    }
protected:
    ShaderBuffer(void* data, UINT dataSize)
        : data(data), dataSize(dataSize)
    {
        // 버퍼의 사용 용도 // DYNAMIC = CPU에서 수정 가능
        desc.Usage = D3D11_USAGE_DYNAMIC;
        // 버퍼의 크기
        desc.ByteWidth = dataSize;
        // 사용 목적 // CONSTANT_BUFFER = 상수 버퍼로 사용할 것이다.
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        // CPU 접근 방식
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
        CHECK(hr);
    }

private: // 함수

    // Map은 DirectX에서 런타임중에 메모리가 가지고 있는 데이터를 수정하는
    // 기능을 말한다.
    // Map을 사용하는 이유는 런타임중에 중요한 데이터가 손상없이 수정 가능하도록
    // 하기 위해서 인데, 그렇기 때문에 굳이 중요한 데이터가 아니라면
    // Map을 사용하진 않는다.
    // Map은 반드시 D3D11_MAPPED_SUBRESOURCE를 이용해 메모리를 수정하는데
    // D3D11_MAPPED_SUBRESOURCE 는 거의 모든 데이터를 저장하고 옮길수 있는
    // 구조체 이다.
    void MapData()
    {
        // 데이터 맵핑을 도와줄 구조체
        D3D11_MAPPED_SUBRESOURCE subRe;
        // 데이터 맵핑
        HRESULT hr = DC->Map
        (
            buffer,                 // 매핑할 대상
            0,                      // 매핑 시작 위치 (0 = 처음부터)
            D3D11_MAP_WRITE_DISCARD,// 매핑 방법 // WRITE_DISCARD는 지웠다 다시
            0,                      // 추가로 맵핑할 대상 (0 = 없음)
            &subRe                  // 매핑 데이터를 보관할 구조체
        );
        CHECK(hr);
        // 메모리 복사 // subRe가 가지고있는 데이터를 data에게 dataSize만큼
        memcpy(subRe.pData, data, dataSize);
        DC->Unmap(buffer, 0);
    }
private: // 변수
    D3D11_BUFFER_DESC desc = { 0 };
    ID3D11Buffer* buffer = nullptr;

    void* data = nullptr;
    UINT dataSize = 0;
};