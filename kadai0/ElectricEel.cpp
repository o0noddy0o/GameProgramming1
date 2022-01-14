//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：ElectricEel.cpp
// 概要　　　　　：電気ウナギのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/13 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "GameResource.h"
#include "RectangleBoundingBox.h"
#include "ThunderBullet.h"
#include "ElectricEel.h"


ElectricEel::ElectricEel(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Super(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_ElectricEel, ELECTRICEEL_SIZE_X, ELECTRICEEL_SIZE_Y);
	m_pImg->setAngle(0.f, 180.f, _angle);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, XMFLOAT2(ELECTRICEEL_SIZE_X, ELECTRICEEL_SIZE_Y));
}

ElectricEel::~ElectricEel()
{
	delete m_pBoundingBox;
	m_pBoundingBox = NULL;
}

// 攻撃の処理
void ElectricEel::AttackProcess(XMFLOAT2 _SubmarinePos)
{
	// 弾を打つ速度の制御
	if (m_coolDownCnt < m_coolDown)
	{
		++m_coolDownCnt;
	}
	else
	{
		m_coolDown = rand() % 60 + ELECTRICEEL_TURRET_COOL_DOWN;
		// カウンターをリセットする
		m_coolDownCnt = 0;

		// 弾の座標を計算
		XMFLOAT4 pos = m_pImg->getPos();
		{
			XMFLOAT2 pos2 = AngleToDirectionVector(m_angle);
			pos.x += pos2.x * (ELECTRICEEL_SIZE_X / 2.f) + pos2.x * 10.f;
			pos.y += pos2.y * (ELECTRICEEL_SIZE_X / 2.f) + pos2.y * 10.f;
		}

		// 使える弾を探す
		if (m_pEnemyBullet->size() >= 1)
		{
			for (unsigned int i = 0; i < m_pEnemyBullet->size(); ++i)
			{
				if ((*m_pEnemyBullet)[i]->GetActive())
				{
					// なかったら新しいのを作る
					if (i >= m_pEnemyBullet->size() - 1)
					{
						m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new ThunderBullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
						break;
					}
				}
				else
				{
					// あったらそれを使う
					(*m_pEnemyBullet)[i]->SetActive(true);
					(*m_pEnemyBullet)[i]->SetPos(XMFLOAT2(pos.x, pos.y));
					(*m_pEnemyBullet)[i]->SetMoveDirection(m_angle);
					break;
				}
			}
		}
		else
		{
			m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new EnemyBullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
		}
	}
}

// 移動処理
void ElectricEel::MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime)
{
	// 敵の座標を取得
	XMFLOAT4 _EnemyPos = m_pImg->getPos();
	float diffX = _SubmarinePos.x - _EnemyPos.x;
	float diffY = _SubmarinePos.y - _EnemyPos.y;
	float mag = sqrtf(diffX * diffX + diffY * diffY);
	// 敵から潜水艦への方向
	XMFLOAT2 target;
	target.x = diffX / mag;
	target.y = diffY / mag;

	XMFLOAT2 EnemyMoveDir = AngleToDirectionVector(m_angle);

	// 外積の計算
	float cross = (EnemyMoveDir.x * target.y - EnemyMoveDir.y * target.x);

	if (cross >= 0)
	{
		m_angle += 200.f * _deltaTime;
	}
	else
	{
		m_angle -= 200.f * _deltaTime;
	}

	// 敵の移動方向の設定
	EnemyMoveDir = AngleToDirectionVector(m_angle);
	XMFLOAT4 EnemyMove = { EnemyMoveDir.x * ENEMY_1_MOVE_SPEED * _deltaTime, EnemyMoveDir.y * ENEMY_1_MOVE_SPEED * _deltaTime, 0.f, 0.f };
	m_pImg->offsetPos(EnemyMove);
	{
		// 敵の向きの設定
		int angle = Abs((int)m_angle % 360);
		if (angle < 90 || angle > 270)
		{
			m_pImg->setAngle(0.f, 180.f, m_angle);
		}
		else
		{
			m_pImg->setAngle(180.f, 180.f, m_angle);
		}}
	m_pImg->setAngleZ(m_angle);
	m_pBoundingBox->SetPos({ m_pImg->getPos().x, m_pImg->getPos().y });
}