//����������������������������������������������
// �t�@�C�����@�@�FWhale.h
// �T�v�@�@�@�@�@�F�N�W���i�X�e�[�W�P�̃{�X�j�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/17 �쐬�i���j
//����������������������������������������������
#pragma once
#include "Boss.h"
#include "Enemy.h"

class MissileLauncher;

class Whale : public Boss
{
	typedef Boss Super;
private:
	// �N�W���̍U���p�^�[��
	enum ActionPattern
	{
		none = 0,
		biowFire,
		dash,
		laser,
		summonEnemy,
		Total
	};

public:
	Whale(GameInfo* _pGameInfo, XMFLOAT2 _pos);
	virtual ~Whale();

	// �s���p�^�[�������߂�
	virtual void DecideActionPattern(XMFLOAT2 _SubmarinePos);

	// ���t���[���̏���
	virtual void Tick(XMFLOAT2 _SubmarinePos)override;

	// �摜�̕`��
	virtual void renderSprite()override;

// �e�U���p�^�[���̊֐�
private:
	void BiowFireProcess(XMFLOAT2 _SubmarinePos);
	void LaserProcess();
	void DashProcess();
	void SummonEnemyProcess();

private:
	ActionPattern			m_nowAction;
	XMFLOAT2				m_pos;
	MissileLauncher*		m_pMissileLauncher;	// �N�W���̔w�ɏ悹���~�T�C�����ˋ@
	vector<Enemy*>			m_pEnemy;
	int						m_actionTimeCnt;
};