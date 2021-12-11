//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：SceneryObject.cpp
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/11/26 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "SceneryObject.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：ブロックの初期座標
// 引数３：ブロックの初期角度
//━━━━━━━━━━━━━━━━━━━━━━━
SceneryObject::SceneryObject(GameInfo* _pGameInfo,XMFLOAT2 _pos,float _angle)
	:CObjectBase(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_Rock,Block_X_SIZE,Block_Y_SIZE);
	m_pImg->setPos(_pos);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
SceneryObject::~SceneryObject()
{
	DisposeSprite(m_pImg);
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
void SceneryObject::Collision(CPicture* _pImg)
{

}