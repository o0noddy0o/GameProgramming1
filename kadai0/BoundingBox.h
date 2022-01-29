//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：BoundingBox.h
// 概要　　　　　：バウンディングボックスの仮想クラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/27 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

class CPicture;
class CircleBoundingBox;
class RectangleBoundingBox;
class PolygonBoundingBox;

class BoundingBox
{
public:
	BoundingBox(int _boundingBoxType) :m_boundingBoxType(_boundingBoxType) {}
	virtual ~BoundingBox() {}

	virtual bool Collision(const BoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const = 0;
	virtual bool Collision(CPicture* _target, XMFLOAT2* _pDirectionVector = NULL)const = 0;
	virtual bool Collision(const CircleBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const = 0;
	virtual bool Collision(const RectangleBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const = 0;
	virtual bool Collision(const PolygonBoundingBox* _target, XMFLOAT2* _pDirectionVector = NULL)const = 0;
	virtual void SetPos(XMFLOAT2 _pos) = 0;
	virtual void SetRelativePos(XMFLOAT2 _newRelativePos = { 0.f,0.f }) = 0;
	virtual XMFLOAT2 GetPos()const = 0;

public:
	const int m_boundingBoxType; // 1->〇, 2->□, 3->多角形
};