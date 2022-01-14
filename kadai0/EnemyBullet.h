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

class EnemyBullet : public CObjectBase
{
	typedef CObjectBase Super;
public:
	EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, float _angle = 0.f, int _bulletType = 0);
	~EnemyBullet();

	BoundingBox* GetBoundingBox()const;
	int GetBulletType()const;
	void renderSprite();											// �e�̉摜��`��
	void SetPos(XMFLOAT2 _newPos);									// �e�̉摜�̈ʒu���Z�b�g����
	bool GetActive()const;											// �e�̉摜�摜���\���\��
	void SetActive(bool _b);										// �e�̉摜��\���\�i�s�j�ɂ���
	void SetMoveDirection(float _angle);							// �e�̈ړ��������Z�b�g����
	virtual void MoveProcess(float _deltaTime);						// �ړ��̏���

protected:
	CPicture* m_pImg;			// �e�̉摜
	XMFLOAT2 m_moveDirection;	// �e�̈ړ������i�x�N�g���j
	BoundingBox* m_pBoundingBox;
	int m_bulletType;
};