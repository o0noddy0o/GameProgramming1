//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：EnemyBullet.h
// 概要　　　　　：敵の弾のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/07 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "CObjectBase.h"

class Enemy;
class SceneryObject;
class BoundingBox;
class CircleBoundingBox;

class EnemyBullet : public CObjectBase
{
	typedef CObjectBase Super;
public:
	EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, float _angle = 0.f, int _bulletType = 0);
	~EnemyBullet();

	BoundingBox* GetBoundingBox()const;
	int GetBulletType()const;
	void renderSprite();											// 弾の画像を描画
	void SetPos(XMFLOAT2 _newPos);									// 弾の画像の位置をセットする
	bool GetActive()const;											// 弾の画像画像が表示可能か
	void SetActive(bool _b);										// 弾の画像を表示可能（不可）にする
	void SetMoveDirection(float _angle);							// 弾の移動方向をセットする
	virtual void MoveProcess(float _deltaTime);						// 移動の処理

protected:
	CPicture* m_pImg;			// 弾の画像
	XMFLOAT2 m_moveDirection;	// 弾の移動方向（ベクトル）
	BoundingBox* m_pBoundingBox;
	int m_bulletType;
};