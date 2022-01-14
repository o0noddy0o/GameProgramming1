//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：RectangleBoundingBox.cpp
// 概要　　　　　：四角形バウンディングボックスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/26 作成
// 　　　　　　　：2021/11/27 コリジョンの実装
// 　　　　　　　：2021/12/26 丸いバウンディングボックスとの当たり判定を修正
// 　　　　　　　：2021/12/26 全部のコリジョンメソッドに二つ目の引数を追加
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
	, Super(2)
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
// 他バウンディングボックスとの当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(const BoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	if (_target->m_boundingBoxType == 1)
	{
		return Collision((CircleBoundingBox*)_target, _pDirectionVector);
	}
	else if (_target->m_boundingBoxType == 2)
	{
		return Collision((RectangleBoundingBox*)_target, _pDirectionVector);
	}
	else if (_target->m_boundingBoxType == 3)
	{
		return Collision((PolygonBoundingBox*)_target, _pDirectionVector);
	}
	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像との当たり判定
// 引数１：対象の画像
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(CPicture* _target, XMFLOAT2* _pDirectionVector)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	if (_pDirectionVector)
	{
		// 接触面を計算する
		XMFLOAT2 contactSurface;

		contactSurface.x = ((m_size.x + targetSize.x) - Abs((m_pos.x - m_size.x / 2.f) - (targetPos.x - targetSize.x / 2.f)) - Abs((m_pos.x + m_size.x / 2.f) - (targetPos.x + targetSize.x / 2.f))) / 2.f;
		contactSurface.y = ((m_size.y + targetSize.y) - Abs((m_pos.y - m_size.y / 2.f) - (targetPos.y - targetSize.y / 2.f)) - Abs((m_pos.y + m_size.y / 2.f) - (targetPos.y + targetSize.y / 2.f))) / 2.f;
	
		if (contactSurface.x > contactSurface.y)
		{
			_pDirectionVector->y = -_pDirectionVector->y;
		}
		else
		{
			_pDirectionVector->x = -_pDirectionVector->x;
		}
	}

	return true;
}

bool RectangleBoundingBox::CollisionWithCircle(const CircleBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	float targetRadius = _target->GetRadius();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + m_size.x / 2.f + targetRadius)return false;
	if (m_pos.x < targetPos.x - m_size.x / 2.f - targetRadius)return false;
	if (m_pos.y > targetPos.y + m_size.y / 2.f + targetRadius)return false;
	if (m_pos.y < targetPos.y - m_size.y / 2.f - targetRadius)return false;

	// ターゲットが自分の斜めの方向じゃない場合
	if (Abs(targetPos.x - m_pos.x) < m_size.x / 2.f)
	{
		if (Abs(targetPos.y - m_pos.y) < (m_size.y / 2.f + targetRadius))
		{
			throw 1;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (Abs(targetPos.y - m_pos.y) < m_size.y / 2.f)
	{
		if (Abs(targetPos.x - m_pos.x) < (m_size.x / 2.f + targetRadius))
		{
			throw 2;
			return true;
		}
		else
		{
			return false;
		}
	}

	// 斜め方向にある場合
	XMFLOAT2 vertex;
	// ターゲットが右
	if (m_pos.x < targetPos.x)
	{
		// ターゲットが上
		if (m_pos.y < targetPos.y)
		{
			vertex = { m_pos.x + m_size.x / 2.f, m_pos.y + m_size.y / 2.f };
		}
		// ターゲットが下
		else
		{
			vertex = { m_pos.x + m_size.x / 2.f, m_pos.y - m_size.y / 2.f };
		}
	}
	// ターゲットが左
	else
	{
		// ターゲットが上
		if (m_pos.y < targetPos.y)
		{
			vertex = { m_pos.x - m_size.x / 2.f, m_pos.y + m_size.y / 2.f };
		}
		// ターゲットが下
		else
		{
			vertex = { m_pos.x - m_size.x / 2.f, m_pos.y - m_size.y / 2.f };
		}
	}

	// 頂点とターゲットの座標の距離を計算する
	XMFLOAT2 coordinateDifference = { targetPos.x - vertex.x, targetPos.y - vertex.y };
	float distance = FindDistanceByCoordinateDifference(coordinateDifference);

	// 距離がターゲットの半径より大きい場合
	if (distance > targetRadius)
	{
		return false;
	}
	// そうではない場合
	else
	{
		throw 3;
		return true;
	}

	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 丸いバウンディングボックスとの当たり判定
// 引数１：対象の丸いバウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(const CircleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	try
	{
		// 当たってなかったらfalseを返す
		if (!CollisionWithCircle(_target))return false;

		// 移動方向がない場合はそのままtrueを返す
		if (!_pDirectionVector)return true;
	}

	// 当たっている且つ移動方向のポインターがNULLではない場合は
	// 当たった後の移動方向を計算する
	catch (int num)
	{
		if (!_pDirectionVector)return true;
		//━━━━━━━━━━━━━━━━━━
		// "num"の説明：
		//━━━━━━━━━━━━━━━━━━
		// num が１の場合：
		// 　ターゲットが自分の上か、下にある
		// 
		// num が２の場合：
		// 　ターゲットが自分の左か、右にある
		// 
		// num が３の場合：
		// 　ターゲットが自分の斜め方向にある
		//━━━━━━━━━━━━━━━━━━
		switch (num)
		{
			case 1:
			{
				if ((_pDirectionVector->y < 0.f && _target->GetPos().y < m_pos.y) ||
					(_pDirectionVector->y > 0.f && _target->GetPos().y > m_pos.y))
				{
					_pDirectionVector->y = -_pDirectionVector->y;
				}
			}
			break;

		case 2:
			{
				if ((_pDirectionVector->x < 0.f && _target->GetPos().x < m_pos.x) ||
					(_pDirectionVector->x > 0.f && _target->GetPos().x > m_pos.x))
				{
					_pDirectionVector->x = -_pDirectionVector->x;
				}
			}
			break;

		case 3:
			{
				if (!((_pDirectionVector->y < 0.f && _target->GetPos().y < m_pos.y) ||
					(_pDirectionVector->y > 0.f && _target->GetPos().y > m_pos.y)))
				if (!((_pDirectionVector->x < 0.f && _target->GetPos().x < m_pos.x) ||
					(_pDirectionVector->x > 0.f && _target->GetPos().x > m_pos.x)))break;

				// 必要な情報を揃える
				XMFLOAT2 targetRelativePos = _target->GetPos();
				targetRelativePos.x -= m_pos.x;
				targetRelativePos.y -= m_pos.y;

				bool up = targetRelativePos.y > 0.f;
				bool right = targetRelativePos.x > 0.f;

				targetRelativePos.x = Abs(targetRelativePos.x);
				targetRelativePos.y = Abs(targetRelativePos.y);

				float r = _target->GetRadius();

				XMFLOAT2 line = { m_size.x / 2.f, m_size.y / 2.f };

				float x;
				float y;

				{
					float x1 = r * r - line.y * line.y - 2.f * line.y * targetRelativePos.y + targetRelativePos.y * targetRelativePos.y;
					x1 = Abs(x1);
					x = -sqrtf(x1) + targetRelativePos.x;
				}
				{
					float y1 = r * r - line.x * line.x - 2.f * line.x * targetRelativePos.x + targetRelativePos.x * targetRelativePos.x;
					y1 = Abs(y1);
					y = -sqrtf(y1) + targetRelativePos.y;
				}

				XMFLOAT2 point[2] = {{ x, line.y }, { line.x, y}};
				if (!right)
				{
					point[0].x = -point[0].x;
					point[1].x = -point[1].x;
				}
				if (!up)
				{
					point[0].y = -point[0].y;
					point[1].y = -point[1].y;
				}

				// point[0]からpoint[1]までのベクトルを計算する
				XMFLOAT2 vector = { point[1].x - point[0].x, point[1].y - point[0].y };

				// 単位化する
				float d = FindDistanceByCoordinateDifference(vector);
				vector.x /= d;
				vector.y /= d;

				// ベクトルを回転する
				XMFLOAT2 newVector;
				if (up)
				{
					if (right)
					{
						newVector.x = vector.x * cosf(DegreeToRadian(90.f)) - vector.y * sinf(DegreeToRadian(90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(90.f)) + vector.y * cosf(DegreeToRadian(90.f));
					}
					else
					{
						newVector.x = vector.x * cosf(DegreeToRadian(-90.f)) - vector.y * sinf(DegreeToRadian(-90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(-90.f)) + vector.y * cosf(DegreeToRadian(-90.f));
					}
				}
				else
				{
					if (right)
					{
						newVector.x = vector.x * cosf(DegreeToRadian(-90.f)) - vector.y * sinf(DegreeToRadian(-90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(-90.f)) + vector.y * cosf(DegreeToRadian(-90.f));
					}
					else
					{
						newVector.x = vector.x * cosf(DegreeToRadian(90.f)) - vector.y * sinf(DegreeToRadian(90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(90.f)) + vector.y * cosf(DegreeToRadian(90.f));
					}
				}

				// 元の方向ベクトルの大きさを保存しておく
				float m = FindDistanceByCoordinateDifference(*_pDirectionVector);

				// 元の方向ベクトルの単位ベクトル
				XMFLOAT2 directionVector = *_pDirectionVector;
				directionVector.x /= m;
				directionVector.y /= m;

				float cosAngle = -directionVector.x * newVector.x + -directionVector.y * newVector.y;

				// 元の方向ベクトルがnewVector上の投影
				XMFLOAT2 vector2 = newVector;
				vector2.x *= cosAngle;
				vector2.y *= cosAngle;

				XMFLOAT2 newDirectionVector = directionVector;

				newDirectionVector.x = newDirectionVector.x + vector2.x * 2.f * m;
				newDirectionVector.y = newDirectionVector.y + vector2.y * 2.f * m;

				*_pDirectionVector = newDirectionVector;
			}
			break;
		}
	}
	return true;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 四角形バウンディングボックスとの当たり判定
// 引数１：対象の四角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(const RectangleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	if (_pDirectionVector)
	{
		// 接触面を計算する
		XMFLOAT2 contactSurface;

		contactSurface.x = ((m_size.x + targetSize.x) - Abs((m_pos.x - m_size.x / 2.f) - (targetPos.x - targetSize.x / 2.f)) - Abs((m_pos.x + m_size.x / 2.f) - (targetPos.x + targetSize.x / 2.f))) / 2.f;
		contactSurface.y = ((m_size.y + targetSize.y) - Abs((m_pos.y - m_size.y / 2.f) - (targetPos.y - targetSize.y / 2.f)) - Abs((m_pos.y + m_size.y / 2.f) - (targetPos.y + targetSize.y / 2.f))) / 2.f;

		if (contactSurface.x > contactSurface.y)
		{
			if ((_pDirectionVector->y > 0.f && targetPos.y > m_pos.y) ||
				(_pDirectionVector->y < 0.f && targetPos.y < m_pos.y))
			{
				_pDirectionVector->y = -_pDirectionVector->y;
			}
			else if((_pDirectionVector->x > 0.f && targetPos.x > m_pos.x) ||
				(_pDirectionVector->x < 0.f && targetPos.x < m_pos.x))
			{
				_pDirectionVector->x = -_pDirectionVector->x;
			}
		}
		else
		{
			if ((_pDirectionVector->x > 0.f && targetPos.x > m_pos.x) ||
				(_pDirectionVector->x < 0.f && targetPos.x < m_pos.x))
			{
				_pDirectionVector->x = -_pDirectionVector->x;
			}
			else if((_pDirectionVector->y > 0.f && targetPos.y > m_pos.y) ||
				(_pDirectionVector->y < 0.f && targetPos.y < m_pos.y))
			{
				_pDirectionVector->y = -_pDirectionVector->y;
			}
		}
	}

	return true;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 多角形バウンディングボックスとの当たり判定
// 引数１：対象の多角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool RectangleBoundingBox::Collision(const PolygonBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	RectangleBoundingBox ob(m_pos, m_size, m_relativePos);

	return _target->Collision(&ob);
}