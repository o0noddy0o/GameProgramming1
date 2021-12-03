//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Turret.cpp
// 概要　　　　　：タレットのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成
// 　　　　　　　：2021/11/21 弾を打つのカウントダウンを追加
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Turret.h"
#include "Define.h"
#include "GameResource.h"
#include "Bullet.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：タレットが向いている方向（０－＞右、１－＞上、２ー＞左、３ー＞下）
// 引数３：潜水艦の座標
//━━━━━━━━━━━━━━━━━━━━━━━
Turret::Turret(GameInfo* _pGameInfo, int _turretFace, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_coolDownCnt(0)
{
	m_pImg = CreateSprite(Tex_Turret, TURRET_SIZE_X, TURRET_SIZE_Y);
	
	m_angle = (float)_turretFace * 90.f;
	m_pImg->setAngleZ(m_angle);

	m_rotationRange[0] = m_angle - TURRET_ROTATION_RANGE / 2.f;
	m_rotationRange[1] = m_angle + TURRET_ROTATION_RANGE / 2.f;

	switch(_turretFace % 4)
	{
	case 0:
		m_relativePos.x += TURRET_DISTANCE;
		break;
	case 1:
		m_relativePos.y += TURRET_DISTANCE;
		break;
	case 2:
		m_relativePos.x -= TURRET_DISTANCE;
		break;
	case 3:
		m_relativePos.y -= TURRET_DISTANCE;
		break;
	}

	m_pImg->setPos(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Turret::~Turret()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの入力処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Turret::InputProcess()
{
	if (GetInput()->isKeyPressed(DIK_LEFTARROW))
	{
		if ((m_angle += TURRET_ROTATION_SPEED) > m_rotationRange[1])
		{
			m_angle = m_rotationRange[1];
		}
		m_pImg->setAngleZ(m_angle);
	}
	else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
	{
		if ((m_angle -= TURRET_ROTATION_SPEED) < m_rotationRange[0])
		{
			m_angle = m_rotationRange[0];
		}
		m_pImg->setAngleZ(m_angle);
	}

	// 弾を打つ速度の制御
	if (m_coolDownCnt < TURRET_COOL_DOWN)
	{
		++m_coolDownCnt;
	}
	else
	{
		if (GetInput()->isKeyPressed(DIK_SPACE))
		{
			// カウンターをリセットする
			m_coolDownCnt = 0;

			// 弾の座標を計算
			XMFLOAT4 pos = m_pImg->getPos();
			{
				XMFLOAT2 pos2 = AngleToDirectionVector(m_angle);
				pos.x += pos2.x * (TURRET_SIZE_X / 2.f);
				pos.y += pos2.y * (TURRET_SIZE_X / 2.f);
			}

			// 使える弾を探す
			if (m_pBullet.size() >= 1)
			{
				for (unsigned int i = 0; i < m_pBullet.size(); ++i)
				{
					if (m_pBullet[i]->GetActive())
					{
						// なかったら新しいのを作る
						if (i >= m_pBullet.size() - 1)
						{
							m_pBullet.push_back(shared_ptr<Bullet>(new Bullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
							break;
						}
					}
					else
					{
						// あったらそれを使う
						m_pBullet[i]->SetActive(true);
						m_pBullet[i]->SetPos(XMFLOAT2(pos.x, pos.y));
						m_pBullet[i]->SetMoveDirection(m_angle);
						break;
					}
				}
			}
			else
			{
				m_pBullet.push_back(shared_ptr<Bullet>(new Bullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
			}

		}
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の配列のアドレスを取得する
//━━━━━━━━━━━━━━━━━━━━━━━
vector<shared_ptr<Bullet>>* Turret::GetBullet()
{
	return &m_pBullet;
}

