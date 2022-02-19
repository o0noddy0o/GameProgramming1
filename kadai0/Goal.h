//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Goal.h
// 概要　　　　　：ゴールのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/02/16 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "CObjectBase.h"

class BoundingBox;
class RectangleBoundingBox;

class Goal : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Goal(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _size = {250.f, 250.f});
	virtual ~Goal();
	virtual BoundingBox* GetBoundingBox()const;
	virtual void rendingSprite();

protected:
	CPicture* m_pImg;
	RectangleBoundingBox* m_pBoundingBox;
};