//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Submarine.h
// 概要　　　　　：潜水艦のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include <vector>
#include <memory>
#include "Define.h"
#include "CObjectBase.h"
#include "CText.h"

class Enemy;
class SceneryObject;
class Bullet;
class Item;
class Player;
class OperationDevice;
class Component;
class MapDevice;
class UI;
class JetEngine;
class EnemyBullet;
class BoundingBox;
class CircleBoundingBox;

class Submarine : public CObjectBase
{
	typedef CObjectBase Super;

public:
	struct Wall
	{
		CPicture* ob;
		XMFLOAT2  relativePos;
		Wall(CPicture* _ob = NULL, XMFLOAT2 _relativePos = {0.f, 0.f}) : ob(_ob), relativePos(_relativePos) {}
	};
	struct Floor
	{
		CPicture* ob;
		XMFLOAT2  relativePos;
		Floor(CPicture* _ob = NULL, XMFLOAT2 _relativePos = { 0.f, 0.f }) : ob(_ob), relativePos(_relativePos) {}
	};

public:
	Submarine(GameInfo* _pGameInfo);
	~Submarine();

	// 毎フレームにやる処理
	void Tick(float _deltaTime);

	// 画像を描画する
	void RenderProcess();

	// 当たり判定
	void CollisionProcess(
		vector<shared_ptr<Enemy>>*								_pEnemy,
		vector<shared_ptr<vector<shared_ptr<EnemyBullet>>>>*	_pEnemyBullet,
		vector<shared_ptr<SceneryObject>>*						_pSceneryObject,
		vector<shared_ptr<Item>>*								_pItem);
		
	// 潜水艦全体の移動
	void MoveProcess(float _deltaTime);

	// アイテムを取得した後の処理
	void GetItem(int _itemType);

	// カメラの移動の処理
	void MoveCamera();

	// 潜水艦座標の取得
	XMFLOAT2 GetPos()const;

	// ダメージを受けた後の処理
	void GetDamaged(float _damage);

	BoundingBox* GetBoundingBox()const;

private:
	int killedEnemyCnt;

	CPicture*					m_pImg;
	vector<Floor>				m_floor;
	vector<Wall>				m_wall;

	float						m_hp;
	XMFLOAT2					m_pos;
	shared_ptr<Player>			m_pPlayer[2];
	shared_ptr<OperationDevice> m_pOperationDevice[NUM_OF_OPERATION_DEVICE];
	shared_ptr<Component>		m_pComponent[NUM_OF_COMPONENT];
	//shared_ptr<MapDevice>		m_pMapDevice;
	vector<shared_ptr<Bullet>>* m_pBullet[4];
	shared_ptr<UI>				m_pUI;

	JetEngine*					m_pJetEngine;

	shared_ptr<CircleBoundingBox>	m_pCircleBoundingBox;

#if ShowDeltaTimeAndFPS
	shared_ptr<CText> pDeltaTimeText;
#endif
};