//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Stage.h
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/01 作成
// 　　　　　　　：2022/01/29 カメラを管理するメソッドを追加（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "CObjectBase.h"
#include "Define.h"
#include "Submarine.h"
#include "SceneryObject.h"
#include "Board.h"

class EnemyBullet;
class Boss;
class Goal;
class Arrow;

class Stage :public CObjectBase
{
	typedef CObjectBase Super;
public:
	Stage(GameInfo* _pGameInfo);
	~Stage();
	// 毎フレームの処理
	void Tick();

	// 全てのRenderメソッドを呼び出す
	void RenderProcess();

	// 全て当たり判定をまとめたメソッド(潜水艦のを呼び出す)
	void CollisionProcess();

	int GetKilledEnemyCnt()const;

	void SetNextStage(const int _stageNum = -1);

	void ResetStage();

	void SetCameraPos(XMFLOAT2 _newPos);

	void SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max);

private:
	void InitStage1();
	void InitStage2();

	void StartBossBattle();

private:
	// 潜水艦オブジェクト
	shared_ptr < Submarine > m_pSubmarine;

	// マップにある障害物などのオブジェクトの配列
	vector < shared_ptr < SceneryObject > > m_pSceneryObject;

	//掲示板
	vector < shared_ptr < Board > > m_pBoard;

	// 敵のオブジェクトの配列
	vector < shared_ptr < Enemy > > m_pEnemy;

	// アイテムのオブジェクトの配列
	//vector < shared_ptr < Item > > m_pItem;

	// 敵の弾の配列のアドレスの配列
	shared_ptr<vector<shared_ptr<EnemyBullet>>> m_pEnemyBullet;

	shared_ptr<Boss> m_pBoss;

	shared_ptr<vector<shared_ptr<EnemyBullet>>> m_pBossBullet;

	shared_ptr<Goal> m_pGoal;

	shared_ptr<Arrow> m_pArrow;

	// 前1フレームの時間(deltaTime計算用)
	clock_t m_lastFrameTime;

	//掲示板
	CPicture* pBoard = nullptr;

	float m_deltaTime;

	int m_map[Map_Y_SIZE][Map_X_SIZE];

	int m_nowStageNum;

	bool m_bBossBettle;
};
