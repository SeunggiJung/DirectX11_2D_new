#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
    SAFE_RELEASE(il);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count, ID3DBlob* blob)
{
    // 매게변수중 하나라도 없을경우
    if (!descs || !count || !blob)
        CHECK(false); // 프로그램 강제 종료

    HRESULT hr = DEVICE->CreateInputLayout
    (
        descs,                      // 설계도
        count,                      // 설계도 개수
        blob->GetBufferPointer(),   // VertexBuffer의 위치
        blob->GetBufferSize(),      // VertexBuffer의 크기
        &il
    );
    CHECK(hr);
}

void InputLayout::SetIA()
{
    DC->IASetInputLayout(il);
}
