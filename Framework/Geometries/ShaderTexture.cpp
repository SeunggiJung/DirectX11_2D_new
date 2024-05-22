#include "Framework.h"
#include "ShaderTexture.h"

ShaderTexture::ShaderTexture(Vector3 position, Vector3 size, float rotation, wstring path)
    : TextureRect(position, size, rotation, path)
{
    sb = new STBuffer();
    sb->SetTextureSize(Vector2(size.x, size.y));
    SetShader(ShaderPath + L"VertexShader.hlsl");
}

ShaderTexture::~ShaderTexture()
{
    SAFE_DELETE(sb);
}

void ShaderTexture::Update()
{
    __super::Update();
}

void ShaderTexture::Render()
{
    sb->SetPSBuffer(0);
    __super::Render();
}

void ShaderTexture::GUI()
{
    ImGui::Begin("ShaderTexture");
    {
        ImGui::RadioButton("Normal", sb->GetSelPtr(), 1);
        ImGui::RadioButton("Gray", sb->GetSelPtr(), 2);
        ImGui::RadioButton("Negative", sb->GetSelPtr(), 3);
        ImGui::RadioButton("Blur", sb->GetSelPtr(), 4);
        ImGui::RadioButton("PivotRL", sb->GetSelPtr(), 5);
        ImGui::RadioButton("PivotUD", sb->GetSelPtr(), 6);

        ImGui::SliderInt("BlurCount", sb->GetBCPtr(), 1, 20);
    }
    ImGui::End();
}
