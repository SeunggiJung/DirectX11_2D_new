#pragma once

#include "Geometries/Rect.h"

class VDGame : public IObject
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
과제! 세상에서 가장 어려운게임 만들기
// 기간 : 24.04.19 ~ 24.04.26

기본
: 1 스테이지 배경 및 오브젝트 배치하기
1. 플레이어 배치 및 조작
2. 배경 배치
3. 장해물 배치 및 이동 // 장해물 네모임
// 아직 충돌을 안배웠기 때문에 벽이나 장해물에 닿아도 아무런 이상 없음
// 벽은 뚫고 장해물에 닿아도 안죽음
// 24.04.22 까지 해오기

기본+
: 1스테이지 충돌 구현하기
1. 플레이어는 벽을 뚫을수 없음 // 혹은 배경 밖을 나갈수 없음
2. 장해물에 닿을시 시작 위치로 돌아감
3. 반대편 특정 구역에 들어갈시 다음 스테이지 이동
// 개인적인 디테일이나 특징은 자유롭게 가능함
// 반드시 완벽하게 똑같을 필요 없음

추가
: 2 ~ 3스테이지 등 구현하기
// 노가다 영역

*/