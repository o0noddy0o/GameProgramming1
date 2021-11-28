//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：RectangleBoundingBox.cpp
// 概要　　　　　：四角形バウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
// 　　　　　　　：2021/11/27 コリジョンの実装
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Define.h"
#include "CPicture.h"
#include "CircleBoundingBox.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：バウンディングボックスの中心座標
// 引数２：バウンディングボックスのサイズ
// 引数３：バウンディングボックスとそれを持っているオブジェクトの座標の差
//━━━━━━━━━━━━━━━━━━━━━━━
RectangleBoundingBox::RectangleBoundingBox(XMFLOAT2 _pos, XMFLOAT2 _size, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_size(_size)
	, m_relativePos(_relativePos)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
RectangleBoundingBox::~RectangleBoundingBox()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標を取得
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 RectangleBoundingBox::GetPos()const
{
	return m_pos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスのサイズを取得
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 RectangleBoundingBox::GetSize()const
{
	return m_size;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標を設置する
// 引数１：このバウンディングボックスを持つオブジェクトの新しい座標
//━━━━━━━━━━━━━━━━━━━━━━━
void RectangleBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスのサイズを変える
// 引数１：新しい座標
//━━━━━━━━━━━━━━━━━━━━━━━
void RectangleBoundingBox::ChangeSize(XMFLOAT2 _newSize)
{
	m_size = _newSize;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標とそれを持つオブジェクトの座標の差を変える
// 引数１：新しい距離（差）
//━━━━━━━━━━━━━━━━━━━━━━━
void RectangleBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像との当たり判定
// 引数１：対象の画像
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(CPicture* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	return true;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 丸いバウンディングボックスとの当たり判定
// 引数１：対象の丸いバウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(const CircleBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	float targetRadius = _target->GetRadius();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + m_size.x / 2.f + targetRadius)return false;
	if (m_pos.x < targetPos.x - m_size.x / 2.f - targetRadius)return false;
	if (m_pos.y > targetPos.y + m_size.y / 2.f + targetRadius)return false;
	if (m_pos.y < targetPos.y - m_size.y / 2.f - targetRadius)return false;

	// 座標の差を計算しておく
	XMFLOAT2 relativePos = { m_pos.x - targetPos.x, m_pos.y - targetPos.y };

	if (Abs(relativePos.x) <= targetRadius)return true;
	if (Abs(relativePos.y) <= targetRadius)return true;

	//float r = sqrtf(m_size.x / 2.f * m_size.x / 2.f + m_size.x / 2.f * m_size.x / 2.f) + targetRadius;
	//float r2 = sqrtf(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
	//XMFLOAT2 pos = { Abs(relativePos.x) - (targetRadius/* + m_size.x / 2.f*/), Abs(relativePos.y) - (targetRadius/* + m_size.y / 2.f*/) };
	//if (pos.x <= 0.f && pos.y <= 0.f)return true;
	//if(r2 < r)return true;

	float d = sqrtf(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
	XMFLOAT2 pos = { relativePos.x / d * targetRadius - m_size.x / 2.f, relativePos.y / d * targetRadius - m_size.y / 2.f };
	if (pos.x < 0.f && pos.y < 0.f)return true;

	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 四角形バウンディングボックスとの当たり判定
// 引数１：対象の四角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(const RectangleBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	return true;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 多角形バウンディングボックスとの当たり判定
// 引数１：対象の多角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(const PolygonBoundingBox* _target)const
{
	return false;
}