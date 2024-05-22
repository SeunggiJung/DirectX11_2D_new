#pragma once

// 단색의 사각형을 그릴때 사용될 VertexType
struct VertexColor
{
    VertexColor()
        : position(0,0,0), color(0,0,0,0) {}

    VertexColor(Vector3 position, Color color)
        : position(position), color(color) {}

    // 정점의 위치
    Vector3 position;
    // 정점의 색
    Color color;

    // static 은 해당 데이터를 외부에서 사용하는것을 허락한다는 키워드

    // 정점의 데이터의 구조를 서술해줄 desc들
    static D3D11_INPUT_ELEMENT_DESC descs[];

    // 정점 데이터의 개수
    // 2인 이유는 position과 color 2개를 가지고 있기 때문
    static const UINT count = 2;
};

// 그림이 있는 사각형을 그릴때 사용될 VertexType
struct VertexTexture
{
    VertexTexture()
        : position(0, 0, 0), uv(0, 0) {}

    VertexTexture(Vector3 position, Vector2 uv)
        : position(position), uv(uv) {}

    // 정점의 위치
    Vector3 position;
    // 그림의 좌표
    Vector2 uv;

    // static 은 해당 데이터를 외부에서 사용하는것을 허락한다는 키워드

    // 정점의 데이터의 구조를 서술해줄 desc들
    static D3D11_INPUT_ELEMENT_DESC descs[];

    // 정점 데이터의 개수
    // 2인 이유는 position과 color 2개를 가지고 있기 때문
    static const UINT count = 2;
};