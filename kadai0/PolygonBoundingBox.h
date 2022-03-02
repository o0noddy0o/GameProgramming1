//����������������������������������������������
// �t�@�C�����@�@�FPolygonBoundingBox.h
// �T�v�@�@�@�@�@�F���p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#pragma once
#include "stdafx.h"
#include "BoundingBox.h"

class CircleBoundingBox;
class RectangleBoundingBox;

class PolygonBoundingBox : public BoundingBox
{
	typedef BoundingBox Super;
public:
	// �R���X�g���N�^
	PolygonBoundingBox(XMFLOAT2 _pos, vector<XMFLOAT2>& _vertexPos, bool _bRelativePosActive = false, XMFLOAT2 _relativePos = { 0.f, 0.f });

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
	void FlipHorizontal();
	void FlipVertical();

	// �����蔻��
	bool Collision(const BoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const override;
	bool Collision(CPicture* _target, XMFLOAT2* _pDirectionVector = NULL)const override;					// �摜
	bool Collision(const CircleBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const override;		// �ۂ��o�E���f�B���O�{�b�N�X
	bool Collision(const RectangleBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const override;	// �l�p�`�o�E���f�B���O�{�b�N�X
	bool Collision(const PolygonBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const override;	// ���p�`�o�E���f�B���O�{�b�N�X

private:
	bool CollisionWithCircle(const CircleBoundingBox* _target)const;
	bool CollisionWithRectangle(const RectangleBoundingBox* _target, vector<int>& hitLine)const;
	bool CollisionWithPolygon(const PolygonBoundingBox* _target)const;

private:
	XMFLOAT2						m_pos;			// �o�E���f�B���O�{�b�N�X�̒��S���W
	XMFLOAT2						m_maxPos;		// ���_���W�̒���ԑ傫��X���W��Y���W
	XMFLOAT2						m_minPos;		// ���_���W�̒���ԏ�����X���W��Y���W
	shared_ptr<vector<XMFLOAT2>>	m_pVertexPos;	// ���_���W�̔z��
	shared_ptr<vector<XMFLOAT2>>	m_pVector;		// ���_���W���璸�_���W�̃x�N�g���̔z��
	XMFLOAT2						m_relativePos;	// �o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
	bool							m_bRelativePosActive;
};