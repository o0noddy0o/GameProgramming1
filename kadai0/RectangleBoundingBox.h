//����������������������������������������������
// �t�@�C�����@�@�FRectangleBoundingBox.h
// �T�v�@�@�@�@�@�F�l�p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#pragma once
#include "stdafx.h"

class RectangleBoundingBox
{
public:
	RectangleBoundingBox();
	~RectangleBoundingBox();

	XMFLOAT2 GetPos()const;
	XMFLOAT2 GetSize()const;

private:
	XMFLOAT2 m_pos;
	XMFLOAT2 m_size;
};