//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Stage.h
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/01 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "CObjectBase.h"
#include "Define.h"
#include "Submarine.h"
#include "SceneryObject.h"

class EnemyBullet;

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

	// 潜水艦オブジェクト
	shared_ptr < Submarine > m_pSubmarine;

	// マップにある障害物などのオブジェクトの配列
	vector < shared_ptr < SceneryObject > > m_pSceneryObject;

	// 敵のオブジェクトの配列
	vector < shared_ptr < Enemy > > m_pEnemy;

	// アイテムのオブジェクトの配列
	//vector < shared_ptr < Item > > m_pItem;

	// 敵の弾の配列のアドレスの配列
	vector < vector < shared_ptr < EnemyBullet > >* > m_pEnemyBullet;

	// 前1フレームの時間(deltaTime計算用)
	clock_t m_lastFrameTime;

	int m_map[Map_Y_SIZE][Map_X_SIZE];
};
