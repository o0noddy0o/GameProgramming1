//����������������������������������������������
// �t�@�C�����@�@�FBullet.h
// �T�v�@�@�@�@�@�F�v���C���[�̒e�̂��N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/20 �쐬
//����������������������������������������������
#pragma once

#include "CObjectBase.h"

class Enemy;
class SceneryObject;

class Bullet : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Bullet(GameInfo* _pGameInfo, XMFLOAT2 _pos = {0.f, 0.f}, float _angle = 0.f);
	~Bullet();

	CPicture* GetImg()const;										// �e�̉摜���擾
	void renderSprite();											// �e�̉摜��`��
	void SetPos(XMFLOAT2 _newPos);									// �e�̉摜�̈ʒu���Z�b�g����
	bool GetActive()const;											// �e�̉摜�摜���\���\��
	void SetActive(bool _b);										// �e�̉摜��\���\�i�s�j�ɂ���
	void SetMoveDirection(float _angle);							// �e�̈ړ��������Z�b�g����
	void MoveProcess(float _deltaTime);								// �ړ��̏���
	bool Collision(vector<shared_ptr<Enemy>>* _target);				// �e�̓����蔻��i�G�Ƃ́j
	bool Collision(vector<shared_ptr<SceneryObject>>* _target);		// �e�̓����蔻��i��Q���Ƃ́j

private:
	CPicture* m_pImg;			// �e�̉摜
	XMFLOAT2 m_moveDirection;	// �e�̈ړ������i�x�N�g���j
};