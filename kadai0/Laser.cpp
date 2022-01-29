//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Laser.cpp
// 概要　　　　　：レーザーのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/20 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Laser.h"
#include "GameResource.h"
#include "Define.h"
#include "PolygonBoundingBox.h"


//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：レーザーのサイズ
// 引数３：レーザーの始点座標（発射点）
// 引数４：レーザーの方向
// 引数５：レーザーは前へ移動するか否か
//━━━━━━━━━━━━━━━━━━━━━━━
Laser::Laser(GameInfo* _pGameInfo, XMFLOAT2 _size, XMFLOAT2 _startPointPos, float _angle, bool _bMove)
	: Super(_pGameInfo, TypeOfEnemyBullet::laser)
	, m_size(_size)
	, m_angle(Degree(_angle))
	, m_pos(_startPointPos)
	, m_bMove(_bMove)
{
	if (m_bulletType == TypeOfEnemyBullet::laser)
	{
		// レーザーの画像を作成し、設置する
		m_pImg = CreateSprite(Tex_Laser, _size.x, _size.y);

		// 回転させる
		m_pImg->setAngleZ(m_angle);

		// 座標を計算する
		{
			XMFLOAT2 vector = AngleToDirectionVector(m_angle);
			vector.x *= _size.x / 2.f;
			vector.y *= _size.x / 2.f;

			m_pImg->setPos(_startPointPos.x + vector.x, _startPointPos.y + vector.y);
		}

		vector<XMFLOAT2> vector =
		{
			{ _size.x / 2.f,  _size.y / 2.f},
			{ _size.x / 2.f, -_size.y / 2.f},
			{-_size.x / 2.f, -_size.y / 2.f},
			{-_size.x / 2.f,  _size.y / 2.f},
		};
		m_pBoundingBox = new PolygonBoundingBox(_startPointPos, vector, true, XMFLOAT2(_size.x / 2.f, 0.f));
		((PolygonBoundingBox*)m_pBoundingBox)->RotateVertex(m_angle);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Laser::~Laser()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// レーザーの始点座標をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void Laser::SetPos(XMFLOAT2 _newStartPointPos)
{
	// 新しい座標を保存しておく
	m_pos = _newStartPointPos;

	// バウンディングボックスを新しい座標に設置する
	m_pBoundingBox->SetPos(_newStartPointPos);

	// 画像の新しい座標を計算する
	XMFLOAT2 vector = AngleToDirectionVector(m_angle);
	vector.x *= m_size.x / 2.f;
	vector.y *= m_size.x / 2.f;

	// 画像を新しい座標に設置する
	m_pImg->setPos(m_pos.x + vector.x, m_pos.y + vector.y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// レーザーの方向をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void Laser::SetAngle(float _angle)
{
	// バウンディングボックスを回転させる
	((PolygonBoundingBox*)m_pBoundingBox)->RotateVertex(_angle - m_angle);

	// 新しい角度を保存しておく
	m_angle = _angle;

	// 画像を回転させる
	m_pImg->setAngleZ(m_angle);

	// 画像の新しい座標を計算する
	XMFLOAT2 vector = AngleToDirectionVector(m_angle);
	vector.x *= m_size.x / 2.f;
	vector.y *= m_size.x / 2.f;

	// 画像を新しい座標に設置する
	m_pImg->setPos(m_pos.x + vector.x, m_pos.y + vector.y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// レーザーの方向を加算する
//━━━━━━━━━━━━━━━━━━━━━━━
void Laser::SetOffsetAngle(float _angle)
{
	// バウンディングボックスを回転させる
	((PolygonBoundingBox*)m_pBoundingBox)->RotateVertex(_angle);

	// 新しい角度を計算しておく
	m_angle += _angle;

	// 画像を回転させる
	m_pImg->setAngleZ(m_angle);

	// 画像の新しい座標を計算する
	XMFLOAT2 vector = AngleToDirectionVector(m_angle);
	vector.x *= m_size.x / 2.f;
	vector.y *= m_size.x / 2.f;

	// 画像を新しい座標に設置する
	m_pImg->setPos(m_pos.x + vector.x, m_pos.y + vector.y);
}

void Laser::MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos)
{
	if (!m_bMove)return;
	Super::MoveProcess(_deltaTime, _SubmarinePos);
}