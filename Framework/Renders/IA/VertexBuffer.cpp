#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    // SAFE_RELEASE는 ID3D로 시작하는 인터페이스를 해제하는데
    // 사용되며, 해당 인터페이스들은 프로그래머가 만드는 것이 아닌
    // DirectX가 만들어 놓은 기능을 빌려 오는 방식이기 때문에
    // delete가 아니라 release를 사용하는 것이다.
    SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
    // 인풋 어셈블러에 버퍼를 넣어주는 함수
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
