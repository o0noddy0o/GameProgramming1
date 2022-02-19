//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Stage.cpp
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/01 作成
// 　　　　　　　　2021/12/08　敵の弾を発射機能を追加
// 　　　　　　　　2021/12/10　敵の移動処理を追加
// 　　　　　　　　2021/01/13　障害物の配置(呉)
// 　　　　　　　：2022/01/29 カメラを管理するメソッドを追加（呉）
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
#include "MissileLauncher.h"
#include "Boss.h"
#include "Whale.h"
#include "CameraManager.h"
#include "Goal.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Stage::Stage(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
	, m_pSubmarine(NULL)
	, m_nowStageNum(0)
	, m_pBoss(NULL)
	, m_bBossBettle(false)
	, m_pGoal(NULL)
{
	srand((unsigned)time(NULL));

	CameraManager::SetUpCamera(m_pGameInfo->pCamera);

	SetNextStage(2);

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

	if(m_pGoal)m_pGoal->rendingSprite();
	
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

	if (m_pBossBullet)
	{
		for (int i = 0; i < (int)m_pBossBullet->size(); ++i)
		{
			(*m_pBossBullet)[i].get()->renderSprite();
		}
	}

	if (m_pBoss)m_pBoss->renderSprite();

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

#if HaveEnemy
	{
		XMFLOAT2 SubmarinePos(m_pSubmarine->GetPos());
		for (int i = 0; i < (int)m_pEnemy.size(); ++i)
		{
			m_pEnemy[i]->AttackProcess();
			m_pEnemy[i]->MoveProcess(SubmarinePos, m_deltaTime);
		}

		if (m_pBoss)m_pBoss->Tick(SubmarinePos, m_deltaTime);

		if (m_pBossBullet)
		{
			for (int i = 0; i < (int)m_pBossBullet->size(); ++i)
			{
				(*m_pBossBullet)[i].get()->MoveProcess(m_deltaTime, SubmarinePos);
			}
		}

		if (m_pEnemyBullet)
		{
			for (int i = 0; i < (int)m_pEnemyBullet->size(); ++i)
			{
				(*m_pEnemyBullet)[i].get()->MoveProcess(m_deltaTime, SubmarinePos);
			}
		}

		if (m_pSubmarine->GetKilledEnemyCnt() == MAX_ENEMY_NUM && !m_bBossBettle)
		{
			StartBossBattle();
		}
	}
#endif

	m_pSubmarine->CollisionProcess(&m_pEnemy, m_pEnemyBullet, &m_pSceneryObject, (m_pBoss.get())?(m_pBoss.get()):(NULL), m_pBossBullet, m_pGoal.get(), NULL);
	m_pSubmarine->Tick(m_deltaTime);
}

int Stage::GetKilledEnemyCnt()const
{
	return m_pSubmarine->GetKilledEnemyCnt();
}

void Stage::StartBossBattle()
{
	m_bBossBettle = true;

	SetCameraPos(m_pSubmarine->GetPos());

	XMFLOAT2 cameraPos = m_pSubmarine->GetPos();

	SetCameraMoveRange(XMFLOAT2(cameraPos.x - 300.f, cameraPos.y - 300.f), XMFLOAT2(cameraPos.x, cameraPos.y + 300.f));

	switch (m_nowStageNum)
	{
	case 1:
		m_pBoss = (shared_ptr<Boss>)new Whale(m_pGameInfo, XMFLOAT2(cameraPos.x + CameraManager::GetCameraRangeMax().x, cameraPos.y), &m_pEnemy);
		break;
	case 2:
		m_pBoss = (shared_ptr<Boss>)new Whale(m_pGameInfo, XMFLOAT2(cameraPos.x + CameraManager::GetCameraRangeMax().x, cameraPos.y), &m_pEnemy);
		break;
	}
	
}

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラの座標をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::SetCameraPos(XMFLOAT2 _newPos)
{
	CameraManager::SetCameraPos(_newPos);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラの移動範囲をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void Stage::SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max)
{
	CameraManager::SetCameraMoveRange(_min, _max);
}