#include "Framework.h"
#include "AlphaTexture.h"

AlphaTexture::AlphaTexture(Vector3 position, Vector3 size, float rotation, wstring path)
    : TextureRect(position,size,rotation,path)
{
    ab = new AlphaBuffer();
    SetShader(ShaderPath + L"VertexAlpha.hlsl");
}

AlphaTexture::~AlphaTexture()
{
    SAFE_DELETE(ab);
}

void AlphaTexture::Update()
{
    __super::Update();
}

void AlphaTexture::Render()
{
    ab->SetPSBuffer(0);
    __super::Render();
}

void AlphaTexture::GUI()
{
    ImGui::Begin("Alpha");
    {
        ImGui::SliderFloat("AlphaCount", ab->GetAlphaPtr(), 0, 1);
    }
    ImGui::End();
}
