//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Fish2.h
// 概要　　　　　：敵クラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/03 作成
//			　　　2021/12/08　敵の弾を発射機能を追加
//			　　　2021/12/10　敵の移動処理を追加
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Enemy.h"

class BoundingBox;
class RectangleBoundingBox;

class Fish2:public Enemy
{
public:
	Fish2(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f,0.f }, float _angle = 0.f);
	~Fish2();

	// 攻撃の処理
	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f));
		
	// 移動処理
	virtual void MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime);

	virtual BoundingBox* GetBoundingBox()const;
private:
	// 当たり判定
	RectangleBoundingBox* m_pBoundingBox;
	float m_angle;
	float m_coolDownCnt;
};
