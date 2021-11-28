//����������������������������������������������
// �t�@�C�����@�@�FRectangleBoundingBox.h
// �T�v�@�@�@�@�@�F�l�p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
// �@�@�@�@�@�@�@�F2021/11/27 �R���W�����̎���
//����������������������������������������������
#pragma once
#include "stdafx.h"

class CPicture;
class CircleBoundingBox;
class PolygonBoundingBox;

class RectangleBoundingBox
{
public:
	// �R���X�g���N�^
	RectangleBoundingBox(XMFLOAT2 _pos, XMFLOAT2 _size, XMFLOAT2 _relativePos = { 0.f, 0.f });

	// �f�X�g���N�^
	~RectangleBoundingBox();

	// ��{���̎擾
	XMFLOAT2 GetPos()const;
	XMFLOAT2 GetSize()const;

	// ��{���̐ݒu
	void SetPos(XMFLOAT2 _pos);
	void ChangeSize(XMFLOAT2 _newSize);
	void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f });

	// �����蔻��
	bool Collision(CPicture* _target)const;						// �摜
	bool Collision(const CircleBoundingBox* _target)const;		// �ۂ��o�E���f�B���O�{�b�N�X
	bool Collision(const RectangleBoundingBox* _target)const;	// �l�p�`�o�E���f�B���O�{�b�N�X
	bool Collision(const PolygonBoundingBox* _target)const;		// ���p�`�o�E���f�B���O�{�b�N�X

private:
	XMFLOAT2 m_pos;			// �o�E���f�B���O�{�b�N�X�̒��S���W
	XMFLOAT2 m_size;		// �o�E���f�B���O�{�b�N�X�̃T�C�Y
	XMFLOAT2 m_relativePos;	// �o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
};