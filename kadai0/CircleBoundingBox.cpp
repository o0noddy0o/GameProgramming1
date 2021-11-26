//����������������������������������������������
// �t�@�C�����@�@�FCircleBoundingBox.cpp
// �T�v�@�@�@�@�@�F�ۂ��o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#include "CircleBoundingBox.h"
#include "Define.h"
#include "CPicture.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�o�E���f�B���O�{�b�N�X�̒��S���W
// �����Q�F�o�E���f�B���O�{�b�N�X�̔��a
//����������������������������������������������
CircleBoundingBox::CircleBoundingBox(XMFLOAT2 _pos, float _radius)
	: m_pos(_pos)
	, m_radius(_radius)
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
// �摜�Ƃ̓����蔻��
// �����P�F�Ώۂ̉摜
//����������������������������������������������
bool CircleBoundingBox::Collision(CPicture* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 tagetSize = _target->getSize();
	XMFLOAT4 tagetPos = _target->getPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > tagetPos.x + tagetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < tagetPos.x - tagetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > tagetPos.y + tagetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < tagetPos.y - tagetSize.y / 2.f - m_radius)return false;

	// ���W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - tagetPos.x, m_pos.y - tagetPos.y };

	if (Abs(relativePos.x) <= tagetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= tagetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - tagetSize.x / 2.f, Abs(relativePos.y) - tagetSize.y };

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
bool CircleBoundingBox::Collision(CircleBoundingBox* _target)const
{
	// ��̍��W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - _target->GetPos().x, m_pos.y - _target->GetPos().y };
	
	return (relativePos.x * relativePos.x + relativePos.y * relativePos.y <= 
			(m_radius + _target->GetRadius()) * (m_radius + _target->GetRadius()));
}

//����������������������������������������������
// �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̎l�p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool CircleBoundingBox::Collision(RectangleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 tagetSize = _target->GetSize();
	XMFLOAT2 tagetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > tagetPos.x + tagetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < tagetPos.x - tagetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > tagetPos.y + tagetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < tagetPos.y - tagetSize.y / 2.f - m_radius)return false;

	// ���W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - tagetPos.x, m_pos.y - tagetPos.y };

	if (Abs(relativePos.x) <= tagetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= tagetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - tagetSize.x / 2.f, Abs(relativePos.y) - tagetSize.y };

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
bool CircleBoundingBox::Collision(PolygonBoundingBox* _target)const
{
	return false;
}