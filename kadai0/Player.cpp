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
	, m_bJumping(false)
	, m_jumpPower(0.f)
	, m_jumpTime(0.f)
	, m_relativePos(_pos)
	, m_playerIndex(_index)
	, m_bIsOnFloor(false)
	, m_bMovingLeft(false)
	, m_bMovingRight(false)
{
	switch (_index)
	{
		//プレイヤー１の画像を作成
	case 1:
		m_pImg = CreateSprite(Tex_Player1, PLAYER_SIZE_Y, PLAYER_SIZE_Y);
		m_pImg->setPos(_pos);
		break;
		//プレイヤー１の画像を作成
	case 2:
		m_pImg = CreateSprite(Tex_Player2, PLAYER_SIZE_Y, PLAYER_SIZE_Y);
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
void Player::Tick(float _deltaTime, vector<Submarine::Wall>* _pWall, vector<Submarine::Floor>* _pFloor)
{
	InputProcess();
	CollisionWithWallAndFloor(_pWall, _pFloor);
	Move(_deltaTime);
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
// プレイーの座標を取得
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 Player::GetPos()const
{
	XMFLOAT4 pos = m_pImg->getPos();
	return XMFLOAT2(pos.x, pos.y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイーの座標を更新
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::SetRelativePos(XMFLOAT2 _relativePos)
{
	m_relativePos = _relativePos;
}

XMFLOAT2 Player::GetRelativePos()const
{
	return m_relativePos;
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
			// 左に移動
			if (GetInput()->isKeyPressed(DIK_LEFTARROW))
			{
				m_bMovingLeft = true;
			}
			// 右に移動
			else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
			{
				m_bMovingRight = true;
			}
			if (GetInput()->isKeyPressed(DIK_NUMPAD0))
			{
				Jump();
			}
#if DEBUG
			// 上に移動
			if (GetInput()->isKeyPressed(DIK_UPARROW))
			{
				m_relativePos.y += 20.f;
			}
			// 下に移動
			else if (GetInput()->isKeyPressed(DIK_DOWNARROW))
			{
				m_relativePos.y -= 20.f;
			}
#endif
		}
		break;
	case 2:
		if (m_bMoveable)
		{
			//左に移動
			if (GetInput()->isKeyPressed(DIK_A))
			{
				m_bMovingLeft = true;
			}
			//右に移動
			else if (GetInput()->isKeyPressed(DIK_D))
			{
				m_bMovingRight = true;
			}
			if (GetInput()->isKeyPressed(DIK_SPACE))
			{
				Jump();
			}
#if DEBUG
			// 上に移動
			if (GetInput()->isKeyPressed(DIK_W))
			{
				m_relativePos.y += 20.f;
			}
			// 下に移動
			else if (GetInput()->isKeyPressed(DIK_S))
			{
				m_relativePos.y -= 20.f;
			}
#endif
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
// プレイヤーと壁の当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::CollisionWithWallAndFloor(vector<Submarine::Wall>* _pWall, vector<Submarine::Floor>* _pFloor)
{
	m_bIsOnFloor = false;
	for (int i = 0; i < (int)_pWall->size(); ++i)
	{
		//ジャンプしている時
		if (m_bJumping)
		{
			//プレイヤーが壁の下に当たったら
			if ((*_pWall)[i].ob->collisionBottom(m_pImg) != false)
			{
				m_relativePos.y = (*_pWall)[i].relativePos.y - (*_pWall)[i].ob->getSize().y / 2.f - (PLAYER_SIZE_Y / 2.f);
				m_bJumping = false;
				m_jumpPower = 0.f;
			}
			//壁の下の以外に当たったら
			else
			{
				//右に当たった
				if (m_bMovingRight)
				{
					if ((*_pWall)[i].ob->collisionLeft(m_pImg) != false)
					{
						m_relativePos.x = (*_pWall)[i].relativePos.x - (*_pWall)[i].ob->getSize().x / 2.f - (PLAYER_SIZE_Y / 2.f);
						m_bMovingRight = false;
					}
				}
				//左に当たったら
				else if (m_bMovingLeft)
				{
					if ((*_pWall)[i].ob->collisionRight(m_pImg) != false)
					{
						m_relativePos.x = (*_pWall)[i].relativePos.x + (*_pWall)[i].ob->getSize().x / 2.f + (PLAYER_SIZE_Y / 2.f);
						m_bMovingLeft = false;
					}
				}
			}
		}
		//ジャンプしていない時
		else
		{
			//上
			if ((*_pWall)[i].ob->collisionTop(m_pImg) != false)
			{
				m_relativePos.y = (*_pWall)[i].relativePos.y + (*_pWall)[i].ob->getSize().y / 2.f + (PLAYER_SIZE_Y / 2.f);
				m_bIsOnFloor = true;
				m_jumpPower = 0.f;
			}
			else
			{
				//右
				if (m_bMovingRight)
				{
					if ((*_pWall)[i].ob->collisionLeft(m_pImg) != false)
					{
						m_relativePos.x = (*_pWall)[i].relativePos.x - (*_pWall)[i].ob->getSize().x / 2.f - (PLAYER_SIZE_Y / 2.f);
						m_bMovingRight = false;
					}
				}
				//左
				else if (m_bMovingLeft)
				{
					if ((*_pWall)[i].ob->collisionRight(m_pImg) != false)
					{
						m_relativePos.x = (*_pWall)[i].relativePos.x + (*_pWall)[i].ob->getSize().x / 2.f + (PLAYER_SIZE_Y / 2.f);
						m_bMovingLeft = false;
					}
				}
			}
		}
	}

	//床の当たり判定
	for (int i = 0; i < (int)_pFloor->size(); ++i)
	{
		//ジャンプしている時
		if (m_bJumping)
		{
			//上に
			if ((*_pFloor)[i].ob->collisionBottom(m_pImg) != false)
			{
				m_relativePos.y = (*_pFloor)[i].relativePos.y - (*_pFloor)[i].ob->getSize().y / 2.f - (PLAYER_SIZE_Y / 2.f);
				m_bJumping = false;
				m_jumpPower = 0.f;
			}
			else
			{
				//右に
				if (m_bMovingRight)
				{
					if ((*_pFloor)[i].ob->collisionLeft(m_pImg) != false)
					{
						m_relativePos.x = (*_pFloor)[i].relativePos.x - (*_pFloor)[i].ob->getSize().x / 2.f - (PLAYER_SIZE_Y / 2.f);
						m_bMovingRight = false;
					}
				}
				//左に
				else if (m_bMovingLeft)
				{
					if ((*_pFloor)[i].ob->collisionRight(m_pImg) != false)
					{
						m_relativePos.x = (*_pFloor)[i].relativePos.x + (*_pFloor)[i].ob->getSize().x / 2.f + (PLAYER_SIZE_Y / 2.f);
						m_bMovingLeft = false;
					}
				}
			}
		}
		//ジャンプしていない時
		else
		{
			//下に
			if ((*_pFloor)[i].ob->collisionTop(m_pImg) != false)
			{
				m_relativePos.y = (*_pFloor)[i].relativePos.y + (*_pFloor)[i].ob->getSize().y / 2.f + (PLAYER_SIZE_Y / 2.f);
				m_bIsOnFloor = true;
				m_jumpPower = 0.f;
			}
			else
			{
				//右に
				if (m_bMovingRight)
				{
					if ((*_pFloor)[i].ob->collisionLeft(m_pImg) != false)
					{
						m_relativePos.x = (*_pFloor)[i].relativePos.x - (*_pFloor)[i].ob->getSize().x / 2.f - (PLAYER_SIZE_Y / 2.f);
						m_bMovingRight = false;
					}
				}
				//左に
				else if (m_bMovingLeft)
				{
					if ((*_pFloor)[i].ob->collisionRight(m_pImg) != false)
					{
						m_relativePos.x = (*_pFloor)[i].relativePos.x + (*_pFloor)[i].ob->getSize().x / 2.f + (PLAYER_SIZE_Y / 2.f);
						m_bMovingLeft = false;
					}
				}
			}
		}
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの移動
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::Move(float _deltaTime)
{
	//プレイヤーが潜水艦外に移動しないように
	static XMFLOAT2 BorderOfSubmarine = { (SUBMARINE_SIZE_X - PLAYER_SIZE_X) / 2.f, (SUBMARINE_SIZE_Y - PLAYER_SIZE_Y) / 2.f };

	//右側
	if (m_bMovingRight)
	{
		m_relativePos.x += PLAYER_MOVE_SPEED * _deltaTime;

		if (m_relativePos.x > BorderOfSubmarine.x)
		{
			m_relativePos.x = BorderOfSubmarine.x;
		}

		m_bMovingRight = false;
	}
	//左側
	else if (m_bMovingLeft)
	{
		m_relativePos.x -= PLAYER_MOVE_SPEED * _deltaTime;

		if (m_relativePos.x < -BorderOfSubmarine.x)
		{
			m_relativePos.x = -BorderOfSubmarine.x;
		}

		m_bMovingLeft = false;
	}
	if (!m_bIsOnFloor)
	{
		m_jumpTime += _deltaTime * PLAYER_JUMP_SPEED;
		float moveY = (-GRAVITATION / 2.f) * m_jumpTime * m_jumpTime + m_jumpPower * m_jumpTime;

		if (moveY < 0.f)
		{
			m_bJumping = false;
			if (moveY < -PLAYER_FALLING_SPEED_LIMIT)
			{
				moveY = -PLAYER_FALLING_SPEED_LIMIT;
			}
		}

		m_relativePos.y += moveY;
		if (m_relativePos.y < -BorderOfSubmarine.y)
		{
			m_relativePos.y = -BorderOfSubmarine.y;
		}
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーのジャンプ
//━━━━━━━━━━━━━━━━━━━━━━━
void Player::Jump()
{
	if (!m_bJumping && m_bIsOnFloor)
	{
		m_jumpPower = PLAYER_JUMP_POWER;
		m_jumpTime = 0.f;
		m_bJumping = true;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの画像を取得
//━━━━━━━━━━━━━━━━━━━━━━━
CPicture* Player::GetImg() const
{
	return m_pImg;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーの番号を取得
//━━━━━━━━━━━━━━━━━━━━━━━
int Player::getPlayerIdx() const
{
	return m_playerIndex;
}