//����������������������������������������������
// �t�@�C�����@�@�FMissile.h
// �T�v�@�@�@�@�@�F�~�T�C���̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/01/14 �쐬
//����������������������������������������������
#pragma once
#include "EnemyBullet.h"

class Missile : public EnemyBullet
{
	typedef EnemyBullet Super;
public:
	Missile(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle, bool _bBigSize = false);
	virtual ~Missile();
	virtual void MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f))override;

private:

};