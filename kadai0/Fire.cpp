//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Fire.cpp
// 概要　　　　　：火の弾のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/19 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Fire.h"
#include "Define.h"
#include "GameResource.h"
#include "CircleBoundingBox.h"

Fire::Fire(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _moveDirection, int _disappearTime)
	: Super(_pGameInfo, TypeOfEnemyBullet::fire)
	, m_disappearCnt(0)
	, m_disappearTime(_disappearTime)
{
	// 初期化
	m_moveDirection = _moveDirection;

	if (m_bulletType == TypeOfEnemyBullet::fire)
	{
		// 画像作成
		m_pImg = CreateSprite(Tex_Fire, FIRE_SIZE_X, FIRE_SIZE_Y);
		m_pImg->setPos(_pos);
		m_pImg->setAngleZ(DirectionVectorToAngle(_moveDirection) - 90.f);
		m_pBoundingBox = new CircleBoundingBox(_pos, FIRE_SIZE_X);
	}
}

Fire::~Fire()
{
}

void Fire::renderSprite()
{
	if (m_pImg->getActive())
	{
		RenderSprite(m_pImg, XMFLOAT4(1.f, 1.f, 1.f, (1.f / (float)m_disappearTime) * (m_disappearTime - m_disappearCnt)));

		++m_disappearCnt;
		if (m_disappearCnt > m_disappearTime)
		{
			m_pImg->setActive(false);
		}
	}
}

void Fire::MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos)
{
	if (m_pImg->getActive())
	{
		m_pImg->offsetPos(XMFLOAT4(m_moveDirection.x * FIRE_MOVE_SPEED * _deltaTime, m_moveDirection.y * FIRE_MOVE_SPEED * _deltaTime, 0.f, 0.f));
		XMFLOAT2 newPos = { m_pImg->getPos().x, m_pImg->getPos().y };
		m_pBoundingBox->SetPos(newPos);
		XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

		if (newPos.x > cameraPos.x + 1000.f ||
			newPos.x < cameraPos.x - 1000.f ||
			newPos.y > cameraPos.y + 600.f ||
			newPos.y < cameraPos.y - 600.f)
		{
			m_pImg->setActive(false);
		}
	}
}

void Fire::SetDisappearTime(int _newDisappearTime)
{
	m_disappearTime = _newDisappearTime;
	m_disappearCnt = 0;
}

void Fire::SetMoveDirection(float _angle)
{
	m_pImg->setAngleZ(_angle - 90.f);
	Super::SetMoveDirection(_angle);
}

void Fire::SetMoveDirection(XMFLOAT2 _moveDirection)
{
	m_pImg->setAngleZ(DirectionVectorToAngle(_moveDirection) - 90.f);
	Super::SetMoveDirection(_moveDirection);
}