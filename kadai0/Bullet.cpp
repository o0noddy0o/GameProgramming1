//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Bullet.cpp
// 概要　　　　　：プレイヤーの弾のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/20 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Bullet.h"
#include "Define.h"
#include "GameResource.h"
#include "CircleBoundingBox.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：弾の初期座標
// 引数３：弾の初期移動方向（角度）
//━━━━━━━━━━━━━━━━━━━━━━━
Bullet::Bullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Super(_pGameInfo)
	, m_pBoundingBox(NULL)
{
	if (!m_pImg)
	{
		m_pImg = CreateSprite(Tex_Bullet, BULLET_SIZE_X, BULLET_SIZE_Y);
		m_pImg->setPos(_pos);
	}
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));

	if(!m_pBoundingBox)m_pBoundingBox = new CircleBoundingBox(_pos, BULLET_BOUNDING_BOX_RADIUS);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Bullet::~Bullet()
{
	DisposeSprite(m_pImg);
	delete m_pBoundingBox;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の画像を取得
//━━━━━━━━━━━━━━━━━━━━━━━
CPicture* Bullet::GetImg()const
{
	return m_pImg;
}

BoundingBox* Bullet::GetBoundingBox()const
{
	return m_pBoundingBox;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
void Bullet::renderSprite()
{
	if (m_pImg->getActive())
	{
		RenderSprite(m_pImg);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の画像の位置をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void Bullet::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の画像画像が表示可能か
//━━━━━━━━━━━━━━━━━━━━━━━
bool Bullet::GetActive()const
{
	return m_pImg->getActive();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の画像を表示可能（不可）にする
//━━━━━━━━━━━━━━━━━━━━━━━
void Bullet::SetActive(bool _b)
{
	return m_pImg->setActive(_b);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の移動方向をセットする
// 引数１：新しい移動方向（角度）
//━━━━━━━━━━━━━━━━━━━━━━━
void Bullet::SetMoveDirection(float _angle)
{
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 移動の処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Bullet::MoveProcess(float _deltaTime)
{
	if (m_pImg->getActive())
	{
		m_pImg->offsetPos(XMFLOAT4(m_moveDirection.x * BULLET_MOVE_SPEED * _deltaTime, m_moveDirection.y * BULLET_MOVE_SPEED * _deltaTime, 0.f, 0.f));
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
// 弾の当たり判定（敵との）
// 引数１：敵の配列のアドレス
//━━━━━━━━━━━━━━━━━━━━━━━
bool Bullet::Collision(vector<shared_ptr<Enemy>>* _target)
{
	return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾の当たり判定（障害物との）
// 引数１：障害物の配列のアドレス
//━━━━━━━━━━━━━━━━━━━━━━━
bool Bullet::Collision(vector<shared_ptr<SceneryObject>>* _target)
{
	return false;
}