//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Whale.cpp
// 概要　　　　　：クジラ（ステージ１のボス）のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/17 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Whale.h"
#include "MissileLauncher.h"
#include "GameResource.h"
#include "EnemyBullet.h"
#include "Fire.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：初期座標
//━━━━━━━━━━━━━━━━━━━━━━━
Whale::Whale(GameInfo* _pGameInfo, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_pMissileLauncher(NULL)
	, m_pos(_pos)
{
	// 初期化
	m_nowAction = ActionPattern::none;

	// クジラ本体の画像を作成
	m_pImg.push_back(CreateSprite(Tex_Whale, WHALE_SIZE_X, WHALE_SIZE_Y));
	m_pImg[0]->setPos(_pos);

	// クジラに乗せるミサイル発射機を作成
	XMFLOAT2 missileLauncherPos = _pos;
	missileLauncherPos.x += WHALE_MISSILELAUNCHER_RELATIVE_POS_X;
missileLauncherPos.y += WHALE_MISSILELAUNCHER_RELATIVE_POS_Y;
m_pMissileLauncher = new MissileLauncher(m_pGameInfo, missileLauncherPos);
}

//━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━
Whale::~Whale()
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)
	{
		DisposeSprite(m_pImg[i]);
	}
	if (m_pMissileLauncher)delete (m_pMissileLauncher);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 行動パターンを決める
//━━━━━━━━━━━━━━━━━━━━━━━
void Whale::DecideActionPattern(XMFLOAT2 _SubmarinePos)
{
	// カウンターをリセットする
	m_actionTimeCnt = 0;

	// クジラから潜水艦までのベクトルを取る
	XMFLOAT2 vectorToSubmarine = FindVectorByTwoPos(m_pos, _SubmarinePos);

	// 同じパターンを繰り返さないように
	if (rand() % 2)
	{
		// クジラが火を吹くところから潜水艦までのベクトルを取り、正規化する
		XMFLOAT2 vector = WHALE_PATTERN1_BIOW_FIRE_POS;
		vector.x = _SubmarinePos.x - (vector.x + m_pos.x);
		vector.y = _SubmarinePos.y - (vector.y + m_pos.y);
		
		// 潜水艦が一定程度近づいている
		if (FindDistanceByCoordinateDifference(vector) < WHALE_PATTERN1_BIOW_FIRE_DISTANCE)
		{
			// クジラが火を吹ける角度のcosを計算しておく（内積で使う）
			static float cosBiowFireAngle = cosf(WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f);

			NormalizeVector(vector);

			// 潜水艦が範囲に入っている
			if (vector.x * -1.f > cosBiowFireAngle)
			{
				m_nowAction = ActionPattern::biowFire;
				return;
			}
		}
	}
	else
	{
		// 潜水艦が一定程度近づいている
		if (Abs(vectorToSubmarine.x) < WHALE_PATTERN2_DASH_DISTANCE)
		{
			m_nowAction = ActionPattern::dash;
			return;
		}
	}

	// 残りはランダムで
	m_nowAction = ActionPattern(rand() % (ActionPattern::Total - 3) + 3);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 毎フレームの処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Whale::Tick(XMFLOAT2 _SubmarinePos)
{
	if (m_nowAction == ActionPattern::none)
	{
		DecideActionPattern(_SubmarinePos);
	}
	switch (m_nowAction)
	{
	case ActionPattern::biowFire:		BiowFireProcess(_SubmarinePos);		break;
	case ActionPattern::dash:			DashProcess();						break;
	case ActionPattern::laser:			LaserProcess();						break;
	case ActionPattern::summonEnemy:	SummonEnemyProcess();				break;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像の描画
//━━━━━━━━━━━━━━━━━━━━━━━
void Whale::renderSprite()
{
	if (m_pMissileLauncher)m_pMissileLauncher->renderSprite();
	Super::renderSprite();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 火を噴く時の処理
// 引数１：潜水艦の座標
//━━━━━━━━━━━━━━━━━━━━━━━
void Whale::BiowFireProcess(XMFLOAT2 _SubmarinePos)
{
	if (m_actionTimeCnt++ > WHALE_PATTERN1_DURATION_TIME)
	{
		m_actionTimeCnt = 0;
		m_nowAction = ActionPattern::none;
		return;
	}

	// 弾を生成する座標を計算
	XMFLOAT2 pos = WHALE_PATTERN1_BIOW_FIRE_POS;
	pos.x += m_pos.x;
	pos.y += m_pos.y;

	// クジラが火を吹ける角度のcosを計算しておく（内積で使う）
	static float cosBiowFireAngle = cosf(WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f);

	// クジラの口から潜水艦までのベクトルを計算しておく
	XMFLOAT2 vector = FindVectorByTwoPos(pos, _SubmarinePos);
	NormalizeVector(vector);
	
	bool bOverRange = false;
	float angle;
	if (vector.x * -1.f < cosBiowFireAngle)
	{
		bOverRange = true;
		if (vector.y > 0.f)
		{
			angle = 180.f - WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
		}
		else
		{
			angle = 180.f + WHALE_PATTERN1_BIOW_FIRE_ANGLE / 2.f;
		}
	}

	// 使えるオブジェクトを探す
	for (int i = 0; i < (int)m_pBullet->size(); ++i)
	{
		if ((*m_pBullet)[i]->GetBulletType() == TypeOfEnemyBullet::fire)
		{
			if (!(*m_pBullet)[i]->GetActive())
			{
				(*m_pBullet)[i]->SetPos(pos);
				if (bOverRange)
				{
					(*m_pBullet)[i]->SetMoveDirection(angle);
				}
				else
				{
					(*m_pBullet)[i]->SetMoveDirection(vector);
				}
				(*m_pBullet)[i]->SetActive(true);
				((Fire*)(*m_pBullet)[i].get())->SetDisappearTime(FIRE_DISAPPEAR_TIME);
				return;
			}
		}
	}
	// 見つけなかったら、新しいのを作る
	if (bOverRange)
	{
		m_pBullet->push_back((shared_ptr<EnemyBullet>)new Fire(m_pGameInfo, pos, vector, FIRE_DISAPPEAR_TIME));
		m_pBullet->back()->SetMoveDirection(angle);
	}
	else
	{
		m_pBullet->push_back((shared_ptr<EnemyBullet>)new Fire(m_pGameInfo, pos, vector, FIRE_DISAPPEAR_TIME));
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// レーザーを打つ時の処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Whale::LaserProcess()
{
	m_nowAction = ActionPattern::none;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ダッシュするときの処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Whale::DashProcess()
{
	m_nowAction = ActionPattern::none;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵を召喚するときの処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Whale::SummonEnemyProcess()
{
	m_nowAction = ActionPattern::none;
}