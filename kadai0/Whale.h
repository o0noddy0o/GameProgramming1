//����������������������������������������������
// �t�@�C�����@�@�FWhale.h
// �T�v�@�@�@�@�@�F�N�W���i�X�e�[�W�P�̃{�X�j�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/17 �쐬�i���j
//����������������������������������������������
#pragma once
#include "Boss.h"

class MissileLauncher;

class Whale : public Boss
{
	typedef Boss Super;
public:
	Whale(GameInfo* _pGameInfo);
	virtual ~Whale();

	// �s���p�^�[�������߂�
	virtual void DecideActionPattern(XMFLOAT2 _SubmarinePos)override;

	// ���t���[���̏���
	virtual void Tick(XMFLOAT2 _SubmarinePos)override;

	// �摜�̕`��
	virtual void renderSprite()override;
private:
	float m_angle;								// �N�W���̌���
	MissileLauncher*	m_pMissileLauncher[2];	// �N�W���̔w�ɏ悹���~�T�C�����ˋ@
	XMFLOAT2			m_missilePos[2];		// �~�T�C�����ˋ@�̑��΍��W
};