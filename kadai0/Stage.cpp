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

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Stage::Stage(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
{

	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(_pGameInfo);
	//
	int map[Map_Y_SIZE][Map_X_SIZE] = Stage01;
	//m_map = map;
	
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

	for (int i = 0; i < (int)m_pEnemy.size(); ++i)
	{
		m_pEnemyBullet.push_back((vector<shared_ptr<EnemyBullet>>*)(m_pEnemy[i])->GetBullet());
	}
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

	for (int i = 0; i < (int)m_pEnemyBullet.size(); ++i)
	{
		for (int j = 0; j < (int)m_pEnemyBullet[i]->size(); ++j)
		{
			(*m_pEnemyBullet[i])[j].get()->renderSprite();
		}
	}

	for (int i = 0; i < (int)m_pEnemy.size(); ++i)
	{
		m_pEnemy[i]->renderSprite();
	}
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
	m_pSubmarine->Tick(1.f);
	{
		XMFLOAT2 SubmarinePos(m_pSubmarine->GetPos());
		for (int i = 0; i < (int)m_pEnemy.size(); ++i)
		{
			m_pEnemy[i]->AttackProcess();
			m_pEnemy[i]->MoveProcess(SubmarinePos);
		}
	}
	for (int i = 0; i < (int)m_pEnemyBullet.size(); ++i)
	{
		for (int j = 0; j < (int)m_pEnemyBullet[i]->size(); ++j)
		{
			(*m_pEnemyBullet[i])[j].get()->MoveProcess(1.f);
		}
	}
	m_pSubmarine->MoveProcess(1.f);
}