//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Stage.cpp
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/01 作成
// 　　　　　　　　2021/12/08　敵の弾を発射機能を追加
// 　　　　　　　　2021/12/10　敵の移動処理を追加
// 　　　　　　　　2021/01/13　障害物の配置(呉)
//━━━━━━━━━━━━━━━━━━━━━━━

#include "Stage.h"
#include "GameResource.h"
#include "SceneryObject.h"
#include "Submarine.h"
#include "Map.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Fish.h"
#include "Fish2.h"
#include <time.h>
#include "Rock.h"
#include "ElectricEel.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Stage::Stage(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
	, m_pSubmarine(NULL)
{
	srand((unsigned)time(NULL));

	//潜水艦を作成
	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(_pGameInfo);

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
	
	//
	int map[Map_Y_SIZE][Map_X_SIZE] = Stage01;

	//m_map = map;
	
#if HaveEnemy
	Enemy::ResetEnemyBullet();
	//敵を作成
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(600.f,  850.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(810.f,   10.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-800.f, 200.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(720.f, -900.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-720.f,  90.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(580.f,  450.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(360.f,  180.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(410.f,  680.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-860.f, 210.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(380.f,   70.f), (float)rand()));

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

	m_pEnemyBullet = Enemy::GetBullet();
#endif

	m_lastFrameTime = clock();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Stage::~Stage()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の画像の描画処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::RenderProcess()
{
	
	for (int i = 0; i < (int)m_pSceneryObject.size(); ++i)
	{
		m_pSceneryObject[i]->renderSprite();
	}
	m_pSubmarine->RenderProcess();

#if HaveEnemy
	for (int i = 0; i < (int)m_pEnemyBullet->size(); ++i)
	{
		(*m_pEnemyBullet)[i].get()->renderSprite();
	}

	for (int i = 0; i < (int)m_pEnemy.size(); ++i)
	{
		m_pEnemy[i]->renderSprite();
	}
#endif
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::CollisionProcess()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 毎フレームにやる処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::Tick()
{
	{
		clock_t thisFrameTime = clock();
		m_deltaTime = (float)(thisFrameTime - m_lastFrameTime) / 1000.f;
		m_lastFrameTime = thisFrameTime;
	}

	m_pSubmarine->Tick(m_deltaTime);

	m_pSubmarine->CollisionProcess(&m_pEnemy, m_pEnemyBullet, &m_pSceneryObject, NULL);

	{
		XMFLOAT2 SubmarinePos(m_pSubmarine->GetPos());
		for (int i = 0; i < (int)m_pEnemy.size(); ++i)
		{
			m_pEnemy[i]->AttackProcess();
			m_pEnemy[i]->MoveProcess(SubmarinePos, m_deltaTime);
		}
	}
#if HaveEnemy
	for (int i = 0; i < (int)m_pEnemyBullet->size(); ++i)
	{
		(*m_pEnemyBullet)[i].get()->MoveProcess(m_deltaTime);
	}
#endif
	m_pSubmarine->MoveProcess(m_deltaTime);

}

int Stage::GetKilledEnemyCnt()const
{
	return m_pSubmarine->GetKilledEnemyCnt();
}

float Stage::GetSubmarineHp()const
{
	return m_pSubmarine->GetHp();
}