#include "stdafx.h"
#include "03_ShaderDemo.h"

void ShaderDemo::Init()
{
    st = new ShaderTexture(
        { 320,360,0 },
        { 200,200,1 }, 0.0f,
        TexturePath + L"TakeALook.webp");

    at = new AlphaTexture(
        { 960,360,0 },
        { 200,200,1 }, 0.0f,
        TexturePath + L"TakeALook.webp");
}

void ShaderDemo::Destroy()
{
    SAFE_DELETE(at);
    SAFE_DELETE(st);
}

void ShaderDemo::Update()
{
    st->Update();
    at->Update();
}

void ShaderDemo::Render()
{
    st->Render();
    at->Render();
}

void ShaderDemo::PostRender()
{
}

void ShaderDemo::GUI()
{
    st->GUI();
    at->GUI();
}
