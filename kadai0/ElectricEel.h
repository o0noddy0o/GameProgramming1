//����������������������������������������������
// �t�@�C�����@�@�FElectricEel.h
// �T�v�@�@�@�@�@�F�d�C�E�i�M�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/13 �쐬�i���j
//����������������������������������������������
#pragma once

#include "Fish.h"

class ElectricEel : public Fish
{
	typedef Fish Super;
public:
	ElectricEel(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle = 0.f);
	virtual ~ElectricEel();

	// �U���̏���
	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f));

	// �ړ�����
	virtual void MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime);

private:
};