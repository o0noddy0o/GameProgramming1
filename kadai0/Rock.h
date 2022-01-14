//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Rock.h
// 概要　　　　　：岩のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/13 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "SceneryObject.h"

class Rock : public SceneryObject
{
	typedef SceneryObject Super;
public:
	Rock(GameInfo* _pGameInfo, int _rockType, XMFLOAT2 _pos, float _angle = 0.f);
	virtual ~Rock();
};