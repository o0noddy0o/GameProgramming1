//����������������������������������������������
// �t�@�C�����@�@�FMissileLauncher.h
// �T�v�@�@�@�@�@�F�~�T�C�����ˋ@�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/01/14 �쐬
//����������������������������������������������
#pragma once
#include "Enemy.h"

class MissileLauncher : public Enemy
{
	typedef Enemy Super;
public:
	MissileLauncher(GameInfo* _pGameInfo, XMFLOAT2 _pedestalPos, float _pedestalAngle = 0.f);
	virtual ~MissileLauncher();

	virtual void renderSprite();

	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f));

	virtual void MoveProcess();

private:
	CPicture* m_pImg2;
	float m_angle;
};