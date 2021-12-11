//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Enemy.cpp
// 概要　　　　　：敵クラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/03 作成
//			　　　2021/12/08　敵の弾を発射機能を追加
//			　　　2021/12/10　敵の移動処理を追加
//━━━━━━━━━━━━━━━━━━━━━━━
#include "GameResource.h"
#include "Enemy.h"
#include "BoundingBox.h"

// ━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Enemy::Enemy(GameInfo* _pGameInfo)
	:CObjectBase(_pGameInfo)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Enemy::~Enemy()
{
	DisposeSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
void Enemy::renderSprite()
{
	RenderSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の取得
//━━━━━━━━━━━━━━━━━━━━━━━
shared_ptr<vector<shared_ptr<EnemyBullet>>> Enemy::GetBullet()
{
	return m_pEnemyBullet;
}




