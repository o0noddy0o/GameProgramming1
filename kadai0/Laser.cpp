//����������������������������������������������
// �t�@�C�����@�@�FLaser.cpp
// �T�v�@�@�@�@�@�F���[�U�[�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/01/20 �쐬
//����������������������������������������������
#include "Laser.h"
#include "GameResource.h"
#include "Define.h"
#include "PolygonBoundingBox.h"


//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F���[�U�[�̃T�C�Y
// �����R�F���[�U�[�̎n�_���W�i���˓_�j
// �����S�F���[�U�[�̕���
// �����T�F���[�U�[�͑O�ֈړ����邩�ۂ�
//����������������������������������������������
Laser::Laser(GameInfo* _pGameInfo, XMFLOAT2 _size, XMFLOAT2 _startPointPos, float _angle, bool _bMove)
	: Super(_pGameInfo, TypeOfEnemyBullet::laser)
	, m_size(_size)
	, m_angle(Degree(_angle))
	, m_pos(_startPointPos)
	, m_bMove(_bMove)
{
	if (m_bulletType == TypeOfEnemyBullet::laser)
	{
		// ���[�U�[�̉摜���쐬���A�ݒu����
		m_pImg = CreateSprite(Tex_Laser, _size.x, _size.y);

		// ��]������
		m_pImg->setAngleZ(m_angle);

		// ���W���v�Z����
		{
			XMFLOAT2 vector = AngleToDirectionVector(m_angle);
			vector.x *= _size.x / 2.f;
			vector.y *= _size.x / 2.f;

			m_pImg->setPos(_startPointPos.x + vector.x, _startPointPos.y + vector.y);
		}

		vector<XMFLOAT2> vector =
		{
			{ _size.x / 2.f,  _size.y / 2.f},
			{ _size.x / 2.f, -_size.y / 2.f},
			{-_size.x / 2.f, -_size.y / 2.f},
			{-_size.x / 2.f,  _size.y / 2.f},
		};
		m_pBoundingBox = new PolygonBoundingBox(_startPointPos, vector, true, XMFLOAT2(_size.x / 2.f, 0.f));
		((PolygonBoundingBox*)m_pBoundingBox)->RotateVertex(m_angle);
	}
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Laser::~Laser()
{
}

//����������������������������������������������
// ���[�U�[�̎n�_���W���Z�b�g����
//����������������������������������������������
void Laser::SetPos(XMFLOAT2 _newStartPointPos)
{
	// �V�������W��ۑ����Ă���
	m_pos = _newStartPointPos;

	// �o�E���f�B���O�{�b�N�X��V�������W�ɐݒu����
	m_pBoundingBox->SetPos(_newStartPointPos);

	// �摜�̐V�������W���v�Z����
	XMFLOAT2 vector = AngleToDirectionVector(m_angle);
	vector.x *= m_size.x / 2.f;
	vector.y *= m_size.x / 2.f;

	// �摜��V�������W�ɐݒu����
	m_pImg->setPos(m_pos.x + vector.x, m_pos.y + vector.y);
}

//����������������������������������������������
// ���[�U�[�̕������Z�b�g����
//����������������������������������������������
void Laser::SetAngle(float _angle)
{
	// �o�E���f�B���O�{�b�N�X����]������
	((PolygonBoundingBox*)m_pBoundingBox)->RotateVertex(_angle - m_angle);

	// �V�����p�x��ۑ����Ă���
	m_angle = _angle;

	// �摜����]������
	m_pImg->setAngleZ(m_angle);

	// �摜�̐V�������W���v�Z����
	XMFLOAT2 vector = AngleToDirectionVector(m_angle);
	vector.x *= m_size.x / 2.f;
	vector.y *= m_size.x / 2.f;

	// �摜��V�������W�ɐݒu����
	m_pImg->setPos(m_pos.x + vector.x, m_pos.y + vector.y);
}

//����������������������������������������������
// ���[�U�[�̕��������Z����
//����������������������������������������������
void Laser::SetOffsetAngle(float _angle)
{
	// �o�E���f�B���O�{�b�N�X����]������
	((PolygonBoundingBox*)m_pBoundingBox)->RotateVertex(_angle);

	// �V�����p�x���v�Z���Ă���
	m_angle += _angle;

	// �摜����]������
	m_pImg->setAngleZ(m_angle);

	// �摜�̐V�������W���v�Z����
	XMFLOAT2 vector = AngleToDirectionVector(m_angle);
	vector.x *= m_size.x / 2.f;
	vector.y *= m_size.x / 2.f;

	// �摜��V�������W�ɐݒu����
	m_pImg->setPos(m_pos.x + vector.x, m_pos.y + vector.y);
}

void Laser::MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos)
{
	if (!m_bMove)return;
	Super::MoveProcess(_deltaTime, _SubmarinePos);
}