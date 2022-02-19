//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Component.cpp
// 概要　　　　　：潜水艦の部品
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Component.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：部品の座標と潜水艦の座標の差
//━━━━━━━━━━━━━━━━━━━━━━━
Component::Component(GameInfo* _pGameInfo, XMFLOAT2 _relativePos)
	: Super(_pGameInfo)
	, m_pImg(nullptr)
	, m_relativePos(_relativePos)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Component::~Component()
{
	if (m_pImg)delete m_pImg;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 部品の画像を取得する
//━━━━━━━━━━━━━━━━━━━━━━━
CPicture* Component::GetImg()
{
	return m_pImg;
}

void Component::renderSprite(float _alpha)
{
	RenderSprite(m_pImg, XMFLOAT4(1.f, 1.f, 1.f, _alpha));
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像の位置を設置する
//━━━━━━━━━━━━━━━━━━━━━━━
void Component::SetPos(XMFLOAT2 _pos)
{
	m_pImg->setPos(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y);
}