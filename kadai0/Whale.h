//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Whale.h
// 概要　　　　　：クジラ（ステージ１のボス）のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/17 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Boss.h"

class MissileLauncher;

class Whale : public Boss
{
	typedef Boss Super;
public:
	Whale(GameInfo* _pGameInfo);
	virtual ~Whale();

	// 行動パターンを決める
	virtual void DecideActionPattern(XMFLOAT2 _SubmarinePos)override;

	// 毎フレームの処理
	virtual void Tick(XMFLOAT2 _SubmarinePos)override;

	// 画像の描画
	virtual void renderSprite()override;
private:
	float m_angle;								// クジラの向き
	MissileLauncher*	m_pMissileLauncher[2];	// クジラの背に乗せたミサイル発射機
	XMFLOAT2			m_missilePos[2];		// ミサイル発射機の相対座標
};