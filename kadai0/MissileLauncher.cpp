//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：MissileLauncher.cpp
// 概要　　　　　：ミサイル発射機のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/14 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "MissileLauncher.h"
#include "GameResource.h"
#include "Missile.h"
#include "CircleBoundingBox.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：台座の座標
// 引数３：台座の角度
//━━━━━━━━━━━━━━━━━━━━━━━
MissileLauncher::MissileLauncher(GameInfo* _pGameInfo, XMFLOAT2 _pedestalPos, float _pedestalAngle)
	: Super(_pGameInfo)
	, m_angle(_pedestalAngle)
	, m_coolDownCnt(0)
	, m_coolDown(rand() % 60 + MISSILELAUNCHER_MIN_ATTACK_INTERVAL)
{
	// 頭の部分と台座の部分を分けて作成する
	m_pImg = CreateSprite(Tex_MissileLauncherHead, MISSILELAUNCHER_HEAD_SIZE_X, MISSILELAUNCHER_HEAD_SIZE_Y);
	m_pImg2 = CreateSprite(Tex_MissileLauncherPedestal, MISSILELAUNCHER_PEDESTAL_SIZE_X, MISSILELAUNCHER_PEDESTAL_SIZE_Y);
	
	// 台座の部分を設置
	m_pImg2->setPos(_pedestalPos);
	m_pImg2->addAngleZ(_pedestalAngle);

	// 頭の部分を設置
	XMFLOAT2 headPos = AngleToDirectionVector(_pedestalAngle + 90.f);
	headPos.x *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.y *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.x += _pedestalPos.x;
	headPos.y += _pedestalPos.y;
	m_pImg->setPos(headPos);
	m_pImg->addAngleZ(_pedestalAngle);

	// バウンディングボックスを作成
	XMFLOAT2 boundingBoxPos = AngleToDirectionVector(_pedestalAngle + 90.f);
	float d = (MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f + MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL + MISSILELAUNCHER_HEAD_SIZE_Y / 2.f) / 2.f - MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f;
	boundingBoxPos.x *= d;
	boundingBoxPos.y *= d;
	boundingBoxPos.x += _pedestalPos.x;
	boundingBoxPos.y += _pedestalPos.y;
	m_pBoundingBox = new CircleBoundingBox(boundingBoxPos, d - MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
MissileLauncher::~MissileLauncher()
{
	if (m_pImg)delete m_pImg;
	m_pImg = NULL;
	delete m_pImg2;
	delete m_pBoundingBox;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画する
//━━━━━━━━━━━━━━━━━━━━━━━
void MissileLauncher::renderSprite()
{
	RenderSprite(m_pImg);
	RenderSprite(m_pImg2);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// エネミーの攻撃
//━━━━━━━━━━━━━━━━━━━━━━━
void MissileLauncher::AttackProcess(XMFLOAT2 _SubmarinePos)
{
	// 弾を打つ速度の制御
	if (m_coolDownCnt < m_coolDown)
	{
		++m_coolDownCnt;
	}
	else
	{
		m_coolDown = rand() % 60 + MISSILELAUNCHER_MIN_ATTACK_INTERVAL;
		// カウンターをリセットする
		m_coolDownCnt = 0;

		// 弾の座標を計算
		XMFLOAT4 pos = m_pImg->getPos();
		{
			XMFLOAT2 pos2 = AngleToDirectionVector(m_angle - 180.f);
			pos.x += pos2.x * (ENEMY_1_SIZE_X / 2.f) + pos2.x * 10.f;
			pos.y += pos2.y * (ENEMY_1_SIZE_X / 2.f) + pos2.y * 10.f;
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
						m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new Missile(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle - 180.f)));
						break;
					}
				}
				else
				{
					if ((*m_pEnemyBullet)[i]->GetBulletType() == missile)
					{
						// あったらそれを使う
						(*m_pEnemyBullet)[i]->SetActive(true);
						(*m_pEnemyBullet)[i]->SetPos(XMFLOAT2(pos.x, pos.y));
						(*m_pEnemyBullet)[i]->SetMoveDirection(m_angle - 180.f);
						break;
					}
				}
			}
		}
		else
		{
			m_pEnemyBullet->push_back(shared_ptr<EnemyBullet>(new Missile(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle - 180.f)));
		}
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// エネミーの移動（このエネミーは移動しないため、回転のみ）
// 引数１：潜水艦の座標
//━━━━━━━━━━━━━━━━━━━━━━━
void MissileLauncher::MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime)
{
	// ミサイル発射機の頭の部分の回転
	{
		// 今向いている方向のベクトルを取得
		XMFLOAT2 vector = AngleToDirectionVector(m_angle);

		// ミサイル発射機の頭の部分から潜水艦までのベクトルを取り、正規化する
		XMFLOAT2 vector2 = FindVectorByTwoPos(_SubmarinePos, m_pImg2->getPos());
		NormalizeVector(vector2);

		// 頭の部分の回転
		if (CrossProduct(vector, vector2) > 0.f)
		{
			float angle = Degree(RadianToDegree(acosf(vector.x * vector2.x + vector.y * vector2.y)));
			if (Abs(angle) > MISSILELAUNCHER_MAX_ROTATE_SPEED)
			{
				m_angle += MISSILELAUNCHER_MAX_ROTATE_SPEED;
			}
			else
			{
				m_angle += angle;
			}
		}
		else
		{
			float angle = Degree(RadianToDegree(acosf(vector.x * vector2.x + vector.y * vector2.y)));
			if (Abs(angle) > MISSILELAUNCHER_MAX_ROTATE_SPEED)
			{
				m_angle -= MISSILELAUNCHER_MAX_ROTATE_SPEED;
			}
			else
			{
				m_angle -= angle;
			}
		}
	}
	// 頭の部分の上下反転
	{
		// 台座から頭までのベクトルを取り、正規化する
		XMFLOAT2 vector = FindVectorByTwoPos(m_pImg2->getPos(), m_pImg->getPos());
		NormalizeVector(vector);

		// 今向いている方向のベクトルを取得
		XMFLOAT2 vector2 = AngleToDirectionVector(m_angle);

		if (CrossProduct(vector, vector2) > 0.f)
		{
			// 左だったら、画像のＹ軸の回転を１８０°にする
			m_pImg->setAngle(0.f, 0.f, m_angle + 180.f);
		}
		else
		{
			// 右だったら、画像のＹ軸の回転を０°にする
			m_pImg->setAngle(0.f, 180.f, m_angle);
		}
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスを取得
//━━━━━━━━━━━━━━━━━━━━━━━
BoundingBox* MissileLauncher::GetBoundingBox()const
{
	return m_pBoundingBox;
}

void MissileLauncher::SetPosAndAngle(XMFLOAT2 _newPos, float _newAngle)
{
	m_pImg2->setPos(_newPos);
	m_pImg2->setAngleZ(_newAngle);
	
	XMFLOAT2 headPos = AngleToDirectionVector(_newAngle + 90.f);
	headPos.x *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.y *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.x += _newPos.x;
	headPos.y += _newPos.y;
	m_pImg->setPos(headPos);

	XMFLOAT2 boundingBoxPos = AngleToDirectionVector(_newAngle + 90.f);
	float d = (MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f + MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL + MISSILELAUNCHER_HEAD_SIZE_Y / 2.f) / 2.f - MISSILELAUNCHER_PEDESTAL_SIZE_Y / 2.f;
	boundingBoxPos.x *= d;
	boundingBoxPos.y *= d;
	boundingBoxPos.x += _newPos.x;
	boundingBoxPos.y += _newPos.y;
	m_pBoundingBox->SetPos(boundingBoxPos);
}