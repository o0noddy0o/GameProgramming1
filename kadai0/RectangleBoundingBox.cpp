//����������������������������������������������
// �t�@�C�����@�@�FRectangleBoundingBox.cpp
// �T�v�@�@�@�@�@�F�l�p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
// �@�@�@�@�@�@�@�F2021/11/27 �R���W�����̎���
//����������������������������������������������
#include "Define.h"
#include "CPicture.h"
#include "CircleBoundingBox.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�o�E���f�B���O�{�b�N�X�̒��S���W
// �����Q�F�o�E���f�B���O�{�b�N�X�̃T�C�Y
// �����R�F�o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
//����������������������������������������������
RectangleBoundingBox::RectangleBoundingBox(XMFLOAT2 _pos, XMFLOAT2 _size, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_size(_size)
	, m_relativePos(_relativePos)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
RectangleBoundingBox::~RectangleBoundingBox()
{
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W���擾
//����������������������������������������������
XMFLOAT2 RectangleBoundingBox::GetPos()const
{
	return m_pos;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̃T�C�Y���擾
//����������������������������������������������
XMFLOAT2 RectangleBoundingBox::GetSize()const
{
	return m_size;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W��ݒu����
// �����P�F���̃o�E���f�B���O�{�b�N�X�����I�u�W�F�N�g�̐V�������W
//����������������������������������������������
void RectangleBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̃T�C�Y��ς���
// �����P�F�V�������W
//����������������������������������������������
void RectangleBoundingBox::ChangeSize(XMFLOAT2 _newSize)
{
	m_size = _newSize;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W�Ƃ�������I�u�W�F�N�g�̍��W�̍���ς���
// �����P�F�V���������i���j
//����������������������������������������������
void RectangleBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//����������������������������������������������
// �摜�Ƃ̓����蔻��
// �����P�F�Ώۂ̉摜
//����������������������������������������������
bool RectangleBoundingBox::Collision(CPicture* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	return true;
}

//����������������������������������������������
// �ۂ��o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̊ۂ��o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool RectangleBoundingBox::Collision(const CircleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	float targetRadius = _target->GetRadius();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + m_size.x / 2.f + targetRadius)return false;
	if (m_pos.x < targetPos.x - m_size.x / 2.f - targetRadius)return false;
	if (m_pos.y > targetPos.y + m_size.y / 2.f + targetRadius)return false;
	if (m_pos.y < targetPos.y - m_size.y / 2.f - targetRadius)return false;

	// ���W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - targetPos.x, m_pos.y - targetPos.y };

	if (Abs(relativePos.x) <= targetRadius)return true;
	if (Abs(relativePos.y) <= targetRadius)return true;

	//float r = sqrtf(m_size.x / 2.f * m_size.x / 2.f + m_size.x / 2.f * m_size.x / 2.f) + targetRadius;
	//float r2 = sqrtf(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
	//XMFLOAT2 pos = { Abs(relativePos.x) - (targetRadius/* + m_size.x / 2.f*/), Abs(relativePos.y) - (targetRadius/* + m_size.y / 2.f*/) };
	//if (pos.x <= 0.f && pos.y <= 0.f)return true;
	//if(r2 < r)return true;

	float d = sqrtf(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
	XMFLOAT2 pos = { relativePos.x / d * targetRadius - m_size.x / 2.f, relativePos.y / d * targetRadius - m_size.y / 2.f };
	if (pos.x < 0.f && pos.y < 0.f)return true;

	return false;
}

//����������������������������������������������
// �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̎l�p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool RectangleBoundingBox::Collision(const RectangleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	return true;
}

//����������������������������������������������
// ���p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̑��p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool RectangleBoundingBox::Collision(const PolygonBoundingBox* _target)const
{
	return false;
}