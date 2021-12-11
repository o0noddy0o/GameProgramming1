//����������������������������������������������
// �t�@�C�����@�@�FFish.h
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//			�@�@�@2021/12/08�@�G�̒e�𔭎ˋ@�\��ǉ�
//			�@�@�@2021/12/10�@�G�̈ړ�������ǉ�
//����������������������������������������������
#include "Define.h"
#include "Fish.h"
#include "EnemyBullet.h"
#include "GameResource.h"
#include "RectangleBoundingBox.h"
#include <time.h>

// ����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�G�̏������W
//����������������������������������������������
Fish::Fish(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Enemy(_pGameInfo)
	, m_coolDownCnt(0)
	, m_angle(_angle)
{
	m_pImg = CreateSprite(Tex_Enemy, ENEMY_1_SIZE_X, ENEMY_1_SIZE_Y);
	m_pImg->setAngle(0.f, 180.f, _angle);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, XMFLOAT2(ENEMY_1_SIZE_X, ENEMY_1_SIZE_Y));
	m_pEnemyBullet = (shared_ptr<vector<shared_ptr<EnemyBullet>>>)new vector<shared_ptr<EnemyBullet>>;
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Fish::~Fish()
{
	delete m_pBoundingBox;
}

//����������������������������������������������
// �U���̏���
//����������������������������������������������
void Fish::AttackProcess()
{
	static int coolDown = rand() % 60;

	// �e��ł��x�̐���
	if (m_coolDownCnt < coolDown)
	{
		++m_coolDownCnt;
	}
	else
	{
		coolDown = rand() % 60;
		// �J�E���^�[�����Z�b�g����
		m_coolDownCnt = 0;

		// �e�̍��W���v�Z
		XMFLOAT4 pos = m_pImg->getPos();
		{
			XMFLOAT2 pos2 = AngleToDirectionVector(m_angle);
			pos.x += pos2.x * (ENEMY_1_SIZE_X / 2.f) + pos2.x * 10.f;
			pos.y += pos2.y * (ENEMY_1_SIZE_X / 2.f) + pos2.y * 10.f;
		}

		// �g����e��T��
		if (m_pEnemyBullet->size() >= 1)
		{
			for (unsigned int i = 0; i < m_pEnemyBullet->size(); ++i)
			{
				if ((*m_pEnemyBullet)[i]->GetActive())
				{
					// �Ȃ�������V�����̂����
					if (i >= m_pEnemyBullet->size() - 1)
					{
						m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new EnemyBullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
						break;
					}
				}
				else
				{
					// �������炻����g��
					(*m_pEnemyBullet)[i]->SetActive(true);
					(*m_pEnemyBullet)[i]->SetPos(XMFLOAT2(pos.x, pos.y));
					(*m_pEnemyBullet)[i]->SetMoveDirection(m_angle);
					break;
				}
			}
		}
		else
		{
			m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new EnemyBullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
		}
	}
}

//����������������������������������������������
// �ړ�����
//����������������������������������������������
void Fish::MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime)
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
	XMFLOAT4 EnemyMove = { EnemyMoveDir.x * ENEMY_1_MOVE_SPEED * _deltaTime, EnemyMoveDir.y * ENEMY_1_MOVE_SPEED * _deltaTime, 0.f, 0.f };
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
BoundingBox* Fish::GetBoundingBox()const
{
	return m_pBoundingBox;
}