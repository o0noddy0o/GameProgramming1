//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Turret.cpp
// 概要　　　　　：タレットのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Turret.h"
#include "Define.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：タレットが向いている方向（０－＞上、１－＞左、２ー＞下、３ー＞右）
// 引数３：潜水艦の座標
//━━━━━━━━━━━━━━━━━━━━━━━
Turret::Turret(GameInfo* _pGameInfo, int _turretFace, XMFLOAT2 _pos)
	: Super(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_Turret, TURRET_SIZE_X, TURRET_SIZE_Y);
	
	m_angle = (float)_turretFace * 90.f;
	m_pImg->setAngleZ(m_angle);

	m_rotationRange[0] = m_angle - TURRET_ROTATION_RANGE / 2.f;
	m_rotationRange[1] = m_angle + TURRET_ROTATION_RANGE / 2.f;

	switch(_turretFace % 4)
	{
	case 0:
		m_relativePos.y += TURRET_DISTANCE;
		break;
	case 1:
		m_relativePos.x -= TURRET_DISTANCE;
		break;
	case 2:
		m_relativePos.y -= TURRET_DISTANCE;
		break;
	case 3:
		m_relativePos.x += TURRET_DISTANCE;
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
	if (GetInput()->isKeyPressed(DIK_A))
	{
		if ((m_angle += TURRET_ROTATION_SPEED) > m_rotationRange[1])
		{
			m_angle = m_rotationRange[1];
		}
		m_pImg->setAngleZ(m_angle);
	}
	else if (GetInput()->isKeyPressed(DIK_D))
	{
		if ((m_angle -= TURRET_ROTATION_SPEED) < m_rotationRange[0])
		{
			m_angle = m_rotationRange[0];
		}
		m_pImg->setAngleZ(m_angle);
	}

	if (GetInput()->isKeyPressed(DIK_SPACE))
	{
		/*for (unsigned int i = 0; i < m_pBullet.size(); ++i)
		{
			if (m_pBullet[i]->GetActive())
			{
				if (i == m_pBullet.size() - 1)
				{
					m_pBullet.push_back(shared_ptr<Bullet>(new Bullet()));
				}
				continue;
			}
			else
			{
				m_pBullet[i]->SetActive(true);
				m_pBullet[i]->SetPos();
				m_pBullet[i]->SetAngle();
				break;
			}
		}*/
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の配列のアドレスを取得する
//━━━━━━━━━━━━━━━━━━━━━━━
vector<shared_ptr<Bullet>>* Turret::GetBullet()
{
	return &m_pBullet;
}