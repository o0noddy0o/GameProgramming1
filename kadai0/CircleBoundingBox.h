//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CircleBoundingBox.h
// 概要　　　　　：丸いバウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "stdafx.h"

class CPicture;
class RectangleBoundingBox;
class PolygonBoundingBox;

class CircleBoundingBox
{
public:
	// コンストラクタ
	CircleBoundingBox(XMFLOAT2 _pos, float _radius);

	// デストラクタ
	~CircleBoundingBox();

	// 基本情報んの取得
	XMFLOAT2 GetPos()const;		// 中心座標
	float GetRadius()const;		// 円の半径

	// 当たり判定
	bool Collision(CPicture* _target)const;					// 画像
	bool Collision(CircleBoundingBox* _target)const;		// 丸いバウンディングボックス
	bool Collision(RectangleBoundingBox* _target)const;		// 四角形バウンディングボックス
	bool Collision(PolygonBoundingBox* _target)const;		// 多角形バウンディングボックス

private:
	XMFLOAT2 m_pos;	// バウンディングボックスの中心座標
	float m_radius; // バウンディングボックスの半径
};