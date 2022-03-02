//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：StageInit.cpp
// 概要　　　　　：各ステージの配置をまとめたファイル
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/12/19 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Stage.h"
#include "Define.h"
#include "Fish.h"
#include "Fish2.h"
#include "Boss.h"
#include "Rock.h"
#include "ElectricEel.h"
#include "MissileLauncher.h"
#include "Whale.h"
#include "CameraManager.h"
#include "Board.h"
#include "Goal.h"
#include "Arrow.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// 次のステージに設置する
// 引数１：設置するステージの番号（入れなかったら次のステージ）
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::SetNextStage(const int _stageNum)
{
	// 次のステージ
	if (_stageNum == -1)
	{
		++m_nowStageNum;

		// 全ステージクリア
		if (m_nowStageNum == NUM_OF_STAGE)
		{
			throw (string)"EndOfAllStage";
		}
	}
	// 指定ステージ
	else if(!(_stageNum > NUM_OF_STAGE || _stageNum < 0))
	{
		m_nowStageNum = _stageNum;
	}

	ResetStage();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ステージをリセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::ResetStage()
{
	// 前回使った物を消す
	m_pSubmarine = NULL;
	m_pSceneryObject.clear();
	m_pEnemy.clear();
	//m_pItem.clear();
	if(m_pEnemyBullet)m_pEnemyBullet->clear();
	m_pEnemyBullet = NULL;
	m_pGoal = NULL;

	Enemy::ResetEnemyBullet();
	m_pEnemyBullet = Enemy::GetBullet();
	Boss::ResetBossBullet();
	m_pBossBullet = Boss::GetBossBullet();

	switch (m_nowStageNum)
	{
	case 1: InitStage1(); break;
	case 2: InitStage2(); break;
	}

	if (m_pGoal)
	{
		m_pArrow = (shared_ptr<Arrow>)new Arrow(m_pGameInfo, m_pGoal->GetPos());
	}
	else
	{
		m_pArrow = NULL;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ステージ１
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::InitStage1()
{
	//潜水艦を作成
	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(m_pGameInfo);

	SetCameraMoveRange(XMFLOAT2(0.f, -WINDOW_HEIGHT * (SCREEN_MULTIPLE_Y - 1.f)), XMFLOAT2(WINDOW_WIDTH * (SCREEN_MULTIPLE_X - 1.f), 0.f));
	
	m_pGoal = (shared_ptr<Goal>)new Goal(m_pGameInfo, XMFLOAT2(3500.f, -2750.f), XMFLOAT2(680.f, 400.f));

	//掲示板
	m_pBoard.push_back((shared_ptr<Board>)new Board(m_pGameInfo, 1, XMFLOAT2(600.f, 300.f)));

	//障害物を作成
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
	//敵を作成
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(3600.f, -750.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(3500.f, -710.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(2300.f, -310.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(3500.f, -650.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(2100.f, -2790.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(580.f, -2620.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(2380.f, -2450.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(880.f, -2680.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(880.f, -2750.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(2480.f, -2820.f), (float)rand()));

	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(2480.f, -720.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(3380.f, -1720.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(3680.f, -1920.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(980.f, -1720.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(3460.f, -2720.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(3580.f, -1620.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(3600.f, -2120.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(960.f, -2720.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(1200.f, -2680.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2(1000.f, -3220.f), (float)rand()));

	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(3200.f, -550.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(600.f, -1950.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(700.f, -2650.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(3500.f, -2150.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(3800.f, -2650.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(1200.f, -2550.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(3200.f, -1550.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(3100.f, -2550.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(1000.f, -1580.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new ElectricEel(m_pGameInfo, XMFLOAT2(3320.f, -3150.f), (float)rand()));

	m_pEnemy.push_back((shared_ptr<Enemy>)new MissileLauncher(m_pGameInfo, XMFLOAT2(400.f, -2900.f)));

	

#endif
}

void Stage::InitStage2()
{
	//潜水艦を作成
	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(m_pGameInfo, XMFLOAT2(1000.f, -1000.f));

	StartBossBattle();
}