//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Player.cpp
// 概要　　　　　：プレイヤーのクラス
// 作成者　　　　：20CU0332 フアンスアンズン
// 更新内容　　　：2021/11/24 作成（ズン）
//				   2021/11/25 基本のメソッドを追加（ズン）
//				   2021/11/26 基本のメソッドを修正（ズン）
//				   2021/11/28 移動メソッドを修正（ズン）
//							  プレイヤー数を分ける（ズン）
//				   2021/12/03 移動メソッドを修正（ズン）
//	
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Player.h"
#include "Define.h"
#include "GameResource.h"
#include "Submarine.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：プレイヤーの初期座標
// 引数３：プレイヤーの座標と潜水艦の座標の差
// 引数４：プレイヤーの番号
//━━━━━━━━━━━━━━━━━━━━━━━
Player::Player(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _relativePos, int _index)
	: Super(_pGameInfo)
	, m_bMoveable(true)
	, m_pJumping(false)
	, m_relativePos(_pos)
	, m__playerIndex(_index)
{
	switch (_index)
	{
	//プレイヤー１の画像を作成
	case 1:
		m_pImg = CreateSprite(Tex_Player1, PLAYER_1_SIZE_X, PLAYER_1_SIZE_Y);
		m_pImg->setPos(_pos);
		break;
	//プレイヤー１の画像を作成
	case 2:
		m_pImg = CreateSprite(Tex_Player2, PLAYER_2_SIZE_X, PLAYER_2_SIZE_Y);
		m_pImg->setPos(_pos);
		break;
	}

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
	InputProcess();
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
	if (_b == false)
	{
		m_bMoveable = false;
	}
	else
	{
		m_bMoveable = true;
	}
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
	switch (getPlayerIdx())
	{
	case 1:
		if (m_bMoveable)
		{
			//左に移動
			if (GetInput()->isKeyPressed(DIK_LEFTARROW))
			{
				m_relativePos.x -= PLAYER_1_MOVE_SPEED;
			}
			//右に移動
			else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
			{
				m_relativePos.x += PLAYER_1_MOVE_SPEED;
			}
		}
		break;
	case 2:
		if (m_bMoveable)
		{
			//左に移動
			if (GetInput()->isKeyPressed(DIK_A))
			{
				m_relativePos.x -= PLAYER_2_MOVE_SPEED;
			}
			//右に移動
			else if (GetInput()->isKeyPressed(DIK_D))
			{
				m_relativePos.x += PLAYER_2_MOVE_SPEED;
			}
		}
		break;
	}
	
	
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
//
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::Jump(float _deltaTime)
{

}

//
CPicture* Player::GetImg() const
{
	return m_pImg;
}

//
int Player::getPlayerIdx() const
{
	return m__playerIndex;
}