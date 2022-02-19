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
#include "PolygonBoundingBox.h"
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
	, m_cooldown(2 * 60)
	, pEnemy(_pEnemy)
	, m_bFacingRight(false)
{
	// ������
	m_nowAction = ActionPattern::none;
	m_lastTimeAction = ActionPattern::none;

	// �N�W���{�̂̉摜���쐬
	m_pImg.push_back(CreateSprite(Tex_Whale, WHALE_SIZE_X, WHALE_SIZE_Y));
	m_pImg.back()->setPos(_pos);
	m_pImg.push_back(CreateSprite(Tex_WhaleTooth, WHALE_TOOTH_SIZE_X, WHALE_TOOTH_SIZE_Y, kTexelWhaleTooth));
	m_pImg.back()->setPos(_pos.x + WHALE_TOOTH_RELATIVE_POS_X, _pos.y + WHALE_TOOTH_RELATIVE_POS_Y);

	// �N�W���ɏ悹��~�T�C�����ˋ@���쐬
	XMFLOAT2 missileLauncherPos = _pos;
	missileLauncherPos.x += WHALE_MISSILELAUNCHER_RELATIVE_POS_X;
	missileLauncherPos.y += WHALE_MISSILELAUNCHER_RELATIVE_POS_Y;
	m_pMissileLauncher = new MissileLauncher(m_pGameInfo, missileLauncherPos);

	m_hpBarRelativePos = WHALE_HP_BAR_RELATIVE_POS;
	m_hp = WHALE_MAX_HP;
	m_maxHp = WHALE_MAX_HP;
	m_hpBarSize = XMFLOAT2(WHALE_HP_BAR_SIZE_X, WHALE_HP_BAR_SIZE_Y);

	vector<XMFLOAT2> boundingBoxVertex = {
		{ -730.f, 14.f },
		{ -742.f, 146.f },
		{ -672.f, 298.f },
		{ -498.f, 400.f },
		{ -218.f, 422.f },
		{ 414.f, 372.f },
		{ 530.f, 340.f },
		{ 634.f, 264.f },
		{ 750.f, 110.f },
		{ 740.f, -255.f },
		{ 714.f, -328.f },
		{ 596.f, -382.f },
		{ 156.f, -420.f },
		{ -422.f, -280.f },
		{ -630.f, -176.f },
	};
	m_pBoundingBox.push_back(new PolygonBoundingBox(_pos, boundingBoxVertex));

	m_pHpBar = CreateSprite(Tex_HPBar, WHALE_HP_BAR_SIZE_X, WHALE_HP_BAR_SIZE_Y);
	m_pFreamOfHpBar = CreateSprite(Tex_HPBarFream, WHALE_HP_BAR_FREAM_SIZE_X, WHALE_HP_BAR_FREAM_SIZE_Y);
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();

	m_pHpBar->setPos(cameraPos.x + WHALE_HP_BAR_RELATIVE_POS_X, cameraPos.y + WHALE_HP_BAR_RELATIVE_POS_Y);
	m_pFreamOfHpBar->setPos(cameraPos.x + WHALE_HP_BAR_RELATIVE_POS_X, cameraPos.y + WHALE_HP_BAR_RELATIVE_POS_Y);

	m_moveRangeOfXAxis[0] = CameraManager::GetCameraRangeMin().x + WINDOW_LEFT;
	m_moveRangeOfXAxis[1] = CameraManager::GetCameraRangeMax().x + WINDOW_RIGHT;
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
	if (Percent(70))
	{
		// �N�W�����΂𐁂��Ƃ��납������͂܂ł̃x�N�g�������A���K������
		XMFLOAT2 vector = WAHLE_RELATIVE_POS_OF_MOUTH;
		if (m_bFacingRight)vector.x = -vector.x;
		vector.x = _SubmarinePos.x - (m_pos.x + vector.x);
		vector.y = _SubmarinePos.y - (m_pos.y + vector.y);
		
		// �����͂������x�߂Â��Ă���
		if (FindDistanceByCoordinateDifference(vector) < WHALE_PATTERN1_BIOW_FIRE_DISTANCE)
		{
			// �N�W�����΂𐁂���p�x��cos���v�Z���Ă����i���ςŎg���j
			static float cosBiowFireAngle = cosf(WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f);

			NormalizeVector(vector);

			// �����͂��͈͂ɓ����Ă���
			if (vector.x * ((m_bFacingRight)?(1.f):(-1.f)) > cosBiowFireAngle)
			{
				if (m_lastTimeAction == ActionPattern::biowFire)
				{
					if (Percent(30))
					{
						m_nowAction = ActionPattern::biowFire;
						return;
					}
				}
				else
				{
					m_nowAction = ActionPattern::biowFire;
					return;
				}
			}
		}
	}

	if (Abs(_SubmarinePos.x - m_pos.x) < WHALE_SIZE_X / 2.f)
	{
		if (Percent(70))
		{
			if (m_lastTimeAction == ActionPattern::dash)
			{
				if (Percent(20))
				{
					m_nowAction = ActionPattern::dash;
					return;
				}
			}
			else
			{
				m_nowAction = ActionPattern::dash;
				return;
			}
		}
	}
	else
	{
		if (Percent(70))
		{
			if (m_lastTimeAction == ActionPattern::laser)
			{
				if (Percent(30))
				{
					m_nowAction = ActionPattern::laser;
					return;
				}
			}
			else
			{
				m_nowAction = ActionPattern::laser;
				return;
			}
		}
	}

	// �c��̓����_����
	m_nowAction = ActionPattern(rand() % (ActionPattern::Total - 2) + 2);
	if (m_nowAction == m_lastTimeAction)
	{
		m_nowAction = ActionPattern(rand() % (ActionPattern::Total - 2) + 2);
	}
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
		m_lastTimeAction = m_nowAction;
	}

	switch (m_nowAction)
	{
	case ActionPattern::none:												break;
	case ActionPattern::biowFire:		BiowFireProcess(_SubmarinePos);		break;
	case ActionPattern::dash:			DashProcess();						break;
	case ActionPattern::laser:			LaserProcess(_SubmarinePos);		break;
	//case ActionPattern::summonEnemy:	SummonEnemyProcess();				break;
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
	if (m_bFacingRight)pos.x = -pos.x;
	pos.x += m_pos.x;
	pos.y += m_pos.y;

	// �N�W�����΂𐁂���p�x��cos���v�Z���Ă����i���ςŎg���j
	static float cosBiowFireAngle = cosf(WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f);

	// �N�W���̌���������͂܂ł̃x�N�g�����v�Z���Ă���
	XMFLOAT2 vector = FindVectorByTwoPos(pos, _SubmarinePos);
	NormalizeVector(vector);
	
	bool bOverRange = false;
	float angle;
	if (vector.x * ((m_bFacingRight)?(1.f):(-1.f)) < cosBiowFireAngle)
	{
		bOverRange = true;
		if (vector.y > 0.f)
		{
			if (m_bFacingRight)
			{
				angle = WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
			}
			else
			{
				angle = 180.f - WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
			}
		}
		else
		{
			if (m_bFacingRight)
			{
				angle = -WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
			}
			else
			{
				angle = 180.f + WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
			}
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
	static XMFLOAT2 pos; // ���W��ۑ��p
	if (m_actionTimeCnt++ > WHALE_PATTERN2_DURATION_TIME)
	{
		m_actionTimeCnt = 0;
		m_cooldown = WHALE_COUNTDOWN_BETWEEN_ACTION;
		m_nowAction = ActionPattern::none;
	}
	// ������
	if (m_actionTimeCnt < WHALE_PATTERN2_RETREAT_TIME)
	{
		float yAxisDistanceOfWhaleAndCamera = CameraManager::GetCameraPos().y - m_pImg[0]->getPos().y;
		if (Abs(yAxisDistanceOfWhaleAndCamera) > WHALE_PATTERN2_Y_AXIS_MOVE_LIMIT)yAxisDistanceOfWhaleAndCamera = (yAxisDistanceOfWhaleAndCamera > 0.f) ? (WHALE_PATTERN2_Y_AXIS_MOVE_LIMIT) : (-WHALE_PATTERN2_Y_AXIS_MOVE_LIMIT);
		
		XMFLOAT2 newPos = {
			m_pImg[0]->getPos().x + ((m_bFacingRight)?(-WHALE_RETREAT_DISTANCE):(WHALE_RETREAT_DISTANCE)) / (float)WHALE_PATTERN2_RETREAT_TIME,
			m_pImg[0]->getPos().y + yAxisDistanceOfWhaleAndCamera
		};
		this->SetPos(newPos);
	}
	// �_�b�V��
	else if (m_actionTimeCnt < WHALE_PATTERN2_RETREAT_TIME + WHALE_PATTERN2_DASH_TIME)
	{
		if (m_actionTimeCnt == WHALE_PATTERN2_RETREAT_TIME)
		{
			pos.x = m_pImg[0]->getPos().x;
		}
		XMFLOAT2 newPos = { 
			pos.x + (((m_bFacingRight) ? (m_moveRangeOfXAxis[1] + WINDOW_RIGHT + WHALE_SIZE_X * 0.7f) : (m_moveRangeOfXAxis[0] + WINDOW_LEFT - WHALE_SIZE_X * 0.7f)) - pos.x) * ((float)(m_actionTimeCnt - WHALE_PATTERN2_RETREAT_TIME) / (float)WHALE_PATTERN2_DASH_TIME),
			m_pImg[0]->getPos().y 
		};
		this->SetPos(newPos);
	}
	// ���E���]
	else if(m_actionTimeCnt == WHALE_PATTERN2_RETREAT_TIME + WHALE_PATTERN2_DASH_TIME)
	{
		this->FlipHorizontal();
		pos.x = m_pImg[0]->getPos().x;
		pos.y = CameraManager::GetCameraPos().y;
	}
	// ��ʊO�������
	else if (m_actionTimeCnt < WHALE_PATTERN2_DURATION_TIME)
	{
		XMFLOAT2 newPos = {
			pos.x + (((m_bFacingRight) ? (m_moveRangeOfXAxis[0]) : (m_moveRangeOfXAxis[1])) - pos.x) * ((float)(m_actionTimeCnt - WHALE_PATTERN2_RETREAT_TIME - WHALE_PATTERN2_DASH_TIME - WHALE_PATTERN2_WAIT_TIME_AFTER_DASH) / (float)WHALE_PATTERN2_ENTER_SCREEN_TIME),
			pos.y
		};
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
			if (m_bFacingRight)pos.x = -pos.x;
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
		if (m_bFacingRight)pos.x = -pos.x;
		pos.x += m_pos.x;
		pos.y += m_pos.y;
		m_pBullet->push_back((shared_ptr<EnemyBullet>)new Laser(m_pGameInfo, WHALE_PATTERN3_LASER_SIZE, pos, WHALE_PATTERN3_LASER_START_ANGLE));
		index = (int)m_pBullet->size() - 1;
	}

	float angle;
	if (!m_bFacingRight)
	{
		if (m_bLaserStartFromDown)
		{
			angle = WHALE_PATTERN3_LASER_START_ANGLE + m_actionTimeCnt * (WHALE_PATTERN3_LASER_END_ANGLE - WHALE_PATTERN3_LASER_START_ANGLE) / WHALE_PATTERN3_DURATION_TIME;
		}
		else
		{
			angle = WHALE_PATTERN3_LASER_END_ANGLE + m_actionTimeCnt * (WHALE_PATTERN3_LASER_START_ANGLE - WHALE_PATTERN3_LASER_END_ANGLE) / WHALE_PATTERN3_DURATION_TIME;
		}
	}
	else
	{
		if (m_bLaserStartFromDown)
		{
			angle = 180.f + WHALE_PATTERN3_LASER_END_ANGLE + m_actionTimeCnt * (WHALE_PATTERN3_LASER_START_ANGLE - WHALE_PATTERN3_LASER_END_ANGLE) / WHALE_PATTERN3_DURATION_TIME;
		}
		else
		{
			angle = 180.f + WHALE_PATTERN3_LASER_START_ANGLE + m_actionTimeCnt * (WHALE_PATTERN3_LASER_END_ANGLE - WHALE_PATTERN3_LASER_START_ANGLE) / WHALE_PATTERN3_DURATION_TIME;
		}
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
//void Whale::SummonEnemyProcess()
//{
//	if (pEnemy->size() > WHALE_PATTERN4_SUMMON_ENEMY_NUM / 5 * 2)
//	{
//		m_nowAction = ActionPattern::none;
//		return;
//	}
//
//	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();
//	for (int i = 0; i < WHALE_PATTERN4_SUMMON_ENEMY_NUM; ++i)
//	{
//		if (rand() % 2)
//		{
//			//pEnemy->push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1))), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 5.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
//			pEnemy->push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f)), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 3.f)) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
//		}
//		else
//		{
//			//pEnemy->push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1))), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 5.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
//			pEnemy->push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(cameraPos.x + (float)((rand() % int(WINDOW_WIDTH / 5.f) + 960.f)), cameraPos.y + (float)((rand() % int(WINDOW_HEIGHT / 3.f)) * ((rand() % 2 == 0) ? (1) : (-1)))), (float)(rand() % 360)));
//		}
//	}
//
//	m_actionTimeCnt = 0;
//	m_cooldown = WHALE_COOLDOWN_AFTER_PATTERN4;
//	m_nowAction = ActionPattern::none;
//}

//����������������������������������������������
// �N�W���̍��W��ݒu����
//����������������������������������������������
void Whale::SetPos(XMFLOAT2 _newPos)
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)m_pImg[i]->setPos(_newPos);
	m_pImg[1]->setPos(_newPos.x + ((m_bFacingRight) ? (-WHALE_TOOTH_RELATIVE_POS_X) : (WHALE_TOOTH_RELATIVE_POS_X)), _newPos.y + WHALE_TOOTH_RELATIVE_POS_Y);
	XMFLOAT2 pos = { WHALE_MISSILELAUNCHER_RELATIVE_POS_X, WHALE_MISSILELAUNCHER_RELATIVE_POS_Y };
	if (m_bFacingRight)
	{
		pos.x = _newPos.x - pos.x;
		pos.y = _newPos.y + pos.y;
	}
	else
	{
		pos.x = _newPos.x + pos.x;
		pos.y = _newPos.y + pos.y;
	}

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

	m_pImg[1]->setAnimation(int(10 - int(percents * 11.f)));
}

//����������������������������������������������
// ���E���]�ɂ���
//����������������������������������������������
void Whale::FlipHorizontal()
{
	for (int i = 0; i < (int)m_pImg.size(); ++i) 
	{
		float angleZ = m_pImg[i]->getAngleZ();
		m_pImg[i]->setAngle(0.f, (m_bFacingRight)?(0.f):(180.f), angleZ );
	}
	m_pImg[1]->setPos(m_pos.x + ((m_bFacingRight) ? (-WHALE_TOOTH_RELATIVE_POS_X) : (WHALE_TOOTH_RELATIVE_POS_X)), m_pos.y + WHALE_TOOTH_RELATIVE_POS_Y);

	XMFLOAT2 pos = { WHALE_MISSILELAUNCHER_RELATIVE_POS_X, WHALE_MISSILELAUNCHER_RELATIVE_POS_Y };
	if (!m_bFacingRight)
	{
		pos.x = m_pos.x - pos.x;
		pos.y = m_pos.y + pos.y;
	}
	else
	{
		pos.x = m_pos.x + pos.x;
		pos.y = m_pos.y + pos.y;
	}

	m_pMissileLauncher->SetPosAndAngle(pos, 0.f);
	m_bFacingRight = !m_bFacingRight;
	((PolygonBoundingBox*)m_pBoundingBox[0])->FlipHorizontal();
}