//����������������������������������������������
// �t�@�C�����@�@�FThunderBullet.h
// �T�v�@�@�@�@�@�F�d�C�E�i�M���g���e�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/01/13 �쐬
//����������������������������������������������
#pragma once

#include "EnemyBullet.h"

class ThunderBullet : public EnemyBullet
{
	typedef EnemyBullet Super;
public:
	ThunderBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, float _angle = 0.f);
	~ThunderBullet();

	virtual void MoveProcess(float _deltaTime);

private:

};