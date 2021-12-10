//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：EnemyBullet.cpp
// 概要　　　　　：プレイヤーの弾のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/11/07 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "EnemyBullet.h"
#include "Define.h"
#include "GameResource.h"
#include "CircleBoundingBox.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：弾の初期座標
// 引数３：弾の初期移動方向（角度）
//━━━━━━━━━━━━━━━━━━━━━━━
EnemyBullet::EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Super(_pGameInfo)
	, m_pBoundingBox(NULL)
{
	m_pImg = CreateSprite(Tex_EnemyBullet, ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y);
	m_pImg->setPos(_pos);
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));

	m_pBoundingBox = new CircleBoundingBox(_pos, ENEMY_BULLET_BOUNDING_BOX_RADIUS);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
EnemyBullet::~EnemyBullet()
{
	DisposeSprite(m_pImg);
	delete m_pBoundingBox;
}


//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の弾の画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
void EnemyBullet::renderSprite()
{
	if (m_pImg->getActive())
	{
		RenderSprite(m_pImg);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の弾の画像の位置をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void EnemyBullet::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の弾の画像画像が表示可能か
//━━━━━━━━━━━━━━━━━━━━━━━
bool EnemyBullet::GetActive()const
{
	return m_pImg->getActive();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の弾の画像を表示可能（不可）にする
//━━━━━━━━━━━━━━━━━━━━━━━
void EnemyBullet::SetActive(bool _b)
{
	return m_pImg->setActive(_b);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の弾の移動方向をセットする
// 引数１：新しい移動方向（角度）
//━━━━━━━━━━━━━━━━━━━━━━━
void EnemyBullet::SetMoveDirection(float _angle)
{
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 移動の処理
//━━━━━━━━━━━━━━━━━━━━━━━
void EnemyBullet::MoveProcess(float _deltaTime)
{
	if (m_pImg->getActive())
	{
		m_pImg->offsetPos(XMFLOAT4(m_moveDirection.x * ENEMY_BULLET_MOVE_SPEED * _deltaTime, m_moveDirection.y * ENEMY_BULLET_MOVE_SPEED * _deltaTime, 0.f, 0.f));
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

//━━━━━━━━━━━━━━━━━━━━━━━
// 当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
BoundingBox* EnemyBullet::GetBoundingBox() const
{
	return m_pBoundingBox;
}

