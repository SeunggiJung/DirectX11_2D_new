#pragma once
#include "Framework.h"

// WVP
/*
WVP = World, View, Projection
- 3D모델을 2D 스크린 좌표로 변환하는 과정 중 하나

1. World // 공간
- 모델의 정점을 세계 좌표계에서 지역 좌표계로 변환하는
것을 의미
- 모델의 위치, 회전 및 크기를 조정

2. View // 카메라
- 세계 좌표계에서 카메라가 바라보는 방향을 나타냄
- 카메라의 위치, 방향 을 조정

3. Projection // 투영법
- 3D 공간을 2D 스크린 좌표로 변환하는 것을 의미
- 시야각, 종회비, 크리핑 평면 등을 고려하여 진행
*/

// World의 데이터를 건내줄 버퍼
class WorldBuffer : public ShaderBuffer
{
public:
    WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // 행렬 초기화 // 모든 값을 0으로
        D3DXMatrixIdentity(&data.world);
    }

    void SetWorld(Matrix world)
    {
        // 행렬 전치 // 열과 행을 바꿈
        D3DXMatrixTranspose(&data.world, &world);
    }

    struct Data
    {
        // CPU에서 GPU로 데이터를 건내줄 때는
        // 16Byte이상의 2배수 값을 넣어주는 것이 좋다.
        // Ex) 16, 32, 64 ...
        Matrix world;
    };
private:
    Data data;
};

// View, Proejction
class VPBuffer : public ShaderBuffer
{
public:
    VPBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // 행렬 초기화 // 모든 값을 0으로
        D3DXMatrixIdentity(&data.view);
        D3DXMatrixIdentity(&data.proj);
    }

    void SetView(Matrix view)
    {
        D3DXMatrixTranspose(&data.view, &view);
    }

    void SetProj(Matrix proj)
    {
        D3DXMatrixTranspose(&data.proj, &proj);
    }

    struct Data
    {
        Matrix view;
        Matrix proj;
    };
private:
    Data data;
};