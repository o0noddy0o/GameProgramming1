//����������������������������������������������
// �t�@�C�����@�@�FFish2.h
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//			�@�@�@2021/12/08�@�G�̒e�𔭎ˋ@�\��ǉ�
//			�@�@�@2021/12/10�@�G�̈ړ�������ǉ�
//����������������������������������������������
#include "Define.h"
#include "Fish2.h"
#include "EnemyBullet.h"
#include "GameResource.h"
#include "RectangleBoundingBox.h"

// ����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�G�̏������W
//����������������������������������������������
Fish2::Fish2(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Enemy(_pGameInfo)
	, m_coolDownCnt(0)
	, m_angle(_angle)
{
	m_pImg = CreateSprite(Tex_Enemy2, ENEMY_2_SIZE_X, ENEMY_2_SIZE_Y);
	m_pImg->setAngle(0.f, 180.f, _angle);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, XMFLOAT2(ENEMY_2_SIZE_X, ENEMY_2_SIZE_Y));
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Fish2::~Fish2()
{
	delete m_pBoundingBox;
}

//����������������������������������������������
// �U���̏���
//����������������������������������������������
void Fish2::AttackProcess(XMFLOAT2 _SubmarinePos)
{
}

//����������������������������������������������
// �ړ�����
//����������������������������������������������
void Fish2::MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime)
{
	// �G�̍��W���擾
	XMFLOAT4 _EnemyPos = m_pImg->getPos();
	float diffX = _SubmarinePos.x - _EnemyPos.x;
	float diffY = _SubmarinePos.y - _EnemyPos.y;
	float mag = sqrtf(diffX * diffX + diffY * diffY);
	// �G��������͂ւ̕���
	XMFLOAT2 target;
	target.x = diffX / mag;
	target.y = diffY / mag;

	XMFLOAT2 EnemyMoveDir = AngleToDirectionVector(m_angle);

	// �O�ς̌v�Z
	float cross = (EnemyMoveDir.x * target.y - EnemyMoveDir.y * target.x);

	if (cross >= 0)
	{
		m_angle += 200.f * _deltaTime;
	}
	else
	{
		m_angle -= 200.f * _deltaTime;
	}

	// �G�̈ړ������̐ݒ�
	EnemyMoveDir = AngleToDirectionVector(m_angle);
	XMFLOAT4 EnemyMove = { EnemyMoveDir.x * ENEMY_2_MOVE_SPEED * _deltaTime, EnemyMoveDir.y * ENEMY_2_MOVE_SPEED * _deltaTime, 0.f, 0.f };
	m_pImg->offsetPos(EnemyMove);
	{
		// �G�̌����̐ݒ�
		int angle = Abs((int)m_angle % 360);
		if (angle < 90 || angle > 270)
		{
			m_pImg->setAngle(0.f, 180.f, m_angle);
		}
		else
		{
			m_pImg->setAngle(180.f, 180.f, m_angle);
		}}
	m_pImg->setAngleZ(m_angle);
	m_pBoundingBox->SetPos({ m_pImg->getPos().x, m_pImg->getPos().y });
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̎擾
//����������������������������������������������
BoundingBox* Fish2::GetBoundingBox()const
{
	return m_pBoundingBox;
}