#pragma once

#include "Geometries/Rect.h"

class CollisionDemo : public IObject
{
public:
    // IObject을(를) 통해 상속됨
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;

private:
    Rect* r1 = nullptr;
    Rect* r2 = nullptr;
};