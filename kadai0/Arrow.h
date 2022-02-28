//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Arrow.h
// 概要　　　　　：ヒントの矢印のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/02/27 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "CObjectBase.h"

class Arrow : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Arrow(GameInfo* _pGameInfo, XMFLOAT2 _goalPos);
	~Arrow();
	void RenderSprite();
	void Tick();

private:
	CPicture* m_pImg;
	XMFLOAT2 m_goalPos;
};