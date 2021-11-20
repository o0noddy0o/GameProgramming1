//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Bullet.h
// 概要　　　　　：プレイヤーの弾のｎクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/20 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "CObjectBase.h"

class Enemy;
class SceneryObject;

class Bullet : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Bullet(GameInfo* _pGameInfo, XMFLOAT2 _pos = {0.f, 0.f}, float _angle = 0.f);
	~Bullet();

	CPicture* GetImg()const;										// 弾の画像を取得
	void renderSprite();											// 弾の画像を描画
	void SetPos(XMFLOAT2 _newPos);									// 弾の画像の位置をセットする
	bool GetActive()const;											// 弾の画像画像が表示可能か
	void SetActive(bool _b);										// 弾の画像を表示可能（不可）にする
	void SetMoveDirection(float _angle);							// 弾の移動方向をセットする
	void MoveProcess(float _deltaTime);								// 移動の処理
	bool Collision(vector<shared_ptr<Enemy>>* _target);				// 弾の当たり判定（敵との）
	bool Collision(vector<shared_ptr<SceneryObject>>* _target);		// 弾の当たり判定（障害物との）

private:
	CPicture* m_pImg;			// 弾の画像
	XMFLOAT2 m_moveDirection;	// 弾の移動方向（ベクトル）
};