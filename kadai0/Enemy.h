//����������������������������������������������
// �t�@�C�����@�@�FEnemy.h
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//����������������������������������������������
#pragma once
#include "CObjectBase.h"
#include "Define.h"

class EnemyBullet;
class BoundingBox;

class Enemy :public CObjectBase 
{
public:
	Enemy(GameInfo* _pGameInfo);
	virtual ~Enemy();

	// �摜���擾����
	virtual BoundingBox* GetBoundingBox()const = 0;

	// �摜��`�悷��
	virtual void renderSprite();

	// �U���̏���(�X�e�[�W�p)
	virtual void AttackProcess() = 0;

	// �ړ��̏���(�X�e�[�W�p)
	virtual void MoveProcess() = 0;

	// �e�̔z��̃A�h���X���擾����
	virtual vector < shared_ptr < EnemyBullet > >* GetBullet();

protected:
	// �G�̉摜
	CPicture* m_pImg;

	// �e�̔z��
	vector < shared_ptr < EnemyBullet > >m_pBullet;
};
