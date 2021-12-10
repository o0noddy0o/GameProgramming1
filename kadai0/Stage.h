//����������������������������������������������
// �t�@�C�����@�@�FStage.h
// �T�v�@�@�@�@�@�F�X�e�[�W�ɏo�鑼�̕��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/01 �쐬
//����������������������������������������������
#pragma once
#include "CObjectBase.h"
#include "Define.h"
#include "Submarine.h"
#include "SceneryObject.h"

class EnemyBullet;

class Stage :public CObjectBase
{
	typedef CObjectBase Super;
public:
	Stage(GameInfo* _pGameInfo);
	~Stage();
	// ���t���[���̏���
	void Tick();

	// �S�Ă�Render���\�b�h���Ăяo��
	void RenderProcess();

	// �S�ē����蔻����܂Ƃ߂����\�b�h(�����͂̂��Ăяo��)
	void CollisionProcess();

	// �����̓I�u�W�F�N�g
	shared_ptr < Submarine > m_pSubmarine;

	// �}�b�v�ɂ����Q���Ȃǂ̃I�u�W�F�N�g�̔z��
	vector < shared_ptr < SceneryObject > > m_pSceneryObject;

	// �G�̃I�u�W�F�N�g�̔z��
	vector < shared_ptr < Enemy > > m_pEnemy;

	// �A�C�e���̃I�u�W�F�N�g�̔z��
	//vector < shared_ptr < Item > > m_pItem;

	// �G�̒e�̔z��̃A�h���X�̔z��
	vector < vector < shared_ptr < EnemyBullet > >* > m_pEnemyBullet;

	// �O1�t���[���̎���(deltaTime�v�Z�p)
	clock_t m_lastFrameTime;

	int m_map[Map_Y_SIZE][Map_X_SIZE];
};
