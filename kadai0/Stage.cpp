//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Stage.cpp
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/01 作成
//			　　　2021/12/08　敵の弾を発射機能を追加
//			　　　2021/12/10　敵の移動処理を追加
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

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Stage::Stage(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
	, m_pSubmarine(NULL)
{
	srand((unsigned)time(NULL));

	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(_pGameInfo);
	//
	int map[Map_Y_SIZE][Map_X_SIZE] = Stage01;
	//m_map = map;
	
#if HaveEnemy
	Enemy::ResetEnemyBullet();

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
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));

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

	m_pSubmarine->CollisionProcess(&m_pEnemy, m_pEnemyBullet, NULL, NULL);

	m_pSubmarine->Tick(m_deltaTime);
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