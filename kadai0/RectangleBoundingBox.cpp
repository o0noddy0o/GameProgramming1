//����������������������������������������������
// �t�@�C�����@�@�FRectangleBoundingBox.cpp
// �T�v�@�@�@�@�@�F�l�p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#include "RectangleBoundingBox.h"

RectangleBoundingBox::RectangleBoundingBox()
{
}

RectangleBoundingBox::~RectangleBoundingBox()
{
}

XMFLOAT2 RectangleBoundingBox::GetPos()const
{
	return m_pos;
}

XMFLOAT2 RectangleBoundingBox::GetSize()const
{
	return m_size;
}