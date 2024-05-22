#pragma once

// DirectX에서 쉐이더를 만들고 관리하는 인터페이스
class IShader
{
public:
    // 실질적인 쉐이더 생성 명령 // 생성자
    virtual void Create(const wstring path, const string entryName) = 0;
    // 객체 초기화 // 소멸자
    virtual void Clear() = 0;
    // 쉐이더 세팅
    virtual void SetShader() = 0;

protected:
    // 쉐이더 생성
    void CompileShader(wstring path, string entryName, string profile,
        ID3DBlob** blob);

    wstring path = L"";     // 쉐이더 파일 경로
    string entryName = "";  // 진입점

private:
    // 쉐이더 에러 체크
    void CheckShaderError(HRESULT hr, ID3DBlob* error);
};