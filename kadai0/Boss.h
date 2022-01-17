//����������������������������������������������
// �t�@�C�����@�@�FBoss.cpp
// �T�v�@�@�@�@�@�F�{�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/17 �쐬�i���j
//����������������������������������������������
#pragma once
#include "CObjectBase.h"
#include <memory>

class EnemyBullet;

class Boss : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Boss(GameInfo* _pGameInfo);
	virtual ~Boss();

	// �s���p�^�[�������߂�
	virtual void DecideActionPattern(XMFLOAT2 _SubmarinePos) = 0;

	// ���t���[���̏���
	virtual void Tick(XMFLOAT2 _SubmarinePos) = 0;

	// �摜�̕`��
	virtual void renderSprite();

public:
	// �e�̔z����擾����
	static shared_ptr<vector<shared_ptr<EnemyBullet>>>	GetEnemyBullet();

	// �e�̔z������Z�b�g����
	static void ResetBossBullet();

	// �e�̔z��̃N���X�ϐ�
	static shared_ptr<vector<shared_ptr<EnemyBullet>>> m_pBullet;	// �e

private:
	vector<CPicture*>	m_pImg;				// �摜
	int					m_actionPattern;	// ���̍s���p�^�[��
};