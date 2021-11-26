//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：RectangleBoundingBox.cpp
// 概要　　　　　：四角形バウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "RectangleBoundingBox.h"

RectangleBoundingBox::RectangleBoundingBox()
{
}

RectangleBoundingBox::~RectangleBoundingBox()
{
}

XMFLOAT2 RectangleBoundingBox::GetPos()const
{
	return m_pos;
}

XMFLOAT2 RectangleBoundingBox::GetSize()const
{
	return m_size;
}