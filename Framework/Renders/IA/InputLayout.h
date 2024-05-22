#pragma once

// CPU가 GPU에게 정점의 데이터를 건내줄때
// 해당 정점의 세부적인 데이터를 건내줄 클래스
class InputLayout
{
public:
    ~InputLayout();

    void Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count,
        ID3DBlob* blob);

    void SetIA();
private:
    ID3D11InputLayout* il = nullptr;
};