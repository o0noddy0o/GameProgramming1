//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：ThunderBullet.h
// 概要　　　　　：電気ウナギが使う弾のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/13 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "EnemyBullet.h"

class ThunderBullet : public EnemyBullet
{
	typedef EnemyBullet Super;
public:
	ThunderBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, float _angle = 0.f);
	~ThunderBullet();

	virtual void MoveProcess(float _deltaTime);

private:

};