//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Boss.cpp
// 概要　　　　　：ボスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/17 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "CObjectBase.h"
#include <memory>

class EnemyBullet;
class BoundingBox;

class Boss : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Boss(GameInfo* _pGameInfo);
	virtual ~Boss();

	// 毎フレームの処理
	virtual void Tick(XMFLOAT2 _SubmarinePos) = 0;

	// 画像の描画
	virtual void renderSprite();

	virtual vector<BoundingBox*>* GetBoundingBox()const;

public:
	// 弾の配列を取得する
	static shared_ptr<vector<shared_ptr<EnemyBullet>>>	GetBossBullet();

	// 弾の配列をリセットする
	static void ResetBossBullet();

	// 弾の配列のクラス変数
	static shared_ptr<vector<shared_ptr<EnemyBullet>>> m_pBullet;	// 弾

protected:
	vector<CPicture*>		m_pImg;				// 画像
	vector<BoundingBox*>	m_pBoundingBox;
};