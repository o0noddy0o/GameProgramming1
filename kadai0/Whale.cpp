//����������������������������������������������
// �t�@�C�����@�@�FWhale.cpp
// �T�v�@�@�@�@�@�F�N�W���i�X�e�[�W�P�̃{�X�j�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/01/17 �쐬
//����������������������������������������������
#include "Whale.h"
#include "MissileLauncher.h"
#include "GameResource.h"
#include "EnemyBullet.h"
#include "Fire.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�������W
//����������������������������������������������
Whale::Whale(GameInfo* _pGameInfo, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_pMissileLauncher(NULL)
	, m_pos(_pos)
{
	// ������
	m_nowAction = ActionPattern::none;

	// �N�W���{�̂̉摜���쐬
	m_pImg.push_back(CreateSprite(Tex_Whale, WHALE_SIZE_X, WHALE_SIZE_Y));
	m_pImg[0]->setPos(_pos);

	// �N�W���ɏ悹��~�T�C�����ˋ@���쐬
	XMFLOAT2 missileLauncherPos = _pos;
	missileLauncherPos.x += WHALE_MISSILELAUNCHER_RELATIVE_POS_X;
missileLauncherPos.y += WHALE_MISSILELAUNCHER_RELATIVE_POS_Y;
m_pMissileLauncher = new MissileLauncher(m_pGameInfo, missileLauncherPos);
}

//����������������������������������������������
//����������������������������������������������
Whale::~Whale()
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)
	{
		DisposeSprite(m_pImg[i]);
	}
	if (m_pMissileLauncher)delete (m_pMissileLauncher);
}

//����������������������������������������������
// �s���p�^�[�������߂�
//����������������������������������������������
void Whale::DecideActionPattern(XMFLOAT2 _SubmarinePos)
{
	// �J�E���^�[�����Z�b�g����
	m_actionTimeCnt = 0;

	// �N�W����������͂܂ł̃x�N�g�������
	XMFLOAT2 vectorToSubmarine = FindVectorByTwoPos(m_pos, _SubmarinePos);

	// �����p�^�[�����J��Ԃ��Ȃ��悤��
	if (rand() % 2)
	{
		// �N�W�����΂𐁂��Ƃ��납������͂܂ł̃x�N�g�������A���K������
		XMFLOAT2 vector = WHALE_PATTERN1_BIOW_FIRE_POS;
		vector.x = _SubmarinePos.x - (vector.x + m_pos.x);
		vector.y = _SubmarinePos.y - (vector.y + m_pos.y);
		
		// �����͂������x�߂Â��Ă���
		if (FindDistanceByCoordinateDifference(vector) < WHALE_PATTERN1_BIOW_FIRE_DISTANCE)
		{
			// �N�W�����΂𐁂���p�x��cos���v�Z���Ă����i���ςŎg���j
			static float cosBiowFireAngle = cosf(WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f);

			NormalizeVector(vector);

			// �����͂��͈͂ɓ����Ă���
			if (vector.x * -1.f > cosBiowFireAngle)
			{
				m_nowAction = ActionPattern::biowFire;
				return;
			}
		}
	}
	else
	{
		// �����͂������x�߂Â��Ă���
		if (Abs(vectorToSubmarine.x) < WHALE_PATTERN2_DASH_DISTANCE)
		{
			m_nowAction = ActionPattern::dash;
			return;
		}
	}

	// �c��̓����_����
	m_nowAction = ActionPattern(rand() % (ActionPattern::Total - 3) + 3);
}

//����������������������������������������������
// ���t���[���̏���
//����������������������������������������������
void Whale::Tick(XMFLOAT2 _SubmarinePos)
{
	if (m_nowAction == ActionPattern::none)
	{
		DecideActionPattern(_SubmarinePos);
	}
	switch (m_nowAction)
	{
	case ActionPattern::biowFire:		BiowFireProcess(_SubmarinePos);		break;
	case ActionPattern::dash:			DashProcess();						break;
	case ActionPattern::laser:			LaserProcess();						break;
	case ActionPattern::summonEnemy:	SummonEnemyProcess();				break;
	}
}

//����������������������������������������������
// �摜�̕`��
//����������������������������������������������
void Whale::renderSprite()
{
	if (m_pMissileLauncher)m_pMissileLauncher->renderSprite();
	Super::renderSprite();
}

//����������������������������������������������
// �΂𕬂����̏���
// �����P�F�����͂̍��W
//����������������������������������������������
void Whale::BiowFireProcess(XMFLOAT2 _SubmarinePos)
{
	if (m_actionTimeCnt++ > WHALE_PATTERN1_DURATION_TIME)
	{
		m_actionTimeCnt = 0;
		m_nowAction = ActionPattern::none;
		return;
	}

	// �e�𐶐�������W���v�Z
	XMFLOAT2 pos = WHALE_PATTERN1_BIOW_FIRE_POS;
	pos.x += m_pos.x;
	pos.y += m_pos.y;

	// �N�W�����΂𐁂���p�x��cos���v�Z���Ă����i���ςŎg���j
	static float cosBiowFireAngle = cosf(WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f);

	// �N�W���̌���������͂܂ł̃x�N�g�����v�Z���Ă���
	XMFLOAT2 vector = FindVectorByTwoPos(pos, _SubmarinePos);
	NormalizeVector(vector);
	
	bool bOverRange = false;
	float angle;
	if (vector.x * -1.f < cosBiowFireAngle)
	{
		bOverRange = true;
		if (vector.y > 0.f)
		{
			angle = 180.f - WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
		}
		else
		{
			angle = 180.f + WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
		}
	}

	// �g����I�u�W�F�N�g��T��
	for (int i = 0; i < (int)m_pBullet->size(); ++i)
	{
		if ((*m_pBullet)[i]->GetBulletType() == TypeOfEnemyBullet::fire)
		{
			if (!(*m_pBullet)[i]->GetActive())
			{
				(*m_pBullet)[i]->SetPos(pos);
				if (bOverRange)
				{
					(*m_pBullet)[i]->SetMoveDirection(angle);
				}
				else
				{
					(*m_pBullet)[i]->SetMoveDirection(vector);
				}
				(*m_pBullet)[i]->SetActive(true);
				((Fire*)(*m_pBullet)[i].get())->SetDisappearTime(FIRE_DISAPPEAR_TIME);
				return;
			}
		}
	}
	// �����Ȃ�������A�V�����̂����
	if (bOverRange)
	{
		m_pBullet->push_back((shared_ptr<EnemyBullet>)new Fire(m_pGameInfo, pos, vector, FIRE_DISAPPEAR_TIME));
		m_pBullet->back()->SetMoveDirection(angle);
	}
	else
	{
		m_pBullet->push_back((shared_ptr<EnemyBullet>)new Fire(m_pGameInfo, pos, vector, FIRE_DISAPPEAR_TIME));
	}
}

//����������������������������������������������
// ���[�U�[��ł��̏���
//����������������������������������������������
void Whale::LaserProcess()
{
	m_nowAction = ActionPattern::none;
}

//����������������������������������������������
// �_�b�V������Ƃ��̏���
//����������������������������������������������
void Whale::DashProcess()
{
	m_nowAction = ActionPattern::none;
}

//����������������������������������������������
// �G����������Ƃ��̏���
//����������������������������������������������
void Whale::SummonEnemyProcess()
{
	m_nowAction = ActionPattern::none;
}