//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：PolygonBoundingBox.h
// 概要　　　　　：多角形バウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "stdafx.h"
#include "BoundingBox.h"

class PolygonBoundingBox : public BoundingBox
{
	typedef BoundingBox Super;
public:
	// コンストラクタ
	PolygonBoundingBox(XMFLOAT2 _pos, vector<XMFLOAT2>& _vertexPos, XMFLOAT2 _relativePos = { 0.f, 0.f });

	// デストラクタ
	~PolygonBoundingBox();

	// 基本情報の取得
	XMFLOAT2 GetPos()const;					// 中心座標
	XMFLOAT2 GetMaxPos()const;				// 頂点座標の中一番大きいX座標とY座標
	XMFLOAT2 GetMinPos()const;				// 頂点座標の中一番小さいX座標とY座標
	vector<XMFLOAT2>* GetVertexPos()const;	// 頂点座標の配列
	vector<XMFLOAT2>* GetVector()const;		// 頂点座標から頂点座標のベクトルの配列

	// 基本情報の設置
	void SetPos(XMFLOAT2 _pos);
	void ResetVertexPos(vector<XMFLOAT2>& _vertexPos);
	void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f });
	void RotateVertex(float _angle);
	
	// 当たり判定
	bool Collision(const BoundingBox* _target)const;
	bool Collision(CPicture* _target)const;						// 画像
	bool Collision(const CircleBoundingBox* _target)const;		// 丸いバウンディングボックス
	bool Collision(const RectangleBoundingBox* _target)const;	// 四角形バウンディングボックス
	bool Collision(const PolygonBoundingBox* _target)const;		// 多角形バウンディングボックス

private:
	XMFLOAT2						m_pos;			// バウンディングボックスの中心座標
	XMFLOAT2						m_maxPos;		// 頂点座標の中一番大きいX座標とY座標
	XMFLOAT2						m_minPos;		// 頂点座標の中一番小さいX座標とY座標
	shared_ptr<vector<XMFLOAT2>>	m_pVertexPos;	// 頂点座標の配列
	shared_ptr<vector<XMFLOAT2>>	m_pVector;		// 頂点座標から頂点座標のベクトルの配列
	XMFLOAT2						m_relativePos;	// バウンディングボックスとそれを持っているオブジェクトの座標の差
};