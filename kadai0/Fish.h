//����������������������������������������������
// �t�@�C�����@�@�FFish.h
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//����������������������������������������������
#pragma once
#include "Enemy.h"

class BoundingBox;
class RectangleBoundingBox;

class Fish:public Enemy
{
public:
	Fish(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f,0.f });
	~Fish();

	// �U���̏���
	virtual void AttackProcess();
		
	// �ړ�����
	virtual void MoveProcess();

	virtual BoundingBox* GetBoundingBox()const;
private:
	// �����蔻��
	RectangleBoundingBox* m_pBoundingBox;
};

