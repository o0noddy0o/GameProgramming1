//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Goal.cpp
// 概要　　　　　：ゴールのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/02/16 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Goal.h"
#include "RectangleBoundingBox.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Goal::Goal(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _size)
	: Super(_pGameInfo)
	, m_pImg(NULL)
	, m_pBoundingBox(NULL)
{
	m_pImg = CreateSprite(Tex_TestImage1, _size.x, _size.y);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, _size);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Goal::~Goal()
{
	delete m_pBoundingBox;
	DisposeSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスを取得
//━━━━━━━━━━━━━━━━━━━━━━━
BoundingBox* Goal::GetBoundingBox()const
{
	return (BoundingBox*)m_pBoundingBox;
}

void Goal::rendingSprite()
{
	RenderSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ゴールの座標を取得する
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 Goal::GetPos()const
{
	return XMFLOAT2(m_pImg->getPos().x, m_pImg->getPos().y);
}