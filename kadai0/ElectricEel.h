//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：ElectricEel.h
// 概要　　　　　：電気ウナギのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/13 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "Fish.h"

class ElectricEel : public Fish
{
	typedef Fish Super;
public:
	ElectricEel(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle = 0.f);
	virtual ~ElectricEel();

	// 攻撃の処理
	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f));

	// 移動処理
	virtual void MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime);

private:
};