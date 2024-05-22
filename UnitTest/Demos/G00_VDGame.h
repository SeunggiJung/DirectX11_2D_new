#pragma once

#include "Geometries/Rect.h"

class VDGame : public IObject
{
public:
    // IObject��(��) ���� ��ӵ�
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;

};

/*
����! ���󿡼� ���� �������� �����
// �Ⱓ : 24.04.19 ~ 24.04.26

�⺻
: 1 �������� ��� �� ������Ʈ ��ġ�ϱ�
1. �÷��̾� ��ġ �� ����
2. ��� ��ġ
3. ���ع� ��ġ �� �̵� // ���ع� �׸���
// ���� �浹�� �ȹ���� ������ ���̳� ���ع��� ��Ƶ� �ƹ��� �̻� ����
// ���� �հ� ���ع��� ��Ƶ� ������
// 24.04.22 ���� �ؿ���

�⺻+
: 1�������� �浹 �����ϱ�
1. �÷��̾�� ���� ������ ���� // Ȥ�� ��� ���� ������ ����
2. ���ع��� ������ ���� ��ġ�� ���ư�
3. �ݴ��� Ư�� ������ ���� ���� �������� �̵�
// �������� �������̳� Ư¡�� �����Ӱ� ������
// �ݵ�� �Ϻ��ϰ� �Ȱ��� �ʿ� ����

�߰�
: 2 ~ 3�������� �� �����ϱ�
// �밡�� ����

*/