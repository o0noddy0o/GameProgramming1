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
#include "Fish.h"
#include "Fish2.h"
#include "RectangleBoundingBox.h"
#include "Laser.h"
#include "CameraManager.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�������W
// �����R�F�G�̔z��
//����������������������������������������������
Whale::Whale(GameInfo* _pGameInfo, XMFLOAT2 _pos, vector<shared_ptr<Enemy>>* _pEnemy)
	: Super(_pGameInfo)
	, m_pMissileLauncher(NULL)
	, m_pos(_pos)
	, m_cooldown(1 * 60)
	, pEnemy(_pEnemy)
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

	m_hpBarRelativePos = WHALE_HP_BAR_RELATIVE_POS;
	m_hp = WHALE_MAX_HP;
	m_maxHp = WHALE_MAX_HP;
	m_hpBarSize = XMFLOAT2(WHALE_HP_BAR_SIZE_X, WHALE_HP_BAR_SIZE_Y);

	m_pBoundingBox.push_back(new RectangleBoundingBox(_pos, XMFLOAT2(WHALE_SIZE_X, WHALE_SIZE_Y)));

	m_pHpBar = CreateSprite(Tex_HPBar, WHALE_HP_BAR_SIZE_X, WHALE_HP_BAR_SIZE_Y);
	m_pFreamOfHpBar = CreateSprite(Tex_HPBarFream, WHALE_HP_BAR_FREAM_SIZE_X, WHALE_HP_BAR_FREAM_SIZE_Y);
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();

	m_pHpBar->setPos(cameraPos.x + WHALE_HP_BAR_RELATIVE_POS_X, cameraPos.y + WHALE_HP_BAR_RELATIVE_POS_Y);
	m_pFreamOfHpBar->setPos(cameraPos.x + WHALE_HP_BAR_RELATIVE_POS_X, cameraPos.y + WHALE_HP_BAR_RELATIVE_POS_Y);
}

//����������������������������������������������
// �f�X�g���N�^
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
	// �N�[���_�E�����I����Ă���A���̍s�������߂�
	if (m_cooldown-- > 0)return;

	// �J�E���^�[�����Z�b�g����
	m_actionTimeCnt = 0;

	// �N�W����������͂܂ł̃x�N�g�������
	XMFLOAT2 vectorToSubmarine = FindVectorByTwoPos(m_pos, _SubmarinePos);

	// �����p�^�[�����J��Ԃ��Ȃ��悤��
	if (rand() % 5 > 1)
	{
		// �N�W�����΂𐁂��Ƃ��납������͂܂ł̃x�N�g�������A���K������
		XMFLOAT2 vector = WAHLE_RELATIVE_POS_OF_MOUTH;
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
		if (Abs(vectorToSubmarine.x) < WHALE_PATTERN2_DASH_DISTANCE * 1.75f)
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
void Whale::Tick(XMFLOAT2 _SubmarinePos, float _deltaTime)
{
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();
	m_pHpBar->setPos(cameraPos.x + m_hpBarRelativePos.x, cameraPos.y + m_hpBarRelativePos.y);
	m_pFreamOfHpBar->setPos(cameraPos.x + WHALE_HP_BAR_RELATIVE_POS_X, cameraPos.y + WHALE_HP_BAR_RELATIVE_POS_Y);

	m_pMissileLauncher->AttackProcess(_SubmarinePos);
	m_pMissileLauncher->MoveProcess(_SubmarinePos, _deltaTime);
	if (m_nowAction == ActionPattern::none)
	{
		DecideActionPattern(_SubmarinePos);
	}

	switch (m_nowAction)
	{
	case ActionPattern::none:												break;
	case ActionPattern::biowFire:		BiowFireProcess(_SubmarinePos);		break;
	case ActionPattern::dash:			DashProcess();						break;
	case ActionPattern::laser:			LaserProcess(_SubmarinePos);		break;
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
		m_cooldown = WHALE_COUNTDOWN_BETWEEN_ACTION;
		m_nowAction = ActionPattern::none;
		return;
	}

	// �e�𐶐�������W���v�Z
	XMFLOAT2 pos = WAHLE_RELATIVE_POS_OF_MOUTH;
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
// �_�b�V������Ƃ��̏���
//����������������������������������������������
void Whale::DashProcess()
{
	if (m_actionTimeCnt++ > WHALE_PATTERN2_DURATION_TIME)
	{
		m_actionTimeCnt = 0;
		m_cooldown = WHALE_COUNTDOWN_BETWEEN_ACTION;
		m_nowAction = ActionPattern::none;
	}
	if (m_actionTimeCnt < WHALE_PATTERN2_DURATION_TIME * 2 / 5)
	{
		XMFLOAT2 newPos = { m_pImg[0]->getPos().x + WHALE_PATTERN2_DASH_DISTANCE / 4.f / float(WHALE_PATTERN2_DURATION_TIME * 2 / 5), m_pImg[0]->getPos().y };
		this->SetPos(newPos);
	}
	else if(m_actionTimeCnt < WHALE_PATTERN2_DURATION_TIME * 3 / 5)
	{
		XMFLOAT2 newPos = { m_pImg[0]->getPos().x - WHALE_PATTERN2_DASH_DISTANCE * 1.25f / float(WHALE_PATTERN2_DURATION_TIME * 1 / 5), m_pImg[0]->getPos().y };
		this->SetPos(newPos);
	}
	else
	{
		XMFLOAT2 newPos = { m_pImg[0]->getPos().x + WHALE_PATTERN2_DASH_DISTANCE / float(WHALE_PATTERN2_DURATION_TIME * 2 / 5), m_pImg[0]->getPos().y };
		this->SetPos(newPos);
	}
}

//����������������������������������������������
// ���[�U�[��ł��̏���
//����������������������������������������������
void Whale::LaserProcess(XMFLOAT2 _SubmarinePos)
{
	if (m_actionTimeCnt == 0)
	{
		m_bLaserStartFromDown = _SubmarinePos.y > m_pos.y;
	}
	if (m_actionTimeCnt++ > WHALE_PATTERN3_DURATION_TIME)
	{
		m_actionTimeCnt = 0;
		m_cooldown = WHALE_COUNTDOWN_BETWEEN_ACTION;
		m_nowAction = ActionPattern::none;
		for (int i = 0; i < (int)m_pBullet->size(); ++i)
		{
			// �������炻�̗v�f�ԍ���ۑ�����
			if ((*m_pBullet)[i]->GetBulletType() == TypeOfEnemyBullet::laser)
			{
				(*m_pBullet)[i]->SetActive(false);
				break;
			}
		}
		return;
	}
	
	// �����̒e�̔z��̒��Ƀ��[�U�[�����邩���`�F�b�N
	int index = -1;
	for (int i = 0; i < (int)m_pBullet->size(); ++i)
	{
		// �������炻�̗v�f�ԍ���ۑ�����
		if ((*m_pBullet)[i]->GetBulletType() == TypeOfEnemyBullet::laser)
		{
			index = i;
			XMFLOAT2 pos = WAHLE_RELATIVE_POS_OF_MOUTH;
			pos.x += m_pos.x;
			pos.y += m_pos.y;
			(*m_pBullet)[i]->SetPos(pos);
			(*m_pBullet)[i]->SetActive(true);
			break;
		}
	}

	// �Ȃ�������V�����̂����
	if (index == -1)
	{
		XMFLOAT2 pos = WAHLE_RELATIVE_POS_OF_MOUTH;
		pos.x += m_pos.x;
		pos.y += m_pos.y;
		m_pBullet->push_back((shared_ptr<EnemyBullet>)new Laser(m_pGameInfo, WHALE_PATTERN3_LASER_SIZE, pos, WHALE_PATTERN3_LASER_START_ANGLE));
		index = (int)m_pBullet->size() - 1;
	}

	float angle;
	if (m_bLaserStartFromDown)
	{
		angle = WHALE_PATTERN3_LASER_START_ANGLE + m_actionTimeCnt * (WHALE_PATTERN3_LASER_END_ANGLE - WHALE_PATTERN3_LASER_START_ANGLE) / WHALE_PATTERN3_DURATION_TIME;
	}
	else
	{
		angle = WHALE_PATTERN3_LASER_END_ANGLE + m_actionTimeCnt * (WHALE_PATTERN3_LASER_START_ANGLE - WHALE_PATTERN3_LASER_END_ANGLE) / WHALE_PATTERN3_DURATION_TIME;
	}

//#if DEBUG
//	XMFLOAT2 mousePos = GetInput()->getMousePos();
//	if (!SchoolPC)
//	{
//		mousePos.x = (mousePos.x + 960.f) / 1440.f * 1920.f - 960.f;
//		mousePos.y = (mousePos.y - 540.f) / 900.f * 1080.f + 540.f;
//	}
//	XMFLOAT2 pos = WAHLE_RELATIVE_POS_OF_MOUTH;
//	pos.x += m_pos.x;
//	pos.y += m_pos.y;
//	XMFLOAT2 vector = FindVectorByTwoPos(pos, mousePos);
//	angle = DirectionVectorToAngle(vector);
//	if (vector.x < 0.f)angle += 180.f;
//#endif

	((Laser*)((*m_pBullet)[index].get()))->SetAngle(Degree(angle));
}

//����������������������������������������������
// �G����������Ƃ��̏���
//����������������������������������������������
void Whale::SummonEnemyProcess()
{
	if (pEnemy->size() > WHALE_PATTERN4_SUMMON_ENEMY_NUM / 5 * 2)
	{
		m_nowAction = ActionPattern::none;
		return;
	}

	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();
	for (int i = 0; i < WHALE_PATTERN4_SUMMON_ENEMY_NUM; ++i)
	{
		if (rand() % 2)
		{
			//pEnemy->push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1))), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 5.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
			pEnemy->push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f)), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 3.f)) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
		}
		else
		{
			//pEnemy->push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1))), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 5.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
			pEnemy->push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f)), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 3.f)) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
		}
	}

	m_actionTimeCnt = 0;
	m_cooldown = WHALE_COOLDOWN_AFTER_PATTERN4;
	m_nowAction = ActionPattern::none;
}

//����������������������������������������������
// �N�W���̍��W��ݒu����
//����������������������������������������������
void Whale::SetPos(XMFLOAT2 _newPos)
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)m_pImg[i]->setPos(_newPos);
	XMFLOAT2 pos = { WHALE_MISSILELAUNCHER_RELATIVE_POS_X, WHALE_MISSILELAUNCHER_RELATIVE_POS_Y };
	pos.x += _newPos.x;
	pos.y += _newPos.y;
	m_pMissileLauncher->SetPosAndAngle(pos, 0.f);
	for (int i = 0; i < (int)m_pBoundingBox.size(); ++i)m_pBoundingBox[i]->SetPos(_newPos);
	m_pos = _newPos;
}

void Whale::GetDamege(int _damage)
{
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();
	m_hp -= _damage;
	float percents = (float)m_hp / (float)m_maxHp;
	if (m_hp < 0.f)throw (string)"GameClear";

	m_hpBarRelativePos.x = WHALE_HP_BAR_RELATIVE_POS_X - m_hpBarSize.x / 2.f + m_hpBarSize.x * percents / 2.f;

	m_pHpBar->setScale(percents, 1.f);
	m_pHpBar->setPos(cameraPos.x + m_hpBarRelativePos.x , cameraPos.y + m_hpBarRelativePos.y);
}