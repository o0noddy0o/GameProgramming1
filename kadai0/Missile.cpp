//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Missile.cpp
// 概要　　　　　：ミサイルのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/14 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Missile.h"
#include "GameResource.h"
#include "Define.h"
#include "CircleBoundingBox.h"

Missile::Missile(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle, bool _bBigSize)
	: Super(_pGameInfo, _pos, _angle, missile)
{
	if (!_bBigSize)
	{
		m_pImg = CreateSprite(Tex_Missile, MISSILE_SIZE_X, MISSILE_SIZE_Y);
	}
	else
	{

	}
	m_pImg->setAngleZ(_angle);
	m_pImg->setPos(_pos);

	float d = (MISSILE_SIZE_X - MISSILE_SIZE_Y) / 2.f;
	XMFLOAT2 boundingBoxPos = _pos;
	boundingBoxPos.x += m_moveDirection.x * d;
	boundingBoxPos.y += m_moveDirection.y * d;
	if (!m_pBoundingBox)m_pBoundingBox = new CircleBoundingBox(boundingBoxPos, MISSILE_SIZE_Y / 2.f);
}

Missile::~Missile()
{
}

void Missile::MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos)
{
	if (m_pImg->getActive())
	{
		// 回転
		{
			XMFLOAT4 pos = m_pImg->getPos();
			XMFLOAT2 vector = FindVectorByTwoPos(pos, _SubmarinePos);
			NormalizeVector(vector);
			
			// 左
			if (CrossProduct(m_moveDirection, vector) > 0.f)
			{
				float angle = Degree(RadianToDegree(acosf(m_moveDirection.x * vector.x + m_moveDirection.y * vector.y)));
				if (Abs(angle) > MISSILE_MAX_ROTATE_SPEED)
				{
					VectorRotation(m_moveDirection, MISSILE_MAX_ROTATE_SPEED);
				}
				else
				{
					VectorRotation(m_moveDirection, angle);
				}
			}
			// 右
			else
			{
				float angle = Degree(RadianToDegree(acosf(m_moveDirection.x * vector.x + m_moveDirection.y * vector.y)));
				if (Abs(angle) > MISSILE_MAX_ROTATE_SPEED)
				{
					VectorRotation(m_moveDirection, -MISSILE_MAX_ROTATE_SPEED);
				}
				else
				{
					VectorRotation(m_moveDirection, -angle);
				}
			}
			m_pImg->setAngleZ(DirectionVectorToAngle(m_moveDirection));
		}
	
		m_pImg->offsetPos(XMFLOAT4(m_moveDirection.x * ENEMY_BULLET_MOVE_SPEED * _deltaTime, m_moveDirection.y * ENEMY_BULLET_MOVE_SPEED * _deltaTime, 0.f, 0.f));
		XMFLOAT2 newPos = { m_pImg->getPos().x, m_pImg->getPos().y };
		m_pBoundingBox->SetPos(newPos);
		XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

		if (newPos.x > cameraPos.x + 1000.f ||
			newPos.x < cameraPos.x - 1000.f ||
			newPos.y > cameraPos.y + 600.f  ||
			newPos.y < cameraPos.y - 600.f)
		{
			m_pImg->setActive(false);
		}
	}
}