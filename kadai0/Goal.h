//����������������������������������������������
// �t�@�C�����@�@�FGoal.h
// �T�v�@�@�@�@�@�F�S�[���̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/02/16 �쐬�i���j
//����������������������������������������������
#pragma once
#include "CObjectBase.h"

class BoundingBox;
class RectangleBoundingBox;

class Goal : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Goal(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _size = {250.f, 250.f});
	virtual ~Goal();
	virtual BoundingBox* GetBoundingBox()const;
	virtual void rendingSprite();

protected:
	CPicture* m_pImg;
	RectangleBoundingBox* m_pBoundingBox;
};