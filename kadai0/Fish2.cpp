//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Fish2.h
// 概要　　　　　：敵クラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/03 作成
//			　　　2021/12/08　敵の弾を発射機能を追加
//			　　　2021/12/10　敵の移動処理を追加
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Define.h"
#include "Fish2.h"
#include "EnemyBullet.h"
#include "GameResource.h"
#include "RectangleBoundingBox.h"

// ━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：敵の初期座標
//━━━━━━━━━━━━━━━━━━━━━━━
Fish2::Fish2(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Enemy(_pGameInfo)
	, m_coolDownCnt(0)
	, m_angle(_angle)
{
	m_pImg = CreateSprite(Tex_Enemy2, ENEMY_2_SIZE_X, ENEMY_2_SIZE_Y);
	m_pImg->setAngle(0.f, 180.f, _angle);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, XMFLOAT2(ENEMY_2_SIZE_X, ENEMY_2_SIZE_Y));
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Fish2::~Fish2()
{
	delete m_pBoundingBox;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 攻撃の処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Fish2::AttackProcess(XMFLOAT2 _SubmarinePos)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 移動処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Fish2::MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime)
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
	XMFLOAT4 EnemyMove = { EnemyMoveDir.x * ENEMY_2_MOVE_SPEED * _deltaTime, EnemyMoveDir.y * ENEMY_2_MOVE_SPEED * _deltaTime, 0.f, 0.f };
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

//━━━━━━━━━━━━━━━━━━━━━━━
// バウンディングボックスの取得
//━━━━━━━━━━━━━━━━━━━━━━━
BoundingBox* Fish2::GetBoundingBox()const
{
	return m_pBoundingBox;
}