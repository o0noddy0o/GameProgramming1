//����������������������������������������������
// �t�@�C�����@�@�FPolygonBoundingBox.h
// �T�v�@�@�@�@�@�F���p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#pragma once
#include "stdafx.h"
#include "BoundingBox.h"

class PolygonBoundingBox : public BoundingBox
{
	typedef BoundingBox Super;
public:
	// �R���X�g���N�^
	PolygonBoundingBox(XMFLOAT2 _pos, vector<XMFLOAT2>& _vertexPos, XMFLOAT2 _relativePos = { 0.f, 0.f });

	// �f�X�g���N�^
	~PolygonBoundingBox();

	// ��{���̎擾
	XMFLOAT2 GetPos()const;					// ���S���W
	XMFLOAT2 GetMaxPos()const;				// ���_���W�̒���ԑ傫��X���W��Y���W
	XMFLOAT2 GetMinPos()const;				// ���_���W�̒���ԏ�����X���W��Y���W
	vector<XMFLOAT2>* GetVertexPos()const;	// ���_���W�̔z��
	vector<XMFLOAT2>* GetVector()const;		// ���_���W���璸�_���W�̃x�N�g���̔z��

	// ��{���̐ݒu
	void SetPos(XMFLOAT2 _pos);
	void ResetVertexPos(vector<XMFLOAT2>& _vertexPos);
	void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f });
	void RotateVertex(float _angle);
	
	// �����蔻��
	bool Collision(const BoundingBox* _target)const;
	bool Collision(CPicture* _target)const;						// �摜
	bool Collision(const CircleBoundingBox* _target)const;		// �ۂ��o�E���f�B���O�{�b�N�X
	bool Collision(const RectangleBoundingBox* _target)const;	// �l�p�`�o�E���f�B���O�{�b�N�X
	bool Collision(const PolygonBoundingBox* _target)const;		// ���p�`�o�E���f�B���O�{�b�N�X

private:
	XMFLOAT2						m_pos;			// �o�E���f�B���O�{�b�N�X�̒��S���W
	XMFLOAT2						m_maxPos;		// ���_���W�̒���ԑ傫��X���W��Y���W
	XMFLOAT2						m_minPos;		// ���_���W�̒���ԏ�����X���W��Y���W
	shared_ptr<vector<XMFLOAT2>>	m_pVertexPos;	// ���_���W�̔z��
	shared_ptr<vector<XMFLOAT2>>	m_pVector;		// ���_���W���璸�_���W�̃x�N�g���̔z��
	XMFLOAT2						m_relativePos;	// �o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
};