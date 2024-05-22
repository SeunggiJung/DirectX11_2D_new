#include "stdafx.h"
#include "01_CollisionDemo.h"

void CollisionDemo::Init()
{
    r1 = new Rect(
        Vector3(200, 200, 0),
        Vector3(100, 100, 1), 0.0f);

    r2 = new Rect(
        Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0),
        Vector3(100, 100, 1), 0.0f);

    r1->UpdateWorld();
    r2->UpdateWorld();
}

void CollisionDemo::Destroy()
{
    SAFE_DELETE(r2);
    SAFE_DELETE(r1);
}

void CollisionDemo::Update()
{
    r1->Move();

    if (BoundingBox::AABB(r1->GetCollision(),
        r2->GetCollision()) ||
        BoundingBox::OBB(r1->GetCollision(),
        r2->GetCollision()))
    {
        // r2->SetColor(Color(0, 1, 0, 1));
        r2->SetPosition(
            { (float)Random::GetRandomInt(100,1000),
            r2->GetPosition().y,
            r2->GetPosition().z }
        );
    }
    else
    {
        // r2->SetColor(Color(1, 0, 0, 1));
    }

    r1->Update();
    r2->Update();
}

void CollisionDemo::Render()
{
    r1->Render();
    r2->Render();
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI()
{
    r2->GUI();
}
