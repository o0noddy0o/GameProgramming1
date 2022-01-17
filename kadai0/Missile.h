//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Missile.h
// 概要　　　　　：ミサイルのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/14 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "EnemyBullet.h"

class Missile : public EnemyBullet
{
	typedef EnemyBullet Super;
public:
	Missile(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle, bool _bBigSize = false);
	virtual ~Missile();
	virtual void MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f))override;

private:

};