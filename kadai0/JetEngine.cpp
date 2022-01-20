//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：JetEngine.cpp
// 概要　　　　　：ジェットエンジンのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/19 作成（呉）
// 　　　　　　　：2021/12/23 InputProcessメソッドの編集（ゲームパッドの実装）、コメントの追加（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Define.h"
#include "JetEngine.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：初期座標
// 引数３：潜水艦の初期移動方向
//━━━━━━━━━━━━━━━━━━━━━━━
JetEngine::JetEngine(GameInfo* _pGameInfo, XMFLOAT2 _pos, float m_moveDirection)
	: Super(_pGameInfo)
	, m_moveDirection(m_moveDirection)
	, m_bIsMoving(false)
{
	m_pImg = CreateSprite(Tex_JetEngine, JET_ENGINE_SIZE_X, JET_ENGINE_SIZE_Y);
	m_pImg->setPos(_pos);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
JetEngine::~JetEngine()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの入力処理
// 引数１：プレイヤーの番号
// 引数２：前のフレームの処理時間
//━━━━━━━━━━━━━━━━━━━━━━━
void JetEngine::InputProcess(int _playerIndex, float _deltaTime)
{
	// タレットの回転
	// ゲームパッドの入力を取得
	float gamepadX = GetInput()->GetAnalogStickX(_playerIndex - 1);
	if (Abs(gamepadX) > 0.05f)
	{
		m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime * gamepadX;
		m_pImg->setAngleZ(m_moveDirection);
	}
	if (GetInput()->IsGamePadButtonPressed(GAMEPAD_KEY_Action, _playerIndex - 1))
	{
		m_bIsMoving = true;
	}

	// キーボードの入力
	switch (_playerIndex)
	{
	case 1:
		// 左
		if (GetInput()->isKeyPressed(DIK_LEFTARROW))
		{
			m_moveDirection += JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		// 右
		else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
		{
			m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		// 移動
		if (GetInput()->isKeyPressed(DIK_NUMPAD0))
		{
			m_bIsMoving = true;
		}
		break;

	case 2:
		// 左
		if (GetInput()->isKeyPressed(DIK_A))
		{
			m_moveDirection += JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		// 右
		else if (GetInput()->isKeyPressed(DIK_D))
		{
			m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}

		// 移動
		if (GetInput()->isKeyPressed(DIK_SPACE))
		{
			m_bIsMoving = true;
		}
		break;
	}
	if (Degree(m_moveDirection) > 90.f && Degree(m_moveDirection) < 270.f)
	{
		m_pImg->setAngle(180.f, 0.f, m_moveDirection);
	}
	else
	{
		m_pImg->setAngle(0.f, 0.f, m_moveDirection);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦の移動フラグを取得
//━━━━━━━━━━━━━━━━━━━━━━━
bool JetEngine::GetIsMoving()const
{
	return m_bIsMoving;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦の移動フラグをfalseにする
//━━━━━━━━━━━━━━━━━━━━━━━
void JetEngine::SetIsMoveingToFalse()
{
	m_bIsMoving = false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 移動方向を取得する
//━━━━━━━━━━━━━━━━━━━━━━━
float JetEngine::GetMoveDirection()const
{
	return m_moveDirection;
}