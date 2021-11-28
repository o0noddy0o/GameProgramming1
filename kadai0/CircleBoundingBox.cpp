//����������������������������������������������
// �t�@�C�����@�@�FCircleBoundingBox.cpp
// �T�v�@�@�@�@�@�F�ۂ��o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#include "Define.h"
#include "CPicture.h"
#include "CircleBoundingBox.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"
#include <math.h>

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�o�E���f�B���O�{�b�N�X�̒��S���W
// �����Q�F�o�E���f�B���O�{�b�N�X�̔��a
// �����R�F�o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
//����������������������������������������������
CircleBoundingBox::CircleBoundingBox(XMFLOAT2 _pos, float _radius, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_radius(_radius)
	, m_relativePos(_relativePos)
	, Super(1)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
CircleBoundingBox::~CircleBoundingBox()
{
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̒��S���W���擾����
//����������������������������������������������
XMFLOAT2 CircleBoundingBox::GetPos()const
{
	return m_pos;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̔��a���擾����
//����������������������������������������������
float CircleBoundingBox::GetRadius()const
{
	return m_radius;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W��ݒu����
// �����P�F���̃o�E���f�B���O�{�b�N�X�����I�u�W�F�N�g�̐V�������W
//����������������������������������������������
void CircleBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̔��a��ς���
// �����P�F�V�������a
//����������������������������������������������
void CircleBoundingBox::ChangeRadius(float _newRadius)
{
	m_radius = _newRadius;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W�Ƃ�������I�u�W�F�N�g�̍��W�̍���ς���
// �����P�F�V���������i���j
//����������������������������������������������
void CircleBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//����������������������������������������������
// ���o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
//����������������������������������������������
bool CircleBoundingBox::Collision(const BoundingBox* _target)const
{
	if (_target->m_boundingBoxType == 1)
	{
		return Collision((CircleBoundingBox*)_target);
	}
	else if(_target->m_boundingBoxType == 2)
	{
		return Collision((RectangleBoundingBox*)_target);
	}
	else if (_target->m_boundingBoxType == 3)
	{
		return Collision((PolygonBoundingBox*)_target);
	}
	return false;
}

//����������������������������������������������
// �摜�Ƃ̓����蔻��
// �����P�F�Ώۂ̉摜
//����������������������������������������������
bool CircleBoundingBox::Collision(CPicture* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + targetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < targetPos.x - targetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > targetPos.y + targetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < targetPos.y - targetSize.y / 2.f - m_radius)return false;

	// ���W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - targetPos.x, m_pos.y - targetPos.y };

	if (Abs(relativePos.x) <= targetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= targetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - targetSize.x / 2.f, Abs(relativePos.y) - targetSize.y };

	if (pos.x * pos.x + pos.y * pos.y <= m_radius * m_radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//����������������������������������������������
// �ۂ��o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̊ۂ��o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool CircleBoundingBox::Collision(const CircleBoundingBox* _target)const
{
	// ��̍��W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - _target->GetPos().x, m_pos.y - _target->GetPos().y };
	
	return (sqrtf(relativePos.x * relativePos.x + relativePos.y * relativePos.y) <= 
			(m_radius + _target->GetRadius())/* * (m_radius + _target->GetRadius())*/);
}

//����������������������������������������������
// �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̎l�p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool CircleBoundingBox::Collision(const RectangleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + targetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < targetPos.x - targetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > targetPos.y + targetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < targetPos.y - targetSize.y / 2.f - m_radius)return false;

	// ���W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - targetPos.x, m_pos.y - targetPos.y };

	if (Abs(relativePos.x) <= targetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= targetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - targetSize.x / 2.f, Abs(relativePos.y) - targetSize.y };

	if (pos.x * pos.x + pos.y * pos.y <= m_radius * m_radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//����������������������������������������������
// ���p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̑��p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool CircleBoundingBox::Collision(const PolygonBoundingBox* _target)const
{
	return false;
}