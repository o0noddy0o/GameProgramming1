//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：JetEngine.cpp
// 概要　　　　　：ジェットエンジンのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/19 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Define.h"
#include "JetEngine.h"
#include "GameResource.h"

JetEngine::JetEngine(GameInfo* _pGameInfo, XMFLOAT2 _pos, float m_moveDirection)
	: Super(_pGameInfo)
	, m_moveDirection(m_moveDirection)
	, m_bIsMoving(false)
{
	m_pImg = CreateSprite(Tex_JetEngine, JET_ENGINE_SIZE_X, JET_ENGINE_SIZE_Y);
	m_pImg->setPos(_pos);
}

JetEngine::~JetEngine()
{
}

void JetEngine::InputProcess(int _playerIndex, float _deltaTime)
{
	switch (_playerIndex)
	{
	case 1:
		if (GetInput()->isKeyPressed(DIK_LEFTARROW))
		{
			m_moveDirection += JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
		{
			m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}

		if (GetInput()->isKeyPressed(DIK_NUMPAD0))
		{
			m_bIsMoving = true;
		}
		break;
	case 2:
		if (GetInput()->isKeyPressed(DIK_A))
		{
			m_moveDirection += JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		else if (GetInput()->isKeyPressed(DIK_D))
		{
			m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}

		if (GetInput()->isKeyPressed(DIK_SPACE))
		{
			m_bIsMoving = true;
		}
		break;
	}
	
}

bool JetEngine::GetIsMoving()const
{
	return m_bIsMoving;
}

void JetEngine::SetIsMoveingToFalse()
{
	m_bIsMoving = false;
}

float JetEngine::GetMoveDirection()const
{
	return m_moveDirection;
}