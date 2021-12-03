//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Fish.h
// 概要　　　　　：敵クラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/03 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Enemy.h"

class BoundingBox;
class RectangleBoundingBox;

class Fish:public Enemy
{
public:
	Fish(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f,0.f });
	~Fish();

	// 攻撃の処理
	virtual void AttackProcess();
		
	// 移動処理
	virtual void MoveProcess();

	virtual BoundingBox* GetBoundingBox()const;
private:
	// 当たり判定
	RectangleBoundingBox* m_pBoundingBox;
};

