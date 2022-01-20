//����������������������������������������������
// �t�@�C�����@�@�FStageInit.cpp
// �T�v�@�@�@�@�@�F�e�X�e�[�W�̔z�u���܂Ƃ߂��t�@�C��
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/12/19 �쐬
//����������������������������������������������
#include "Stage.h"
#include "Define.h"
#include "Fish.h"
#include "Fish2.h"
#include "Boss.h"
#include "Rock.h"
#include "ElectricEel.h"
#include "MissileLauncher.h"
#include "Whale.h"

//����������������������������������������������
// ���̃X�e�[�W�ɐݒu����
// �����P�F�ݒu����X�e�[�W�̔ԍ��i����Ȃ������玟�̃X�e�[�W�j
//����������������������������������������������
void Stage::SetNextStage(const int _stageNum)
{
	// ���̃X�e�[�W
	if (_stageNum == -1)
	{
		++m_nowStageNum;

		// �S�X�e�[�W�N���A
		if (m_nowStageNum == NUM_OF_STAGE)
		{

		}
	}
	// �w��X�e�[�W
	else if(!(_stageNum > NUM_OF_STAGE || _stageNum < 0))
	{
		m_nowStageNum = _stageNum;
	}

	ResetStage();
}

//����������������������������������������������
// �X�e�[�W�����Z�b�g����
//����������������������������������������������
void Stage::ResetStage()
{
	// �O��g������������
	m_pSubmarine = NULL;
	m_pSceneryObject.clear();
	m_pEnemy.clear();
	//m_pItem.clear();
	if(m_pEnemyBullet)m_pEnemyBullet->clear();
	m_pEnemyBullet = NULL;

	switch (m_nowStageNum)
	{
	case 1:
		InitStage1();
		break;

	case 2:
		InitStage2();
		break;
	}
}

//����������������������������������������������
// �X�e�[�W�P
//����������������������������������������������
void Stage::InitStage1()
{
	//�����͂��쐬
	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(m_pGameInfo);

	//��Q�����쐬
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 3, XMFLOAT2(2115.f, 540.f), -5.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 2, XMFLOAT2(3755.f, 116.f), 90.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 1, XMFLOAT2(4323.f, -809.f)));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 1, XMFLOAT2(4176.f, -1735.f), -45.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 2, XMFLOAT2(4376.f, -2676.f)));

	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 3, XMFLOAT2(3624.f, -3463.f)));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 4, XMFLOAT2(2250.f, -3459.f)));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 3, XMFLOAT2(950.f, -3459.f), 180.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 1, XMFLOAT2(-173.f, -3296.f), 180.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 5, XMFLOAT2(-606.f, -2618.f)));

	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 3, XMFLOAT2(-644.f, -1496.f), 90.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 2, XMFLOAT2(-484.f, -665.f), 45.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 3, XMFLOAT2(373.f, -538.f), 180.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 4, XMFLOAT2(1228.f, -475.f), -10.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 5, XMFLOAT2(3952.f, -1144.f), 180.f));

	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 3, XMFLOAT2(2885.f, -1180.f), 180.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new Rock(m_pGameInfo, 4, XMFLOAT2(1817.f, -1407.f)));

#if HaveEnemy
	Enemy::ResetEnemyBullet();
	//�G���쐬
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(600.f, 850.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(810.f, 10.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-800.f, 200.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(720.f, -900.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-720.f, 90.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(580.f, 450.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(360.f, 180.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(410.f, 680.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-860.f, 210.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(380.f, 70.f), (float)rand()));

	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));

	m_pEnemy.push_back((shared_ptr<Enemy>)new MissileLauncher(m_pGameInfo, XMFLOAT2(400.f, 0.f)));

	m_pEnemyBullet = Enemy::GetBullet();
#endif
}

void Stage::InitStage2()
{
	//�����͂��쐬
	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(m_pGameInfo);

	m_pBoss = (shared_ptr<Boss>)new Whale(m_pGameInfo, XMFLOAT2(1000.f, 0.f));

	Enemy::ResetEnemyBullet();
	Boss::ResetBossBullet();
	m_pEnemyBullet = Enemy::GetBullet();
	m_pBossBullet = Boss::GetBossBullet();
}