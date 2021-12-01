//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CircleBoundingBox.cpp
// 概要　　　　　：丸いバウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Define.h"
#include "CPicture.h"
#include "CircleBoundingBox.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"
#include <math.h>

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：バウンディングボックスの中心座標
// 引数２：バウンディングボックスの半径
// 引数３：バウンディングボックスとそれを持っているオブジェクトの座標の差
//━━━━━━━━━━━━━━━━━━━━━━━
CircleBoundingBox::CircleBoundingBox(XMFLOAT2 _pos, float _radius, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_radius(_radius)
	, m_relativePos(_relativePos)
	, Super(1)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
CircleBoundingBox::~CircleBoundingBox()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの中心座標を取得する
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 CircleBoundingBox::GetPos()const
{
	return m_pos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの半径を取得する
//━━━━━━━━━━━━━━━━━━━━━━━
float CircleBoundingBox::GetRadius()const
{
	return m_radius;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標を設置する
// 引数１：このバウンディングボックスを持つオブジェクトの新しい座標
//━━━━━━━━━━━━━━━━━━━━━━━
void CircleBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの半径を変える
// 引数１：新しい半径
//━━━━━━━━━━━━━━━━━━━━━━━
void CircleBoundingBox::ChangeRadius(float _newRadius)
{
	m_radius = _newRadius;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標とそれを持つオブジェクトの座標の差を変える
// 引数１：新しい距離（差）
//━━━━━━━━━━━━━━━━━━━━━━━
void CircleBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 他バウンディングボックスとの当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
bool CircleBoundingBox::Collision(const BoundingBox* _target)const
{
	if (_target->m_boundingBoxType == 1)
	{
		return Collision((CircleBoundingBox*)_target);
	}
	else if(_target->m_boundingBoxType == 2)
	{
		return Collision((RectangleBoundingBox*)_target);
	}
	else if (_target->m_boundingBoxType == 3)
	{
		return Collision((PolygonBoundingBox*)_target);
	}
	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像との当たり判定
// 引数１：対象の画像
//━━━━━━━━━━━━━━━━━━━━━━━
bool CircleBoundingBox::Collision(CPicture* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + targetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < targetPos.x - targetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > targetPos.y + targetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < targetPos.y - targetSize.y / 2.f - m_radius)return false;

	// 座標の差を計算しておく
	XMFLOAT2 relativePos = { m_pos.x - targetPos.x, m_pos.y - targetPos.y };

	if (Abs(relativePos.x) <= targetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= targetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - targetSize.x / 2.f, Abs(relativePos.y) - targetSize.y };

	if (pos.x * pos.x + pos.y * pos.y <= m_radius * m_radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 丸いバウンディングボックスとの当たり判定
// 引数１：対象の丸いバウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool CircleBoundingBox::Collision(const CircleBoundingBox* _target)const
{
	// 二つの座標の差を計算しておく
	XMFLOAT2 relativePos = { m_pos.x - _target->GetPos().x, m_pos.y - _target->GetPos().y };
	
	return (sqrtf(relativePos.x * relativePos.x + relativePos.y * relativePos.y) <= 
			(m_radius + _target->GetRadius())/* * (m_radius + _target->GetRadius())*/);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 四角形バウンディングボックスとの当たり判定
// 引数１：対象の四角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool CircleBoundingBox::Collision(const RectangleBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + targetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < targetPos.x - targetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > targetPos.y + targetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < targetPos.y - targetSize.y / 2.f - m_radius)return false;

	// 座標の差を計算しておく
	XMFLOAT2 relativePos = { m_pos.x - targetPos.x, m_pos.y - targetPos.y };

	if (Abs(relativePos.x) <= targetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= targetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - targetSize.x / 2.f, Abs(relativePos.y) - targetSize.y };

	if (pos.x * pos.x + pos.y * pos.y <= m_radius * m_radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 多角形バウンディングボックスとの当たり判定
// 引数１：対象の多角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool CircleBoundingBox::Collision(const PolygonBoundingBox* _target)const
{
	return false;
}