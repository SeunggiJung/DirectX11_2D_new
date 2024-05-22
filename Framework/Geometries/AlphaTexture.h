#pragma once

#include "TextureRect.h"

class AlphaBuffer : public ShaderBuffer
{
public:
    AlphaBuffer() : ShaderBuffer(&data, sizeof(data))
    {
        data.alphaColor = 0xff73e6e1; // Graphics에 있는 clearColor
        data.alpha = 0.0f;
    }

    float GetAlpha() { return data.alpha; }
    float* GetAlphaPtr() { return &data.alpha; }
    void SetAlpha(float alpha) { data.alpha = alpha; }

    Color GetAlphaColor() { return data.alphaColor; }
    void SetAlphaColor(Color color) { data.alphaColor = color; }

    struct Data
    {
        Color alphaColor;        
        float alpha;

        Vector3 dummy; // 패딩 데이터
    };
private:
    Data data;
};

class AlphaTexture : public TextureRect
{
public:
    AlphaTexture(Vector3 position, Vector3 size, float rotation, wstring path);
    ~AlphaTexture();

    void Update();
    void Render();
    void GUI();

    AlphaBuffer* GetAB() { return ab; }

private:
    AlphaBuffer* ab = nullptr;
};