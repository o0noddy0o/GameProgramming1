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

class Enemy;
class SceneryObject;
class Bullet;
class Item;
class Player;
class OperationDevice;
class Component;
class MapDevice;
class UI;

class Submarine : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Submarine(GameInfo* _pGameInfo);
	~Submarine();

	// 毎フレームにやる処理
	void Tick(float _deltaTime);

	// 画像を描画する
	void RenderProcess();

	// 当たり判定
	void CollisionProcess(
		vector < shared_ptr < Enemy> >*				_pEnemy,
		vector < shared_ptr < SceneryObject > >*	_pSceneryObject,
		vector < shared_ptr < Bullet > >**			_pBullet,
		vector < shared_ptr < Item > >*				_pItem);
		
	// 潜水艦全体の移動
	void MoveProcess(float _deltaTime);

	// アイテムを取得した後の処理
	void GetItem(int _itemType);

	void MoveCamera();

private:
	CPicture*					m_pImg;
	XMFLOAT2					m_pos;
	shared_ptr<Player>			m_pPlayer[2];
	shared_ptr<OperationDevice> m_pOperationDevice[NUM_OF_OPERATION_DEVICE];
	shared_ptr<Component>		m_pComponent[NUM_OF_COMPONENT];
	//shared_ptr<MapDevice>		m_pMapDevice;
	vector<shared_ptr<Bullet>>* m_pBullet[4];
	//shared_ptr<UI>				m_pUI;
};