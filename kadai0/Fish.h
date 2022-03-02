//����������������������������������������������
// �t�@�C�����@�@�FFish.h
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//			�@�@�@2021/12/08�@�G�̒e�𔭎ˋ@�\��ǉ�
//			�@�@�@2021/12/10�@�G�̈ړ�������ǉ�
//����������������������������������������������
#pragma once
#include "Enemy.h"

class BoundingBox;
class RectangleBoundingBox;

class Fish:public Enemy
{
public:
	Fish(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f,0.f }, float _angle = 0.f);
	virtual ~Fish();

	// �U���̏���
	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f));
		
	// �ړ�����
	virtual void MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime);

	virtual XMFLOAT2 GetMoveDirection()const override;
	
	virtual void SetMoveDirection(XMFLOAT2 _newMoveDirection)override;

	virtual BoundingBox* GetBoundingBox()const;
protected:
	// �����蔻��
	RectangleBoundingBox* m_pBoundingBox;
	float m_angle;
	int m_coolDownCnt;
	int m_coolDown;
};

