#pragma once

#include "Geometries/Rect.h"

class TGame : public IObject
{
public:
    // IObject을(를) 통해 상속됨
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;

};

/*
과제! 추격하는 AI만들어 오기
// 기간 : 24.04.26 ~ 24.05.03

기본
: 플레이어의 위치를 알고 해당 위치로 이동하는 AI 렉트
// 순간이동이 아니라 플레이어처럼 천천히 이동해야됨
// 방식은 자유

기본+
: 플레이어와 AI 렉트와 충돌시 
플레이어는 랜덤한 위치로 이동
// 이때 랜덤한 위치로 이동한 곳에 AI 렉트가 있을수 있는
// 위험요소 방지하기
// AI 렉트 위치가 랜덤 이동 좌표에서 제외돼야 할꺼임

추가
: 플레이어가 장시간 AI 렉트가 충돌하지 않을시
추가 AI 렉트 투입
// 추가 AI 렉트가 투입 된 이후 플레이어가 AI 렉트와
// 충돌할시 충돌한 AI 렉트를 제외하곤 전부 사라져야함
// 그리고 다시 시간이 지나면 나타남

참고하면 좋을내용
// FSM (유한 상태 머신) // AI 알고리즘
// State Mation // 상태 변화 디자인 패턴 // enum 사용

*/