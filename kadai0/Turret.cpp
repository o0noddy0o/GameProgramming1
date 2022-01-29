//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Turret.cpp
// 概要　　　　　：タレットのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成（呉）
// 　　　　　　　：2021/11/21 弾を打つのカウントダウンを追加（呉）
// 　　　　　　　：2021/12/23 InputProcessメソッドの編集（ゲームパッドの実装）（呉）
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

	switch(_turretFace % 4)
	{
	case 0:
		m_relativePos.x += TURRET_DISTANCE;
		m_angle = 0.f;
		break;
	case 1:
		m_relativePos.y -= TURRET_DISTANCE;
		m_angle = 270.f;
		break;
	case 2:
		m_relativePos.x -= TURRET_DISTANCE;
		m_angle = 180.f;
		break;
	case 3:
		m_relativePos.y += TURRET_DISTANCE;
		m_angle = 90.f;
		break;
	}

	m_pImg->setAngleZ(m_angle);

	m_rotationRange[0] = m_angle - TURRET_ROTATION_RANGE / 2.f;
	m_rotationRange[1] = m_angle + TURRET_ROTATION_RANGE / 2.f;

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
// 引数１：プレイヤーの番号
// 引数２：前のフレームの処理時間
//━━━━━━━━━━━━━━━━━━━━━━━
void Turret::InputProcess(int _playerIndex, float _deltaTime)
{
	// タレットの回転
	// ゲームパッドの入力を取得
	float gamepadX = GetInput()->GetLeftAnalogStickX(_playerIndex - 1);
	if (Abs(gamepadX) > 0.05f)
	{
		m_angle -= TURRET_ROTATION_SPEED * _deltaTime * gamepadX;
		if (m_angle > m_rotationRange[1])
		{
			m_angle = m_rotationRange[1];
		}
		else if (m_angle < m_rotationRange[0])
		{
			m_angle = m_rotationRange[0];
		}
		m_pImg->setAngleZ(m_angle);
	}
	// キーボード入力
	else
	{
		switch (_playerIndex)
		{
		case 1:
			// 左
			if (GetInput()->isKeyPressed(DIK_LEFTARROW))
			{
				if ((m_angle += TURRET_ROTATION_SPEED * _deltaTime) > m_rotationRange[1])
				{
					// 範囲の制御
					m_angle = m_rotationRange[1];
				}
				m_pImg->setAngleZ(m_angle);
			}
			// 右
			else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
			{
				if ((m_angle -= TURRET_ROTATION_SPEED * _deltaTime) < m_rotationRange[0])
				{
					// 範囲の制御
					m_angle = m_rotationRange[0];
				}
				m_pImg->setAngleZ(m_angle);
			}
			break;
		case 2:
			// 左
			if (GetInput()->isKeyPressed(DIK_A))
			{
				if ((m_angle += TURRET_ROTATION_SPEED * _deltaTime) > m_rotationRange[1])
				{
					// 範囲の制御
					m_angle = m_rotationRange[1];
				}
				m_pImg->setAngleZ(m_angle);
			}
			// 右
			else if (GetInput()->isKeyPressed(DIK_D))
			{
				if ((m_angle -= TURRET_ROTATION_SPEED * _deltaTime) < m_rotationRange[0])
				{
					// 範囲の制御
					m_angle = m_rotationRange[0];
				}
				m_pImg->setAngleZ(m_angle);
			}
			break;
		}
	}

	// 弾を打つ速度の制御
	if (m_coolDownCnt < TURRET_COOL_DOWN)
	{
		m_coolDownCnt += _deltaTime;
	}
	else
	{
		if ((GetInput()->isKeyPressed(DIK_NUMPAD0) && _playerIndex == 1) ||
			(GetInput()->isKeyPressed(DIK_SPACE) && _playerIndex == 2) ||
			 GetInput()->IsGamePadButtonPressed(GAMEPAD_KEY_Action, _playerIndex - 1))
		{
			// カウンターをリセットする
			m_coolDownCnt = 0;

			// 弾の座標を計算
			XMFLOAT4 pos = m_pImg->getPos();
			{
				XMFLOAT2 pos2 = AngleToDirectionVector(m_angle);
				pos.x += pos2.x * (TURRET_SIZE_X / 2.f) + pos2.x * 10.f;
				pos.y += pos2.y * (TURRET_SIZE_X / 2.f) + pos2.y * 10.f;
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

