//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：RectangleBoundingBox.h
// 概要　　　　　：四角形バウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "stdafx.h"

class RectangleBoundingBox
{
public:
	RectangleBoundingBox();
	~RectangleBoundingBox();

	XMFLOAT2 GetPos()const;
	XMFLOAT2 GetSize()const;

private:
	XMFLOAT2 m_pos;
	XMFLOAT2 m_size;
};