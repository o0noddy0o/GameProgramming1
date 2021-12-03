//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Fish.h
// 概要　　　　　：敵クラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/03 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Fish.h"
#include "GameResource.h"
#include "RectangleBoundingBox.h"

// ━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：敵の初期座標
//━━━━━━━━━━━━━━━━━━━━━━━
Fish::Fish(GameInfo* _pGameInfo, XMFLOAT2 _pos)
	:Enemy(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_Enemy, Enemy_X_SIZE, Enemy_Y_SIZE);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, XMFLOAT2(Enemy_X_SIZE, Enemy_Y_SIZE));
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Fish::~Fish()
{
	delete m_pBoundingBox;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 攻撃の処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Fish::AttackProcess()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 移動処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Fish::MoveProcess()
{
}

BoundingBox* Fish::GetBoundingBox()const
{
	return (BoundingBox*)m_pBoundingBox;
}