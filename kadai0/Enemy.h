//����������������������������������������������
// �t�@�C�����@�@�FEnemy.h
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//			�@�@�@ 2021/12/08�@�G�̒e�𔭎ˋ@�\��ǉ�
//			�@�@�@ 2021/12/10�@�G�̈ړ�������ǉ�
// �@�@�@�@�@�@�@�@2021/12/17�@�e�̔z����N���X�֐��ɂ��܂���(��)
//����������������������������������������������
#pragma once
#include "CObjectBase.h"
#include "Define.h"

class EnemyBullet;
class BoundingBox;

class Enemy :public CObjectBase 
{
public:
	Enemy(GameInfo* _pGameInfo, float _damage = 0.f);
	virtual ~Enemy();

	// �摜���擾����
	virtual BoundingBox* GetBoundingBox()const = 0;

	// �摜��`�悷��
	virtual void renderSprite();

	// �U���̏���(�X�e�[�W�p)
	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f)) = 0;

	// �ړ��̏���(�X�e�[�W�p)
	virtual void MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime) = 0;

	float GetDamage()const;

	static void ResetEnemyBullet();

	static shared_ptr<vector<shared_ptr<EnemyBullet>>> GetBullet();

protected:
	// �G�̉摜
	CPicture* m_pImg;

	// �e�̔z��
	static shared_ptr<vector<shared_ptr<EnemyBullet>>> m_pEnemyBullet;

	float m_damage;
};