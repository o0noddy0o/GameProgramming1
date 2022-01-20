//����������������������������������������������
// �t�@�C�����@�@�FFire.h
// �T�v�@�@�@�@�@�F�΂̒e�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/19 �쐬�i���j
//����������������������������������������������
#pragma once

#include "EnemyBullet.h"

class Fire : public EnemyBullet
{
	typedef EnemyBullet Super;
public:
	Fire(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _moveDirection, int _disappearCnt);
	virtual ~Fire();
	virtual void renderSprite()override;
	virtual void MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f))override;
	void SetDisappearTime(int _newDisappearTime);
	virtual void SetMoveDirection(float _angle)override;
	virtual void SetMoveDirection(XMFLOAT2 _moveDirection)override;

private:
	int m_disappearCnt;
	int m_disappearTime;
};