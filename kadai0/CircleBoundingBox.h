//����������������������������������������������
// �t�@�C�����@�@�FCircleBoundingBox.h
// �T�v�@�@�@�@�@�F�ۂ��o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
// �@�@�@�@�@�@�@�F2021/11/27 ��{����ݒu���郁�\�b�h�̒ǉ�
//����������������������������������������������
#pragma once
#include "stdafx.h"

class CPicture;
class RectangleBoundingBox;
class PolygonBoundingBox;

class CircleBoundingBox
{
public:
	// �R���X�g���N�^
	CircleBoundingBox(XMFLOAT2 _pos, float _radius, XMFLOAT2 _relativePos = {0.f, 0.f});

	// �f�X�g���N�^
	~CircleBoundingBox();

	// ��{���̎擾
	XMFLOAT2 GetPos()const;		// ���S���W
	float GetRadius()const;		// �~�̔��a

	// ��{���̐ݒu
	void SetPos(XMFLOAT2 _pos);
	void ChangeRadius(float _newRadius);
	void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f });

	// �����蔻��
	bool Collision(CPicture* _target)const;						// �摜
	bool Collision(const CircleBoundingBox* _target)const;		// �ۂ��o�E���f�B���O�{�b�N�X
	bool Collision(const RectangleBoundingBox* _target)const;	// �l�p�`�o�E���f�B���O�{�b�N�X
	bool Collision(const PolygonBoundingBox* _target)const;		// ���p�`�o�E���f�B���O�{�b�N�X

private:
	XMFLOAT2	m_pos;			// �o�E���f�B���O�{�b�N�X�̒��S���W
	float		m_radius;		// �o�E���f�B���O�{�b�N�X�̔��a
	XMFLOAT2	m_relativePos;	// �o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
};