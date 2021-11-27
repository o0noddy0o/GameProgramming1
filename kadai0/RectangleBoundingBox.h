//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：RectangleBoundingBox.h
// 概要　　　　　：四角形バウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
// 　　　　　　　：2021/11/27 コリジョンの実装
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "stdafx.h"

class CPicture;
class CircleBoundingBox;
class PolygonBoundingBox;

class RectangleBoundingBox
{
public:
	// コンストラクタ
	RectangleBoundingBox(XMFLOAT2 _pos, XMFLOAT2 _size, XMFLOAT2 _relativePos = { 0.f, 0.f });

	// デストラクタ
	~RectangleBoundingBox();

	// 基本情報の取得
	XMFLOAT2 GetPos()const;
	XMFLOAT2 GetSize()const;

	// 基本情報の設置
	void SetPos(XMFLOAT2 _pos);
	void ChangeSize(XMFLOAT2 _newSize);
	void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f });

	// 当たり判定
	bool Collision(CPicture* _target)const;						// 画像
	bool Collision(const CircleBoundingBox* _target)const;		// 丸いバウンディングボックス
	bool Collision(const RectangleBoundingBox* _target)const;	// 四角形バウンディングボックス
	bool Collision(const PolygonBoundingBox* _target)const;		// 多角形バウンディングボックス

private:
	XMFLOAT2 m_pos;			// バウンディングボックスの中心座標
	XMFLOAT2 m_size;		// バウンディングボックスのサイズ
	XMFLOAT2 m_relativePos;	// バウンディングボックスとそれを持っているオブジェクトの座標の差
};