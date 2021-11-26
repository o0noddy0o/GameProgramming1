//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Player.cpp
// 概要　　　　　：プレイヤーのクラス
// 作成者　　　　：20CU0332 フアンスアンズン
// 更新内容　　　：2021/11/24 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Player.h"
#include "Define.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Player::Player(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _relativePos)
	: Super(_pGameInfo)
	, m_bMoveable(true)
	, m_pJumping(false)
	, m_relativePos(_pos)
{
	m_pImg = CreateSprite(Tex_Player1, 256.f, 256.f);
	m_pImg->setPos(_pos);

}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Player::~Player()
{
	DisposeSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 毎フレームにやる処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::Tick(float _deltaTime)
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::RenderChara()
{
	RenderSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// m_bMoveableの中身を変える
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::SetMoveAble(bool _b)
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイーの座標を更新
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos.x + m_relativePos.x, _newPos.y + m_relativePos.y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの入力処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::InputProcess()
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーキャラクターと各操作装置の当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::CollisionWithOperationDevice(vector<shared_ptr<OperationDevice>>* _pOperationDevice)
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの移動
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::Move(float _deltaTime, bool _right)
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーのジャンプ
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::Jump(float _deltaTime)
{

}
