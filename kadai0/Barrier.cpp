//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Barrier.cpp
// 概要　　　　　：バリアのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/21 作成（呉）
// 　　　　　　　：2021/12/23 InputProcessメソッドの編集（ゲームパッドの実装）（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Barrier.h"
#include "GameResource.h"
#include "Define.h"
#include "CircleBoundingBox.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：バリアの向く方向（初期の角度）
// 引数３：バリアの初期座標（潜水艦の座標そのまま）
//━━━━━━━━━━━━━━━━━━━━━━━
Barrier::Barrier(GameInfo* _pGameInfo, float _angle, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_angle(_angle + 90.f)
	, m_bIsBarrierOn(true)
{
	m_pImg = CreateSprite(Tex_Barrier, BARRIER_SIZE_X, BARRIER_SIZE_Y, kTexelBarrier);
	m_pImg->setPos(_pos);
	m_pImg->setAngleZ(_angle);
	m_pBoundingBox = new CircleBoundingBox(_pos, BARRIER_SIZE_X / 2.f);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Barrier::~Barrier()
{
	if (m_pBoundingBox)delete m_pBoundingBox;
}

bool Barrier::IsBarrierOn()const
{
	return m_bIsBarrierOn;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの入力処理
// 引数１：プレイヤーの番号
// 引数２：前のフレームの処理時間
//━━━━━━━━━━━━━━━━━━━━━━━
void Barrier::InputProcess(int _playerIndex, float _deltaTime)
{
	// ゲームパッドの入力を取得
	float gamepadX = GetInput()->GetAnalogStickX(_playerIndex - 1);
	if (Abs(gamepadX) > 0.05f)
	{
		m_angle -= BARRIER_ROTATION_SPEED * _deltaTime * gamepadX;
		m_pImg->setAngleZ(m_angle - 90.f);
		//m_bIsBarrierOn = false;
	}

	switch (_playerIndex)
	{
	case 1:
		// 左
		if (GetInput()->isKeyPressed(DIK_LEFTARROW))
		{
			m_angle += BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// 右
		else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
		{
			m_angle -= BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// 移動してなかったら、バリアをオンにする
		else
		{
			m_bIsBarrierOn = true;
		}
		break;

	case 2:
		// 左
		if (GetInput()->isKeyPressed(DIK_A))
		{
			m_angle += BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// 右
		else if (GetInput()->isKeyPressed(DIK_D))
		{
			m_angle -= BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// 移動してなかったら、バリアをオンにする
		else
		{
			m_bIsBarrierOn = true;
		}
		break;
	}
	
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バリアの画像を描画する
//━━━━━━━━━━━━━━━━━━━━━━━
void Barrier::renderSprite()
{
	if (m_bIsBarrierOn)
	{
		RenderSprite(m_pImg);
	}
}

float Barrier::GetBarrierAngle()const
{
	return m_angle;
}

BoundingBox* Barrier::GetBoundingBox()const
{
	return m_pBoundingBox;
}

void Barrier::SetPos(XMFLOAT2 _pos)
{
	m_pImg->setPos(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y);
	m_pBoundingBox->SetPos(XMFLOAT2(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y));
}
