//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：MissileLauncher.h
// 概要　　　　　：ミサイル発射機のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/14 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Enemy.h"

class MissileLauncher : public Enemy
{
	typedef Enemy Super;
public:
	MissileLauncher(GameInfo* _pGameInfo, XMFLOAT2 _pedestalPos, float _pedestalAngle = 0.f);
	virtual ~MissileLauncher();

	virtual void renderSprite();

	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f));

	virtual void MoveProcess();

private:
	CPicture* m_pImg2;
	float m_angle;
};