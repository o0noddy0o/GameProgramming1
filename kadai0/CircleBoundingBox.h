//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CircleBoundingBox.h
// 概要　　　　　：丸いバウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
// 　　　　　　　：2021/11/27 基本情報を設置するメソッドの追加
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "stdafx.h"
#include "BoundingBox.h"

class CPicture;
class RectangleBoundingBox;
class PolygonBoundingBox;

class CircleBoundingBox : public BoundingBox
{
	typedef BoundingBox Super;
public:
	// コンストラクタ
	CircleBoundingBox(XMFLOAT2 _pos, float _radius, XMFLOAT2 _relativePos = {0.f, 0.f});

	// デストラクタ
	~CircleBoundingBox();

	// 基本情報の取得
	XMFLOAT2 GetPos()const;		// 中心座標
	float GetRadius()const;		// 円の半径

	// 基本情報の設置
	void SetPos(XMFLOAT2 _pos);
	void ChangeRadius(float _newRadius);
	void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f });

	// 当たり判定
	bool Collision(const BoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const;
	bool Collision(CPicture* _target, XMFLOAT2* _pDirectionVector = NULL)const;						// 画像
	bool Collision(const CircleBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const;		// 丸いバウンディングボックス
	bool Collision(const RectangleBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const;	// 四角形バウンディングボックス
	bool Collision(const PolygonBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const;		// 多角形バウンディングボックス

private:
	bool CollisionWithRectangle(const RectangleBoundingBox* _target)const;

private:
	XMFLOAT2	m_pos;			// バウンディングボックスの中心座標
	float		m_radius;		// バウンディングボックスの半径
	XMFLOAT2	m_relativePos;	// バウンディングボックスとそれを持っているオブジェクトの座標の差
};