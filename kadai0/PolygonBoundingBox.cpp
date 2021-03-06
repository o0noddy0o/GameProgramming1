//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：PolygonBoundingBox.cpp
// 概要　　　　　：多角形バウンディングボックスのクラス
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
// 引数２：バウンディングボックスの頂点座標の配列（基本は時計回り順）
// 　　　：※ 要素は二つ以上
// 引数３：バウンディングボックスとそれを持っているオブジェクトの座標の差
//━━━━━━━━━━━━━━━━━━━━━━━
PolygonBoundingBox::PolygonBoundingBox(XMFLOAT2 _pos, vector<XMFLOAT2>& _vertexPos, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_pVertexPos(new vector<XMFLOAT2>(_vertexPos))
	, m_pVector(new vector<XMFLOAT2>())
	, m_relativePos(_relativePos)
	, Super(3)
{
	// 頂点座標の配列の要素数を取得しておく
	int arraySize = (int)m_pVertexPos->size();

	// 要素数が３以上
	if (arraySize >= 3)
	{
		XMFLOAT2 pos;			// i番目の座標
		XMFLOAT2 pos1;			// i+1番目の座標
		for (int i = 0; i < arraySize; ++i)
		{
			// 今回処理する座標を保存しておく
			if (i < arraySize - 1)
			{
				if (i == 0)
				{
					pos = (*m_pVertexPos)[i];
					pos1 = (*m_pVertexPos)[i + 1];
				}
				else
				{
					pos = pos1;
					pos1 = (*m_pVertexPos)[i + 1];
				}
			}
			else
			{
				pos = pos1;
				pos1 = (*m_pVertexPos)[0];
			}

			// 座標の最大値と最小値の計算
			if (i == 0)
			{
				m_maxPos = pos;
				m_minPos = pos;
			}
			else
			{
				// X座標
				if		(pos.x > m_maxPos.x)m_maxPos.x = pos.x;
				else if (pos.x < m_minPos.x)m_minPos.x = pos.x;

				// Y座標
				if		(pos.y > m_maxPos.y)m_maxPos.y = pos.y;
				else if (pos.y < m_minPos.y)m_minPos.y = pos.y;
			}

			// ベクトルを計算
			XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

			// 単位化
			float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= distance;
			vector.y /= distance;

			// 保存する
			m_pVector->push_back(vector);
		}
	}
	else if (arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		XMFLOAT2 pos1 = (*m_pVertexPos)[1];

		// 座標の最大値と最小値の計算
		{
			m_maxPos = pos;
			m_minPos = pos;
			// X座標
			if		(pos1.x > m_maxPos.x)m_maxPos.x = pos1.x;
			else if (pos1.x < m_minPos.x)m_minPos.x = pos1.x;
			// Y座標
			if		(pos1.y > m_maxPos.y)m_maxPos.y = pos1.y;
			else if (pos1.y < m_minPos.y)m_minPos.y = pos1.y;
		}

		// ベクトルを計算
		XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

		// 単位化
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= distance;
		vector.y /= distance;

		// 保存する
		m_pVector->push_back(vector);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
PolygonBoundingBox::~PolygonBoundingBox()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標を取得
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 PolygonBoundingBox::GetPos()const
{
	return m_pos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 頂点座標の中一番大きいX座標とY座標を取得
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 PolygonBoundingBox::GetMaxPos()const
{
	return m_maxPos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 頂点座標の中一番小さいX座標とY座標を取得
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 PolygonBoundingBox::GetMinPos()const
{
	return m_minPos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 頂点座標の配列を取得
//━━━━━━━━━━━━━━━━━━━━━━━
vector<XMFLOAT2>* PolygonBoundingBox::GetVertexPos()const
{
	return m_pVertexPos.get();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 頂点座標から頂点座標のベクトルの配列を取得
//━━━━━━━━━━━━━━━━━━━━━━━
vector<XMFLOAT2>* PolygonBoundingBox::GetVector()const
{
	return m_pVector.get();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標を設置する
// 引数１：このバウンディングボックスを持つオブジェクトの新しい座標
//━━━━━━━━━━━━━━━━━━━━━━━
void PolygonBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの頂点座標をセットしなおす
// 引数１：新しい頂点座標の配列
//━━━━━━━━━━━━━━━━━━━━━━━
void PolygonBoundingBox::ResetVertexPos(vector<XMFLOAT2>& _vertexPos)
{
	// 頂点座標の配列の要素数を取得しておく
	int arraySize = (int)m_pVertexPos->size();

	// 要素数が３以上
	if (arraySize >= 3)
	{
		m_pVertexPos->clear();
		m_pVector->clear();

		XMFLOAT2 pos;			// i番目の座標
		XMFLOAT2 pos1;			// i+1番目の座標
		for (int i = 0; i < arraySize; ++i)
		{
			// 今回処理する座標を保存しておく
			if (i < arraySize - 1)
			{
				if (i == 0)
				{
					pos = (*m_pVertexPos)[i];
					pos1 = (*m_pVertexPos)[i + 1];
				}
				else
				{
					pos = pos1;
					pos1 = (*m_pVertexPos)[i + 1];
				}
			}
			else
			{
				pos = pos1;
				pos1 = (*m_pVertexPos)[0];
			}

			// 座標の最大値と最小値の計算
			if (i == 0)
			{
				m_maxPos = pos;
				m_minPos = pos;
			}
			else
			{
				// X座標
				if (pos.x > m_maxPos.x)m_maxPos.x = pos.x;
				else if (pos.x < m_minPos.x)m_minPos.x = pos.x;

				// Y座標
				if (pos.y > m_maxPos.y)m_maxPos.y = pos.y;
				else if (pos.y < m_minPos.y)m_minPos.y = pos.y;
			}

			// ベクトルを計算
			XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

			// 単位化
			float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= distance;
			vector.y /= distance;

			// 保存する
			m_pVector->push_back(vector);
		}
	}
	else if (arraySize == 2)
	{
		m_pVertexPos->clear();
		m_pVector->clear();

		XMFLOAT2 pos = (*m_pVertexPos)[0];
		XMFLOAT2 pos1 = (*m_pVertexPos)[1];

		// 座標の最大値と最小値の計算
		{
			m_maxPos = pos;
			m_minPos = pos;
			// X座標
			if (pos1.x > m_maxPos.x)m_maxPos.x = pos1.x;
			else if (pos1.x < m_minPos.x)m_minPos.x = pos1.x;
			// Y座標
			if (pos1.y > m_maxPos.y)m_maxPos.y = pos1.y;
			else if (pos1.y < m_minPos.y)m_minPos.y = pos1.y;
		}

		// ベクトルを計算
		XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

		// 単位化
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= distance;
		vector.y /= distance;

		// 保存する
		m_pVector->push_back(vector);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの座標とそれを持つオブジェクトの座標の差を変える
// 引数１：新しい距離（差）
//━━━━━━━━━━━━━━━━━━━━━━━
void PolygonBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスを回転する
// 引数１：回転する角度
//━━━━━━━━━━━━━━━━━━━━━━━
void PolygonBoundingBox::RotateVertex(float _angle)
{
	// 頂点座標の配列の要素数を取得しておく
	int arraySize = (int)m_pVertexPos->size();

	if (arraySize < 2)return;

	float radian = DegreeToRadian(-_angle);

	{
		XMFLOAT2 newRelativePos;
		if (m_relativePos.x != 0.f && m_relativePos.y != 0.f)
		{
			newRelativePos =
			{
				m_relativePos.x * cosf(radian) - m_relativePos.y * sinf(radian),
				m_relativePos.x * sinf(radian) + m_relativePos.y * cosf(radian)
			};
		}

		XMFLOAT2 pos;
		for (int i = 0; i < arraySize; ++i)
		{
			pos = (*m_pVertexPos)[i];

			if (m_relativePos.x != 0.f && m_relativePos.y != 0.f)
			{
				pos.x += m_relativePos.x;
				pos.y += m_relativePos.y;
			}

			(*m_pVertexPos)[i].x = pos.x * cosf(radian) - pos.y * sinf(radian);
			(*m_pVertexPos)[i].y = pos.x * sinf(radian) + pos.y * cosf(radian);

			if (m_relativePos.x != 0.f && m_relativePos.y != 0.f)
			{
				pos.x -= newRelativePos.x;
				pos.y -= newRelativePos.y;
			}
		}
	}

	// 要素数が３以上
	if (arraySize >= 3)
	{
		m_pVector->clear();
		XMFLOAT2 pos;			// i番目の座標
		XMFLOAT2 pos1;			// i+1番目の座標
		for (int i = 0; i < arraySize; ++i)
		{
			// 今回処理する座標を保存しておく
			if (i < arraySize - 1)
			{
				if (i == 0)
				{
					pos = (*m_pVertexPos)[i];
					pos1 = (*m_pVertexPos)[i + 1];
				}
				else
				{
					pos = pos1;
					pos1 = (*m_pVertexPos)[i + 1];
				}
			}
			else
			{
				pos = pos1;
				pos1 = (*m_pVertexPos)[0];
			}

			// 座標の最大値と最小値の計算
			if (i == 0)
			{
				m_maxPos = pos;
				m_minPos = pos;
			}
			else
			{
				// X座標
				if (pos.x > m_maxPos.x)m_maxPos.x = pos.x;
				else if (pos.x < m_minPos.x)m_minPos.x = pos.x;

				// Y座標
				if (pos.y > m_maxPos.y)m_maxPos.y = pos.y;
				else if (pos.y < m_minPos.y)m_minPos.y = pos.y;
			}

			// ベクトルを計算
			XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

			// 単位化
			float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= distance;
			vector.y /= distance;

			// 保存する
			m_pVector->push_back(vector);
		}
	}
	else if (arraySize == 2)
	{
		m_pVector->clear();
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		XMFLOAT2 pos1 = (*m_pVertexPos)[1];

		// 座標の最大値と最小値の計算
		{
			m_maxPos = pos;
			m_minPos = pos;
			// X座標
			if (pos1.x > m_maxPos.x)m_maxPos.x = pos1.x;
			else if (pos1.x < m_minPos.x)m_minPos.x = pos1.x;
			// Y座標
			if (pos1.y > m_maxPos.y)m_maxPos.y = pos1.y;
			else if (pos1.y < m_minPos.y)m_minPos.y = pos1.y;
		}

		// ベクトルを計算
		XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

		// 正規化
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= distance;
		vector.y /= distance;

		// 保存する
		m_pVector->push_back(vector);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 他バウンディングボックスとの当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
bool PolygonBoundingBox::Collision(const BoundingBox* _target)const
{
	if (_target->m_boundingBoxType == 1)
	{
		return Collision((CircleBoundingBox*)_target);
	}
	else if (_target->m_boundingBoxType == 2)
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
bool PolygonBoundingBox::Collision(CPicture* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x + m_minPos.x > targetPos.x + targetSize.x / 2.f)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetSize.x / 2.f)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetSize.y / 2.f)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetSize.y / 2.f)return false;

	// 画像の四つ頂点を計算する
	XMFLOAT2 vertex[4] = { XMFLOAT2(targetPos.x, targetPos.y) };
	{
		vertex[0].x += targetSize.x / 2.f;
		vertex[1].x += targetSize.x / 2.f;
		vertex[2].x -= targetSize.x / 2.f;
		vertex[3].x -= targetSize.x / 2.f;
		vertex[0].y += targetSize.y / 2.f;
		vertex[1].y -= targetSize.y / 2.f;
		vertex[2].y -= targetSize.y / 2.f;
		vertex[3].y += targetSize.y / 2.f;
	}

	int arraySize = (int)m_pVertexPos->size();
	if (arraySize >= 3)
	{
		{
			XMFLOAT2 vector;
			XMFLOAT2 pos;
			for (int i = 0; i < arraySize; ++i)
			{
				// 今計算する頂点の座標を保存しておく
				pos = (*m_pVertexPos)[i];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				for (int j = 0; j < 4; ++j)
				{
					// 計算用のベクトル
					vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

					// 正規化
					float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
					vector.x /= r;
					vector.y /= r;

					// 外積
					float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

					// 右にある場合はこれ以上やっても意味ないからbreak
					if (z < 0.f)
					{
						break;
					}

					// 最後まで全部左にあればfalseをreturn
					if (j == 3)
					{
						return false;
					}
				}
			}
		}

		// ここまでやっても結果が出ない場合
		// ターゲットからもう一度やる

		// 画像の単位ベクトル
		XMFLOAT2 vector[4] = { {0.f, 0.f} };	
		vector[0].y = -1;
		vector[1].x = -1;
		vector[2].y = 1;
		vector[3].x = 1;

		// 頂点座標
		XMFLOAT2 pos;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < arraySize; ++j)
			{
				// 今やる頂点の座標を保存しておく
				pos = (*m_pVertexPos)[j];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				// 計算用のベクトル
				XMFLOAT2 vector2 = { pos.x - vertex[i].x , pos.y - vertex[i].y };

				// 正規化
				float r = sqrtf(vector2.x * vector2.x + vector2.y * vector2.y);
				vector2.x /= r;
				vector2.y /= r;

				// 外積
				float z = vector[i].x * vector2.y - vector[i].y * vector2.x;

				// 右にある場合はこれ以上やっても意味ないからbreak
				if (z < 0.f)
				{
					break;
				}

				// 最後まで全部左にあればfalseをreturn
				if (j == arraySize - 1)
				{
					return false;
				}
			}
		}
		return true;
	}
	else if(arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		pos.x += m_pos.x;
		pos.y += m_pos.y;

		XMFLOAT2 vector;
		for (int j = 0; j < 4; ++j)
		{
			// 計算用のベクトル
			vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

			// 正規化
			float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= r;
			vector.y /= r;

			// 外積
			float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

			// 右にある場合はtrue
			if (z < 0.f)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 丸いバウンディングボックスとの当たり判定
// 引数１：対象の丸いバウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool PolygonBoundingBox::Collision(const CircleBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	float targetRadius = _target->GetRadius();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x + m_minPos.x > targetPos.x + targetRadius)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetRadius)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetRadius)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetRadius)return false;

	// 頂点数を取得
	int arraySize = (int)m_pVertexPos->size();

	// 頂点数が３以上（図形）
	if (arraySize >= 3)
	{
		// 計算用の変数
		XMFLOAT2 targetVector;
		XMFLOAT2 pos;
		int cnt = 0;

		// 円の中心点がどの線の左にあるかを調べる
		for (int i = 0; i < arraySize; ++i)
		{
			// 現在処理中の頂点の座標を取得しておく
			pos = (*m_pVertexPos)[i];
			pos.x += m_pos.x;
			pos.y += m_pos.y;

			// 現在処理中の頂点から円の中心までのベクトル
			targetVector = { targetPos.x - pos.x,targetPos.y - pos.y };

			// ベクトルの正規化
			XMFLOAT2 vector = targetVector;
			float d = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= d;
			vector.y /= d;

			// 外積
			float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

			// 右だったら、これ以上やっても意味ない
			if (z < 0)
			{
				++cnt;
				continue;
			}
			// 左だったら
			// 垂直線の長さを計算
			float d2 = d * z;

			// 垂直線が円の半径より長い
			if (d2 > targetRadius)
			{
				return false;
			}

			// 次の頂点の座標を取得しておく
			XMFLOAT2 pos2 = (*m_pVertexPos)[(i == arraySize - 1) ? (0) : (i + 1)];
			pos2.x += m_pos.x;
			pos2.y += m_pos.y;

			XMFLOAT2 pos1ToPos2Vector = { pos2.x - pos.x, pos2.y - pos.y };
			XMFLOAT2 pos2ToPos1Vector = { -pos1ToPos2Vector.x, -pos1ToPos2Vector.y };
			XMFLOAT2 targetVector2 = { targetPos.x - pos2.x, targetPos.y - pos2.y };

			float lengthOfline = sqrtf(pos1ToPos2Vector.x * pos1ToPos2Vector.x + pos1ToPos2Vector.y * pos1ToPos2Vector.y);
			float d3 = sqrtf(targetPos.x * targetPos.x + targetPos.y * targetPos.y);

			if (d > lengthOfline + targetRadius)
			{
				return false;
			}
			if (d3 > lengthOfline + targetRadius)
			{
				return false;
			}

			if (d < targetRadius)
			{
				return true;
			}

			if (d3 < targetRadius)
			{
				return true;
			}
			++cnt;
		}
		if (cnt >= arraySize)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// 頂点数が２（線）
	else if(arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];

		// ターゲットへのベクトル
		XMFLOAT2 targetVector = { targetPos.x - pos.x,targetPos.y - pos.y };

		// ベクトルの正規化
		XMFLOAT2 vector = targetVector;
		float d = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= d;
		vector.y /= d;

		// 外積
		float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

		// 右だったら、これ以上やっても意味ない
		if (z < 0)return true;

		// 左だったら
		// 垂直線の長さを計算
		float d2 = d * z;

		// 垂直線が円の半径より長い
		if (d2 > targetRadius)return true;

		// 次の頂点の座標を取得しておく
		XMFLOAT2 pos2 = (*m_pVertexPos)[1];
		pos2.x += m_pos.x;
		pos2.y += m_pos.y;

		XMFLOAT2 pos1ToPos2Vector = { pos2.x - pos.x, pos2.y - pos.y };
		XMFLOAT2 pos2ToPos1Vector = { -pos1ToPos2Vector.x, -pos1ToPos2Vector.y };
		XMFLOAT2 targetVector2 = { targetPos.x - pos2.x, targetPos.y - pos2.y };

		float lengthOfline = sqrtf(pos1ToPos2Vector.x * pos1ToPos2Vector.x + pos1ToPos2Vector.y * pos1ToPos2Vector.y);
		float d3 = sqrtf(targetPos.x * targetPos.x + targetPos.y * targetPos.y);

		if (d > lengthOfline + targetRadius)
		{
			return false;
		}
		if (d3 > lengthOfline + targetRadius)
		{
			return false;
		}

		if (d < targetRadius)
		{
			return true;
		}

		if (d3 < targetRadius)
		{
			return true;
		}
	}
	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 四角形バウンディングボックスとの当たり判定
// 引数１：対象の四角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool PolygonBoundingBox::Collision(const RectangleBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x + m_minPos.x > targetPos.x + targetSize.x / 2.f)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetSize.x / 2.f)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetSize.y / 2.f)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetSize.y / 2.f)return false;

	// ターゲットの四つ頂点を計算する
	XMFLOAT2 vertex[4] = { targetPos, targetPos, targetPos, targetPos };
	{
		vertex[0].x += targetSize.x / 2.f;
		vertex[1].x += targetSize.x / 2.f;
		vertex[2].x -= targetSize.x / 2.f;
		vertex[3].x -= targetSize.x / 2.f;
		vertex[0].y += targetSize.y / 2.f;
		vertex[1].y -= targetSize.y / 2.f;
		vertex[2].y -= targetSize.y / 2.f;
		vertex[3].y += targetSize.y / 2.f;
	}

	int arraySize = (int)m_pVertexPos->size();
	if (arraySize >= 3)
	{
		{
			XMFLOAT2 vector;
			XMFLOAT2 pos;
			for (int i = 0; i < arraySize; ++i)
			{
				// 今計算する頂点の座標を保存しておく
				pos = (*m_pVertexPos)[i];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				for (int j = 0; j < 4; ++j)
				{
					// 計算用のベクトル
					vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

					// 正規化
					float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
					vector.x /= r;
					vector.y /= r;

					// 外積
					float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

					// 右にある場合はこれ以上やっても意味ないからbreak
					if (z < 0.f)
					{
						break;
					}

					// 最後まで全部左にあればfalseをreturn
					if (j == 3)
					{
						return false;
					}
				}
			}
		}

		// ここまでやっても結果が出ない場合
		// ターゲットからもう一度やる

		// ターゲットの単位ベクトル
		XMFLOAT2 vector[4] = { {0.f, 0.f} };
		vector[0].y = -1;
		vector[1].x = -1;
		vector[2].y = 1;
		vector[3].x = 1;

		// 頂点座標
		XMFLOAT2 pos;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < arraySize; ++j)
			{
				// 今やる頂点の座標を保存しておく
				pos = (*m_pVertexPos)[j];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				// 計算用のベクトル
				XMFLOAT2 vector2 = { pos.x - vertex[i].x , pos.y - vertex[i].y };

				// 正規化
				float r = sqrtf(vector2.x * vector2.x + vector2.y * vector2.y);
				vector2.x /= r;
				vector2.y /= r;

				// 外積
				float z = vector[i].x * vector2.y - vector[i].y * vector2.x;

				// 右にある場合はこれ以上やっても意味ないからbreak
				if (z < 0.f)
				{
					break;
				}

				// 最後まで全部左にあればfalseをreturn
				if (j == arraySize - 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	else if (arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		pos.x += m_pos.x;
		pos.y += m_pos.y;

		XMFLOAT2 vector;
		for (int j = 0; j < 4; ++j)
		{
			// 計算用のベクトル
			vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

			// 正規化
			float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= r;
			vector.y /= r;

			// 外積
			float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

			// 右にある場合はtrue
			if (z < 0.f)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 多角形バウンディングボックスとの当たり判定
// 引数１：対象の多角形バウンディングボックス
//━━━━━━━━━━━━━━━━━━━━━━━
bool PolygonBoundingBox::Collision(const PolygonBoundingBox* _target)const
{
	// 対象の座標とサイズを取得しておく
	XMFLOAT2 targetMaxPos = _target->GetMaxPos();
	XMFLOAT2 targetMinPos = _target->GetMinPos();
	XMFLOAT2 targetPos = _target->GetPos();

	// 当たれない場所にいたら、直接falseをreturnする
	if (m_pos.x + m_minPos.x > targetPos.x + targetMaxPos.x)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x + targetMinPos.x)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetMaxPos.y)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y + targetMaxPos.y)return false;

	// ターゲットの頂点数を取得し、頂点座標を計算する
	vector<XMFLOAT2> targetVertex = *(_target->GetVertexPos());
	int targetArraySize = (int)targetVertex.size();
	for (int i = 0; targetArraySize; ++i)
	{
		targetVertex[i].x += targetPos.x;
		targetVertex[i].y += targetPos.y;
	}
	
	// 自分の頂点数を取得する
	int arraySize = (int)m_pVertexPos->size();

	// 頂点数３以上だったら（図形）
	if (arraySize >= 3)
	{
		{
			XMFLOAT2 vector;
			XMFLOAT2 pos;
			for (int i = 0; i < arraySize; ++i)
			{
				// 今計算する頂点の座標を保存しておく
				pos = (*m_pVertexPos)[i];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				for (int j = 0; j < targetArraySize; ++j)
				{
					// 計算用のベクトル
					vector = { targetVertex[j].x - pos.x, targetVertex[j].y - pos.y };

					// 正規化
					float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
					vector.x /= r;
					vector.y /= r;

					// 外積
					float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

					// 右にある場合はこれ以上やっても意味ないからbreak
					if (z < 0.f)
					{
						break;
					}

					// 最後まで全部左にあればfalseをreturn
					if (j == targetArraySize - 1)
					{
						return false;
					}
				}
			}
		}

		// ここまでやっても結果が出ない場合
		// ターゲットからもう一度やる

		// ターゲットのベクトル
		vector<XMFLOAT2> targetVector = *(_target->GetVector());

		// 頂点座標
		XMFLOAT2 pos;
		for (int i = 0; i < targetArraySize; ++i)
		{
			for (int j = 0; j < arraySize; ++j)
			{
				// 今やる頂点の座標を保存しておく
				pos = (*m_pVertexPos)[j];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				// 計算用のベクトル
				XMFLOAT2 vector2 = { pos.x - targetVertex[i].x , pos.y - targetVertex[i].y };

				// 正規化
				float r = sqrtf(vector2.x * vector2.x + vector2.y * vector2.y);
				vector2.x /= r;
				vector2.y /= r;

				// 外積
				float z = targetVector[i].x * vector2.y - targetVector[i].y * vector2.x;

				// 右にある場合はこれ以上やっても意味ないからbreak
				if (z < 0.f)
				{
					break;
				}

				// 最後まで全部左にあればfalseをreturn
				if (j == arraySize - 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	// 頂点数が２だったら（線）
	else if (arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		pos.x += m_pos.x;
		pos.y += m_pos.y;

		XMFLOAT2 vector;
		for (int j = 0; j < 4; ++j)
		{
			// 計算用のベクトル
			vector = { targetVertex[j].x - pos.x, targetVertex[j].y - pos.y };

			// 正規化
			float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= r;
			vector.y /= r;

			// 外積
			float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

			// 右にある場合はtrue
			if (z < 0.f)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}