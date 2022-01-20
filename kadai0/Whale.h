//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Whale.h
// 概要　　　　　：クジラ（ステージ１のボス）のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/17 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Boss.h"
#include "Enemy.h"

class MissileLauncher;

class Whale : public Boss
{
	typedef Boss Super;
private:
	// クジラの攻撃パターン
	enum ActionPattern
	{
		none = 0,
		biowFire,
		dash,
		laser,
		summonEnemy,
		Total
	};

public:
	Whale(GameInfo* _pGameInfo, XMFLOAT2 _pos);
	virtual ~Whale();

	// 行動パターンを決める
	virtual void DecideActionPattern(XMFLOAT2 _SubmarinePos);

	// 毎フレームの処理
	virtual void Tick(XMFLOAT2 _SubmarinePos)override;

	// 画像の描画
	virtual void renderSprite()override;

// 各攻撃パターンの関数
private:
	void BiowFireProcess(XMFLOAT2 _SubmarinePos);
	void LaserProcess();
	void DashProcess();
	void SummonEnemyProcess();

private:
	ActionPattern			m_nowAction;
	XMFLOAT2				m_pos;
	MissileLauncher*		m_pMissileLauncher;	// クジラの背に乗せたミサイル発射機
	vector<Enemy*>			m_pEnemy;
	int						m_actionTimeCnt;
};