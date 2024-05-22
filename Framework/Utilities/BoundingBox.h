#pragma once

enum
{
    x = 0,
    y
};

struct RectEdge
{
    Vector3 LT;
    Vector3 LB;
    Vector3 RT;
    Vector3 RB;
};

struct AxisData
{
    Vector3 centerPos;  // 중앙 좌표
    Vector3 axisDir[2]; // 축 방향
    float axisLen[2];   // 축 길이
};

class BoundingBox
{
public:
    BoundingBox();
    ~BoundingBox();

    void UpdateData(const Matrix world,
        const Vector3 verticesLocalPosition[]);
    
    // static 키워드는 해당 함수나 변수를 외부에서 불러와서
    // 사용하는것을 허락해주는 키워드 이다.
    static bool AABB(BoundingBox* a, BoundingBox* b);
    static bool OBB(BoundingBox* a, BoundingBox* b);

private:
    RectEdge* edge = nullptr;
    AxisData* data = nullptr;
};