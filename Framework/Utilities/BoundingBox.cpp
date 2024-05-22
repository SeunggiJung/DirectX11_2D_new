#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
    edge = new RectEdge();
    data = new AxisData();
}

BoundingBox::~BoundingBox()
{
    SAFE_DELETE(data);
    SAFE_DELETE(edge);
}

void BoundingBox::UpdateData(const Matrix world, const Vector3 verticesLocalPosition[])
{
    // AABB
    {
        // LocalPos -> WorldPos
        D3DXVec3TransformCoord(&edge->LT,
            &verticesLocalPosition[3], &world);
        D3DXVec3TransformCoord(&edge->LB,
            &verticesLocalPosition[0], &world);
        D3DXVec3TransformCoord(&edge->RT,
            &verticesLocalPosition[1], &world);
        D3DXVec3TransformCoord(&edge->RB,
            &verticesLocalPosition[2], &world);
    }

    // OBB
    {
        // CenterPos Vector
        {
            data->centerPos = Vector3
            (
                (edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) * 0.25f,
                (edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) * 0.25f,
                0
            );
        }

        // AxisDir 
        {
            // Normal이 들어가는 대부분은 정규화 시키는 함수이다.
            // 정규화는 모든 값을 0 ~ 1 로 바꾸는 과정이다.
            D3DXVec3TransformNormal(&data->axisDir[x],
                &Vector3(1, 0, 0), &world);
            D3DXVec3TransformNormal(&data->axisDir[y],
                &Vector3(0, 1, 0), &world);

            D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
            D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
        }

        // AxisLen
        {
            Vector3 unitAxis[2] =
            { data->axisDir[x], data->axisDir[y] };

            Vector3 verticesPos[4] =
            { edge->LT, edge->LB, edge->RT, edge->RB };

            float minValues[2] = { INT_MAX, INT_MAX };
            float maxValues[2] = { INT_MIN, INT_MIN };
            
            for (int i = 0; i < 4; i++)
            {
                Vector3 point = verticesPos[i];

                for (int j = 0; j < 2; j++)
                {
                    float projection =
                        D3DXVec3Dot(&point, &unitAxis[j]);

                    if (projection < minValues[j])
                        minValues[j] = projection;

                    if (projection > maxValues[j])
                        maxValues[j] = projection;
                }
            }

            data->axisLen[x] = (maxValues[x] - minValues[x]) * 0.5f;
            data->axisLen[y] = (maxValues[y] - minValues[y]) * 0.5f;
        }
    }
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
    if (a == nullptr || b == nullptr) return false;

    RectEdge aEdge = *a->edge;
    RectEdge bEdge = *b->edge;

    if (aEdge.LT.x <= bEdge.RB.x &&
        aEdge.LT.y >= bEdge.RB.y &&
        aEdge.RB.x >= bEdge.LT.x &&
        aEdge.RB.y <= bEdge.LT.y)
        return true;

    return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
    if (a == nullptr || b == nullptr) return false;

    AxisData aData = *a->data;
    AxisData bData = *b->data;

    Vector3 centerDir, axis;
    float centerProjDist, r1, r2;

    // a와 b사이의 거리
    centerDir = aData.centerPos - bData.centerPos;

    // a Rect : x축
    {
        // 기준 축
        axis = aData.axisDir[x];

        // 비교할 사이거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        // 기준 렉트의 기준 축의 길이
        r1 = aData.axisLen[x];
        r2 = abs(D3DXVec3Dot(&bData.axisDir[x], &axis)
                * bData.axisLen[x]) +
            abs(D3DXVec3Dot(&bData.axisDir[y], &axis)
                * bData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // a Rect : y축
    {
        // 기준 축
        axis = aData.axisDir[y];

        // 비교할 사이거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        // 기준 렉트의 기준 축의 길이
        r1 = aData.axisLen[y];
        r2 = abs(D3DXVec3Dot(&bData.axisDir[x], &axis)
            * bData.axisLen[x]) +
            abs(D3DXVec3Dot(&bData.axisDir[y], &axis)
                * bData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // b Rect : x축
    {
        // 기준 축
        axis = bData.axisDir[x];

        // 비교할 사이거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        // 기준 렉트의 기준 축의 길이
        r1 = bData.axisLen[x];

        r2 = abs(D3DXVec3Dot(&aData.axisDir[x], &axis)
            * aData.axisLen[x]) +
            abs(D3DXVec3Dot(&aData.axisDir[y], &axis)
                * aData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // b Rect : y축
    {
        // 기준 축
        axis = bData.axisDir[y];

        // 비교할 사이거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        // 기준 렉트의 기준 축의 길이
        r1 = bData.axisLen[y];

        r2 = abs(D3DXVec3Dot(&aData.axisDir[x], &axis)
            * aData.axisLen[x]) +
            abs(D3DXVec3Dot(&aData.axisDir[y], &axis)
                * aData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    return true;
}
