//����������������������������������������������
// �t�@�C�����@�@�FArrow.h
// �T�v�@�@�@�@�@�F�q���g�̖��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/02/27 �쐬
//����������������������������������������������
#pragma once

#include "CObjectBase.h"

class Arrow : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Arrow(GameInfo* _pGameInfo, XMFLOAT2 _goalPos);
	~Arrow();
	void RenderSprite();
	void Tick();

private:
	CPicture* m_pImg;
	XMFLOAT2 m_goalPos;
};