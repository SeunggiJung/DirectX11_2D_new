#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
    // 컴파일러 오류 메세지를 저장할 Blob
    ID3DBlob* error = nullptr;
        
    HRESULT hr = D3DCompileFromFile
    (
        // 컴파일할 쉐이더 파일 경로
        path.c_str(),
        // 쉐이더 파일의 헤더 파일을 나타내는 포인터
        nullptr,
        // Include 인터페이스를 구현한 클래스를 나타내는 포인터
        nullptr,
        // 컴파일할 쉐이더 파일의 진입점
        entryName.c_str(),
        // 컴파일할 쉐이더 파일의 표시자 이름
        profile.c_str(),
        // 엄격한 컴파일 옵션 // 경고 레벨을 1로 설정
        D3DCOMPILE_ENABLE_STRICTNESS,
        // 디버그 정보를 저장할 포인터
        0,
        // 컴파일 정보를 저장할 Blob
        blob,
        // 컴파일 오류 메세지를 저장할 Blob
        &error
    );
    CheckShaderError(hr, error);
    SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
    // HRESULT 가 실패했을 경우 // 폭파는 안시킴
    if (FAILED(hr))
    {
        // 에러 메세지가 존재할 경우
        if (error)
        {
            string str = (const char*)error->GetBufferPointer();
            MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
        }
        // 프로그램 폭파
        CHECK(false);
    }
}
