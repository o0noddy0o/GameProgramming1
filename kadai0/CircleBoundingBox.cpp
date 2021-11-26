//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CircleBoundingBox.cpp
// 概要　　　　　：丸いバウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "CircleBoundingBox.h"
#include "Define.h"
#include "CPicture.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：バウンディングボックスの中心座標
// 引数２：バウンディングボックスの半径
//━━━━━━━━━━━━━━━━━━━━━━━
CircleBoundingBox::CircleBoundingBox(XMFLOAT2 _pos, float _radius)
	: m_pos(_pos)
	, m_radius(_radius)
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
// 画像との当たり判定
// 引数１：対象の画像
//━━━━━━━━━━━━━━━━━━━━━━━
bool CircleBoundingBox::Collision(CPicture* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 tagetSize = _target->getSize();
	XMFLOAT4 tagetPos = _target->getPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > tagetPos.x + tagetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < tagetPos.x - tagetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > tagetPos.y + tagetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < tagetPos.y - tagetSize.y / 2.f - m_radius)return false;

	// 座標の差を計算しておく
	XMFLOAT2 relativePos = { m_pos.x - tagetPos.x, m_pos.y - tagetPos.y };

	if (Abs(relativePos.x) <= tagetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= tagetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - tagetSize.x / 2.f, Abs(relativePos.y) - tagetSize.y };

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
bool CircleBoundingBox::Collision(CircleBoundingBox* _target)const
{
	// 二つの座標の差を計算しておく
	XMFLOAT2 relativePos = { m_pos.x - _target->GetPos().x, m_pos.y - _target->GetPos().y };
	
	return (relativePos.x * relativePos.x + relativePos.y * relativePos.y <= 
			(m_radius + _target->GetRadius()) * (m_radius + _target->GetRadius()));
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 四角形バウンディングボックスとの当たり判定
// 引数１：対象の四角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool CircleBoundingBox::Collision(RectangleBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 tagetSize = _target->GetSize();
	XMFLOAT2 tagetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > tagetPos.x + tagetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < tagetPos.x - tagetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > tagetPos.y + tagetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < tagetPos.y - tagetSize.y / 2.f - m_radius)return false;

	// 座標の差を計算しておく
	XMFLOAT2 relativePos = { m_pos.x - tagetPos.x, m_pos.y - tagetPos.y };

	if (Abs(relativePos.x) <= tagetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= tagetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - tagetSize.x / 2.f, Abs(relativePos.y) - tagetSize.y };

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
bool CircleBoundingBox::Collision(PolygonBoundingBox* _target)const
{
	return false;
}