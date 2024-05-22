#include "Framework.h"
#include "VertexType.h"

/*
D3D11_INPUT_ELEMENT_DESC

SemanticName        : 정점 데이터의 의미를 나타내는 문구

SemanticIndex       : 위 이름이 중복되는 경우 구분하기 위한 인덱스 값 
// 번호

Format              : 데이터의 형식을 나타냄 
// 어떤 자료형 몇 비트 가지고 있다.

InputSlot           : 입력 슬롯의 번호 

AlignedByteOffset   : 정점 데이터의 바이트 단위 오프셋
// 0 = 자동 계산 
// D3D11_APPEND_ALIGNED_ELEMENT = 기본값 지정 // 앞선 데이터와 동일하게

InputSlotClass      : 입력 슬롯의 형식
// 사용되는 데이터 형식 지정

InstanceDataStepRate: 인스턴스마다 데이터를 읽어들이는데 사용할 시간
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
    0, D3D11_INPUT_PER_VERTEX_DATA, 0},

    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
    D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[]
{
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
    0, D3D11_INPUT_PER_VERTEX_DATA, 0},

    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
    D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};