//����������������������������������������������
// �t�@�C�����@�@�FEnemyBullet.h
// �T�v�@�@�@�@�@�F�G�̒e�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/07 �쐬
//����������������������������������������������
#pragma once

#include "CObjectBase.h"

class Enemy;
class SceneryObject;
class BoundingBox;
class CircleBoundingBox;

enum TypeOfEnemyBullet
{
	normal = 0,
	thunderBullet,
	missile,
	fire,
	laser,
	Total
};

class EnemyBullet : public CObjectBase
{
	typedef CObjectBase Super;
public:
	EnemyBullet(GameInfo* _pGameInfo, TypeOfEnemyBullet _bulletType = normal);
	EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle = 0.f, TypeOfEnemyBullet _bulletType = normal);
	EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _moveDirection, TypeOfEnemyBullet _bulletType = normal);
	~EnemyBullet();

	BoundingBox* GetBoundingBox()const;
	int GetBulletType()const;
	virtual void renderSprite();										// �e�̉摜��`��
	virtual void SetPos(XMFLOAT2 _newPos);								// �e�̉摜�̈ʒu���Z�b�g����
	virtual bool GetActive()const;										// �e�̉摜�摜���\���\��
	virtual void SetActive(bool _b);									// �e�̉摜��\���\�i�s�j�ɂ���
	virtual void SetMoveDirection(float _angle);								// �e�̈ړ��������Z�b�g����
	virtual void SetMoveDirection(XMFLOAT2 _moveDirection);						// �e�̈ړ��������Z�b�g����
	virtual void MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f));	// �ړ��̏���

protected:
	CPicture* m_pImg;			// �e�̉摜
	XMFLOAT2 m_moveDirection;	// �e�̈ړ������i�x�N�g���j
	BoundingBox* m_pBoundingBox;
	TypeOfEnemyBullet m_bulletType;
};