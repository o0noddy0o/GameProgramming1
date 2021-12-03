//����������������������������������������������
// �t�@�C�����@�@�FBoundingBox.h
// �T�v�@�@�@�@�@�F�o�E���f�B���O�{�b�N�X�̉��z�N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/27 �쐬
//����������������������������������������������
#pragma once

class CPicture;

class BoundingBox
{
public:
	BoundingBox(int _boundingBoxType) :m_boundingBoxType(_boundingBoxType) {}
	~BoundingBox() {}

	virtual bool Collision(const BoundingBox* _target)const = 0;
	virtual bool Collision(CPicture* _target)const = 0;
	virtual void SetPos(XMFLOAT2 _pos) = 0;
	virtual void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f }) = 0;

public:
	const int m_boundingBoxType; // 1->�Z, 2->��, 3->���p�`
};