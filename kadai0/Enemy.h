//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Enemy.h
// 概要　　　　　：敵クラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/03 作成
//			　　　2021/12/08　敵の弾を発射機能を追加
//			　　　2021/12/10　敵の移動処理を追加
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "CObjectBase.h"
#include "Define.h"

class EnemyBullet;
class BoundingBox;

class Enemy :public CObjectBase 
{
public:
	Enemy(GameInfo* _pGameInfo);
	virtual ~Enemy();

	// 画像を取得する
	virtual BoundingBox* GetBoundingBox()const = 0;

	// 画像を描画する
	virtual void renderSprite();

	// 攻撃の処理(ステージ用)
	virtual void AttackProcess() = 0;

	// 移動の処理(ステージ用)
	virtual void MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime) = 0;

	// 弾の配列のアドレスを取得する
	virtual shared_ptr<vector<shared_ptr<EnemyBullet>>> GetBullet();

protected:
	// 敵の画像
	CPicture* m_pImg;

	// 弾の配列
	shared_ptr<vector<shared_ptr<EnemyBullet>>> m_pEnemyBullet;
};
