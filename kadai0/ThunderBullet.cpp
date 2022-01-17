//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：ThunderBullet.cpp
// 概要　　　　　：電気ウナギが使う弾のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/13 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "ThunderBullet.h"
#include "GameResource.h"
#include "Define.h"
#include "CircleBoundingBox.h"

ThunderBullet::ThunderBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Super(_pGameInfo, _pos, _angle, thunderBullet)
{
	m_pImg = CreateSprite(Tex_ThunderBullet, ELECTRICEEL_BULLET_SIZE_X, ELECTRICEEL_BULLET_SIZE_Y);
	m_pImg->setAngleZ(_angle);
	m_pImg->setPos(_pos);
}

ThunderBullet::~ThunderBullet()
{
}

void ThunderBullet::MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos)
{
	if (m_pImg->getActive())
	{
		m_pImg->offsetPos(XMFLOAT4(m_moveDirection.x * ELECTRICEEL_BULLET_MOVE_SPEED * _deltaTime, m_moveDirection.y * ENEMY_BULLET_MOVE_SPEED * _deltaTime, 0.f, 0.f));
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