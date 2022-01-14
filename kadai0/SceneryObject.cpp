//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：SceneryObject.cpp
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/11/26 作成
// 　　　　　　　：2021/01/12 コンストラクタを編集
// 　　　　　　　　           GetBoundingBoxメソッド追加
//━━━━━━━━━━━━━━━━━━━━━━━
#include "SceneryObject.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：ブロックの初期座標
// 引数３：ブロックの初期角度
//━━━━━━━━━━━━━━━━━━━━━━━
SceneryObject::SceneryObject(GameInfo* _pGameInfo)
	:CObjectBase(_pGameInfo)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
SceneryObject::~SceneryObject()
{
	DisposeSprite(m_pImg);
	if (m_pBoundingBox)delete m_pBoundingBox;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ブロックの画像を取得
//━━━━━━━━━━━━━━━━━━━━━━━
CPicture* SceneryObject::GetImg()const
{
	return m_pImg;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ブロックの画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
void SceneryObject::renderSprite()
{
	RenderSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ブロックの画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
BoundingBox* SceneryObject::GetBoundingBox()const
{
	return m_pBoundingBox;
}