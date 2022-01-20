//����������������������������������������������
// �t�@�C�����@�@�FMissileLauncher.cpp
// �T�v�@�@�@�@�@�F�~�T�C�����ˋ@�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/14 �쐬�i���j
//����������������������������������������������
#include "MissileLauncher.h"
#include "GameResource.h"
#include "Missile.h"
#include "CircleBoundingBox.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F����̍��W
// �����R�F����̊p�x
//����������������������������������������������
MissileLauncher::MissileLauncher(GameInfo* _pGameInfo, XMFLOAT2 _pedestalPos, float _pedestalAngle)
	: Super(_pGameInfo)
	, m_angle(_pedestalAngle)
	, m_coolDownCnt(0)
	, m_coolDown(rand() % 60 + MISSILELAUNCHER_MIN_ATTACK_INTERVAL)
{
	// ���̕����Ƒ���̕����𕪂��č쐬����
	m_pImg = CreateSprite(Tex_MissileLauncherHead, MISSILELAUNCHER_HEAD_SIZE_X, MISSILELAUNCHER_HEAD_SIZE_Y);
	m_pImg2 = CreateSprite(Tex_MissileLauncherPedestal, MISSILELAUNCHER_PEDESTAL_SIZE_X, MISSILELAUNCHER_PEDESTAL_SIZE_Y);
	
	// ����̕�����ݒu
	m_pImg2->setPos(_pedestalPos);
	m_pImg2->addAngleZ(_pedestalAngle);

	// ���̕�����ݒu
	XMFLOAT2 headPos = AngleToDirectionVector(_pedestalAngle + 90.f);
	headPos.x *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.y *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.x += _pedestalPos.x;
	headPos.y += _pedestalPos.y;
	m_pImg->setPos(headPos);
	m_pImg->addAngleZ(_pedestalAngle);

	// �o�E���f�B���O�{�b�N�X���쐬
	XMFLOAT2 boundingBoxPos = AngleToDirectionVector(_pedestalAngle + 90.f);
	float d = (MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f + MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL + MISSILELAUNCHER_HEAD_SIZE_Y / 2.f) / 2.f - MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f;
	boundingBoxPos.x *= d;
	boundingBoxPos.y *= d;
	boundingBoxPos.x += _pedestalPos.x;
	boundingBoxPos.y += _pedestalPos.y;
	m_pBoundingBox = new CircleBoundingBox(boundingBoxPos, d - MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
MissileLauncher::~MissileLauncher()
{
	if (m_pImg)delete m_pImg;
	m_pImg = NULL;
	delete m_pImg2;
	delete m_pBoundingBox;
}

//����������������������������������������������
// �摜��`�悷��
//����������������������������������������������
void MissileLauncher::renderSprite()
{
	RenderSprite(m_pImg);
	RenderSprite(m_pImg2);
}

//����������������������������������������������
// �G�l�~�[�̍U��
//����������������������������������������������
void MissileLauncher::AttackProcess(XMFLOAT2 _SubmarinePos)
{
	// �e��ł��x�̐���
	if (m_coolDownCnt < m_coolDown)
	{
		++m_coolDownCnt;
	}
	else
	{
		m_coolDown = rand() % 60 + MISSILELAUNCHER_MIN_ATTACK_INTERVAL;
		// �J�E���^�[�����Z�b�g����
		m_coolDownCnt = 0;

		// �e�̍��W���v�Z
		XMFLOAT4 pos = m_pImg->getPos();
		{
			XMFLOAT2 pos2 = AngleToDirectionVector(m_angle - 180.f);
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
						m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new Missile(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle - 180.f)));
						break;
					}
				}
				else
				{
					if ((*m_pEnemyBullet)[i]->GetBulletType() == missile)
					{
						// �������炻����g��
						(*m_pEnemyBullet)[i]->SetActive(true);
						(*m_pEnemyBullet)[i]->SetPos(XMFLOAT2(pos.x, pos.y));
						(*m_pEnemyBullet)[i]->SetMoveDirection(m_angle - 180.f);
						break;
					}
				}
			}
		}
		else
		{
			m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new Missile(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle - 180.f)));
		}
	}
}

//����������������������������������������������
// �G�l�~�[�̈ړ��i���̃G�l�~�[�͈ړ����Ȃ����߁A��]�̂݁j
// �����P�F�����͂̍��W
//����������������������������������������������
void MissileLauncher::MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime)
{
	// �~�T�C�����ˋ@�̓��̕����̉�]
	{
		// �������Ă�������̃x�N�g�����擾
		XMFLOAT2 vector = AngleToDirectionVector(m_angle);

		// �~�T�C�����ˋ@�̓��̕�����������͂܂ł̃x�N�g�������A���K������
		XMFLOAT2 vector2 = FindVectorByTwoPos(_SubmarinePos, m_pImg2->getPos());
		NormalizeVector(vector2);

		// ���̕����̉�]
		if (CrossProduct(vector, vector2) > 0.f)
		{
			float angle = Degree(RadianToDegree(acosf(vector.x * vector2.x + vector.y * vector2.y)));
			if (Abs(angle) > MISSILELAUNCHER_MAX_ROTATE_SPEED)
			{
				m_angle += MISSILELAUNCHER_MAX_ROTATE_SPEED;
			}
			else
			{
				m_angle += angle;
			}
		}
		else
		{
			float angle = Degree(RadianToDegree(acosf(vector.x * vector2.x + vector.y * vector2.y)));
			if (Abs(angle) > MISSILELAUNCHER_MAX_ROTATE_SPEED)
			{
				m_angle -= MISSILELAUNCHER_MAX_ROTATE_SPEED;
			}
			else
			{
				m_angle -= angle;
			}
		}
	}
	// ���̕����̏㉺���]
	{
		// ������瓪�܂ł̃x�N�g�������A���K������
		XMFLOAT2 vector = FindVectorByTwoPos(m_pImg2->getPos(), m_pImg->getPos());
		NormalizeVector(vector);

		// �������Ă�������̃x�N�g�����擾
		XMFLOAT2 vector2 = AngleToDirectionVector(m_angle);

		if (CrossProduct(vector, vector2) > 0.f)
		{
			// ����������A�摜�̂x���̉�]���P�W�O���ɂ���
			m_pImg->setAngle(0.f, 0.f, m_angle + 180.f);
		}
		else
		{
			// �E��������A�摜�̂x���̉�]���O���ɂ���
			m_pImg->setAngle(0.f, 180.f, m_angle);
		}
	}
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X���擾
//����������������������������������������������
BoundingBox* MissileLauncher::GetBoundingBox()const
{
	return m_pBoundingBox;
}

void MissileLauncher::SetPosAndAngle(XMFLOAT2 _newPos, float _newAngle)
{
	m_pImg2->setPos(_newPos);
	m_pImg2->setAngleZ(_newAngle);
	
	XMFLOAT2 headPos = AngleToDirectionVector(_newAngle + 90.f);
	headPos.x *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.y *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.x += _newPos.x;
	headPos.y += _newPos.y;
	m_pImg->setPos(headPos);

	XMFLOAT2 boundingBoxPos = AngleToDirectionVector(_newAngle + 90.f);
	float d = (MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f + MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL + MISSILELAUNCHER_HEAD_SIZE_Y / 2.f) / 2.f - MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f;
	boundingBoxPos.x *= d;
	boundingBoxPos.y *= d;
	boundingBoxPos.x += _newPos.x;
	boundingBoxPos.y += _newPos.y;
	m_pBoundingBox->SetPos(boundingBoxPos);
}