//����������������������������������������������
// �t�@�C�����@�@�FRock.h
// �T�v�@�@�@�@�@�F��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/01/13 �쐬
//����������������������������������������������
#pragma once
#include "SceneryObject.h"

class Rock : public SceneryObject
{
	typedef SceneryObject Super;
public:
	Rock(GameInfo* _pGameInfo, int _rockType, XMFLOAT2 _pos, float _angle = 0.f);
	virtual ~Rock();
};