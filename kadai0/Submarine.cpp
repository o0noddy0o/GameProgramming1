//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Submarine.cpp
// 概要　　　　　：潜水艦のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成（呉）
//				   2021/11/28 移動メソッドを修正（ズン）
//							  プレイヤー数を分ける（ズン）		
//			　　　2021/12/10　敵移動のため、潜水艦座標取得メソッドを追加（林）  
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Submarine.h"
#include "GameResource.h"
#include "Turret.h"
#include "JetEngine.h"
#include "Player.h"
#include "Bullet.h"
#include "Barrier.h"
#include "OperationDevice.h"
#include "UI.h"
#include <string>
#include "CircleBoundingBox.h"
#include "Enemy.h"
#include "EnemyBullet.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Submarine::Submarine(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
	, m_pos(0.f, 0.f)
	, m_hp(SUBMARINE_MAX_HP)
	, m_pBullet{ nullptr }
	, killedEnemyCnt(0)
{
	m_pGameInfo->pCamera->get()->setPos(m_pos.x, m_pos.y, m_pGameInfo->pCamera->get()->getPos().z);

	m_pImg = CreateSprite(Tex_Submarine, SUBMARINE_SIZE_X, SUBMARINE_SIZE_Y);
	m_pImg->setPos(m_pos);

	// 床の作成
	m_floor.push_back(Floor(CreateSprite(Tex_Yuka, 400.f, 10.f), XMFLOAT2(0.f, YUKA_POSITION)));

	// 床の位置を設置する
	for (int i = 0; i < (int)m_floor.size(); ++i)
	{
		m_floor[i].ob->setPos(m_pos.x + m_floor[i].relativePos.x, m_pos.y + m_floor[i].relativePos.y);
	}

	// 壁の画像を作成
	m_wall.push_back(Wall(CreateSprite(Tex_rightup, WALL_1_SIZE_X, WALL_1_SIZE_Y), XMFLOAT2(WALL_1_X, WALL_1_Y)));
	m_wall.push_back(Wall(CreateSprite(Tex_leftup, WALL_2_SIZE_X, WALL_2_SIZE_Y), XMFLOAT2(WALL_2_X, WALL_2_Y)));
	m_wall.push_back(Wall(CreateSprite(Tex_leftdown, WALL_3_SIZE_X, WALL_3_SIZE_Y), XMFLOAT2(WALL_3_X, WALL_3_Y)));
	m_wall.push_back(Wall(CreateSprite(Tex_rightdown, WALL_4_SIZE_X, WALL_4_SIZE_Y), XMFLOAT2(WALL_4_X, WALL_4_Y)));

	// 壁の位置を設置する
	for (int i = 0; i < (int)m_wall.size(); ++i)
	{
		m_wall[i].ob->setPos(m_pos.x + m_wall[i].relativePos.x, m_pos.y + m_wall[i].relativePos.y);
	}

	// プレイヤーオブジェクトの作成
	m_pPlayer[0] = shared_ptr<Player>(new Player(m_pGameInfo, { 0.f, 0.f }, m_pos, 1));
	m_pPlayer[1] = shared_ptr<Player>(new Player(m_pGameInfo, { 0.f, 0.f }, m_pos, 2));

	// 部品オブジェクトのの作成
	m_pComponent[0] = shared_ptr<Component>(new Turret(m_pGameInfo, 0, m_pos));
	m_pComponent[1] = shared_ptr<Component>(new Turret(m_pGameInfo, 1, m_pos));
	m_pComponent[2] = shared_ptr<Component>(new Turret(m_pGameInfo, 2, m_pos));
	m_pComponent[3] = shared_ptr<Component>(new Turret(m_pGameInfo, 3, m_pos));
	m_pComponent[4] = shared_ptr<Component>(new JetEngine(m_pGameInfo));
	m_pComponent[5] = shared_ptr<Component>(new Barrier(m_pGameInfo));

	// 弾の配列のアドレス保存しておく
	for (int i = 0; i < 4; ++i)
	{
		m_pBullet[i] = ((Turret*)(m_pComponent[i].get()))->GetBullet();
	}

	vector<XMFLOAT2> pos = {
		{ 160.f, 0.f },
		{ 0.f, -160.f },
		{ -160.f, 0.f },
		{ 0.f, 160.f },
		{ -64.f, 0.f },
		{ 98.f, 64.f },
	};

	// 操作装置オブジェクトの作成
	for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{
		m_pOperationDevice[i] = shared_ptr<OperationDevice>(new OperationDevice(m_pGameInfo, XMFLOAT2(m_pos.x + pos[i].x, m_pos.y + pos[i].y), pos[i], i));
		m_pOperationDevice[i]->SetComponent(m_pComponent[i]);
	}

	m_pUI = (shared_ptr<UI>)new UI(m_pGameInfo);
	m_pUI->SetNumOfKilledEnemy(0);

	m_pJetEngine = (JetEngine*)m_pComponent[4].get();

	m_pCircleBoundingBox = (shared_ptr<CircleBoundingBox>)new CircleBoundingBox(m_pos, SUBMARINE_SIZE_X / 2.f);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Submarine::~Submarine()
{
	DisposeSprite(m_pImg);

	for (int i = 0; i < (int)m_floor.size(); ++i)
	{
		DisposeSprite(m_floor[i].ob);
	}

	for (int i = 0; i < (int)m_wall.size(); ++i)
	{
		DisposeSprite(m_wall[i].ob);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 毎フレームにやる処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::Tick(float _deltaTime)
{
#if DEBUG
	if (GetInput()->isPressedOnce(DIK_BACKSPACE))
	{
		GetDamaged(20.f);
	}
	if (GetInput()->isPressedOnce(DIK_R))
	{
		m_hp = SUBMARINE_MAX_HP;
		m_pUI->SetHP(m_hp);
	}
#endif

	MoveProcess(_deltaTime);

	MoveCamera(_deltaTime);

#if ShowDeltaTimeAndFPS
	{
		if (!pDeltaTimeText)pDeltaTimeText = (shared_ptr<CText>)new CText(m_pGameInfo, Tex_Text, kTexelText, XMFLOAT2(28.f, 28.f), DeltaTimeText_Pos, XMFLOAT2(5.f, 5.f));

		string deltaTimeText = "DELTA TIME - " + to_string((int)(_deltaTime * 1000.f)) + "\nFPS        - " + to_string((int)(1.f / _deltaTime));
		pDeltaTimeText->SetText(deltaTimeText);
	}
#endif

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < (int)m_pBullet[i]->size(); ++j)
		{
			(*m_pBullet[i])[j]->MoveProcess(_deltaTime);
		}
	}

	for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			m_pOperationDevice[i]->collisionWithPlayer(m_pPlayer[j].get(), _deltaTime);
		}
	}

	m_pPlayer[0]->Tick(_deltaTime, &m_wall, &m_floor);
	m_pPlayer[1]->Tick(_deltaTime, &m_wall, &m_floor);
  
	m_pUI->UpdateMap(GetPos());
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画する
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::RenderProcess()
{
	m_pUI->renderSprite();

	m_pComponent[4]->renderSprite();
	m_pComponent[5]->renderSprite();
	RenderSprite(m_pImg);

	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		// ジェットエンジンとバリアは潜水艦の下の描画する
		if (i == 4 || i == 5)
		{
			continue;
		}
		m_pComponent[i]->renderSprite();
	}

	//操作装置の画像を描画
	for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{
		m_pOperationDevice[i]->RenderDevice();
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < (int)m_pBullet[i]->size(); ++j)
		{
			(*m_pBullet[i])[j]->renderSprite();
		}
	}

	//プレイヤーの画像を描画
	m_pPlayer[0]->RenderChara();
	m_pPlayer[1]->RenderChara();

	// 床
	for (int i = 0; i < (int)m_floor.size(); ++i)
	{
		RenderSprite(m_floor[i].ob);
	}

	// 壁
	for (int i = 0; i < (int)m_wall.size(); ++i)
	{
		RenderSprite(m_wall[i].ob);
	}

#if ShowDeltaTimeAndFPS
	pDeltaTimeText->RenderText(0, COLOR_RED);
#endif
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::CollisionProcess(
	vector < shared_ptr < Enemy> >*							_pEnemy,
	shared_ptr<vector<shared_ptr<EnemyBullet>>>				_pEnemyBullet,
	vector < shared_ptr < SceneryObject > >*				_pSceneryObject,
	vector < shared_ptr < Item > >*							_pItem)
{
	// NULLチェック
	if (_pEnemy)
	{
		for (auto i = _pEnemy->begin(); i != _pEnemy->end();)
		{
			// 敵のバウンディングボックスを取得しておく
			BoundingBox* boundingBox = i->get()->GetBoundingBox();

			// 敵と潜水艦の当たり判定
			if (boundingBox->Collision(m_pCircleBoundingBox.get()))
			{
				GetDamaged(DAMAGE_WHEN_ENEMY_HIT_SUBMARINE);
			}

			// 潜水艦の弾と敵の当たり判定
			bool bEndloop = false;
			for (int j = 0; j < 4; ++j)
			{
				if (m_pBullet[j])
				{
					for (auto i2 = m_pBullet[j]->begin(); i2 != m_pBullet[j]->end(); ++i2)
					{
						if (boundingBox->Collision(i2->get()->GetBoundingBox()))
						{
							if (i == _pEnemy->begin())
							{
								_pEnemy->erase(i);
								i = _pEnemy->begin();
							}
							else
							{
								--i;
								_pEnemy->erase(i + 1);
								++i;
							}
							++killedEnemyCnt;
							m_pUI->SetNumOfKilledEnemy(killedEnemyCnt);
							m_pBullet[j]->erase(i2);
							bEndloop = true;

							break;
						}
					}
					if (bEndloop)
					{
						break;
					}
				}
			}
			if (bEndloop)
			{
				continue;
			}
			++i;
		}
	}

	// NULLチェック
	if (_pEnemyBullet)
	{
		// 敵の弾と潜水艦の当たり判定
		for (int i = 0; i < _pEnemyBullet->size(); ++i)
		{
			for (auto i2 = _pEnemyBullet->begin(); i2 != _pEnemyBullet->end();)
			{
				if (i2->get()->GetBoundingBox()->Collision(m_pCircleBoundingBox.get()))
				{
					GetDamaged(DAMAGE_WHEN_ENEMY_BULLET_HIT_SUBMARINE);
					if (i2 == _pEnemyBullet->begin())
					{
						_pEnemyBullet->erase(i2);
						i2 = _pEnemyBullet->begin();
					}
					else
					{
						--i2;
						_pEnemyBullet->erase(i2 + 1);
						++i2;
					}
					continue;
				}
				++i2;
			}
		}
	}

	// NULLチェック
	if (_pSceneryObject)
	{
	}

	// NULLチェック
	if (_pItem)
	{
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦全体の移動
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::MoveProcess(float _deltaTime)
{
	// 移動中かをチェックする
	if (!m_pJetEngine->GetIsMoving())
	{
		//プレイヤーを一緒に移動させる
		m_pPlayer[0]->SetPos(m_pos);
		m_pPlayer[1]->SetPos(m_pos);

		return;
	}

	float moveDirection = m_pJetEngine->GetMoveDirection();

	// 潜水艦の新しい座標を計算
	XMFLOAT2 offsetPos = AngleToDirectionVector(moveDirection);
	m_pos.x += offsetPos.x * SUBMARINE_MOVE_SPEED / 30.f/* * _deltaTime*/;
	m_pos.y += offsetPos.y * SUBMARINE_MOVE_SPEED / 30.f/* * _deltaTime*/;

	static XMFLOAT2 max = {
		WINDOW_WIDTH / 2.f + WINDOW_WIDTH * (SCREEN_MULTIPLE_X - 1.f) - SUBMARINE_SIZE_X / 2.f,
		WINDOW_HEIGHT / 2.f - SUBMARINE_SIZE_Y / 2.f
	};

	static XMFLOAT2 min = {
		-WINDOW_WIDTH / 2.f + SUBMARINE_SIZE_X / 2.f,
		-WINDOW_HEIGHT / 2.f - WINDOW_HEIGHT * (SCREEN_MULTIPLE_Y - 1.f) + SUBMARINE_SIZE_Y / 2.f
	};

	//潜水艦の移動制御
	if (m_pos.x < min.x)
	{
		m_pos.x = min.x;
	}
	else if (m_pos.x > max.x)
	{
		m_pos.x = max.x;
	}
	if (m_pos.y > max.y)
	{
		m_pos.y = max.y;
	}
	if (m_pos.y < min.y)
	{
		m_pos.y = min.y;
	}


	m_pCircleBoundingBox->SetPos(m_pos);

	// 潜水艦の位置を設置する
	m_pImg->setPos(m_pos);

	for (int i = 0; i < (int)m_floor.size(); ++i)
	{
		m_floor[i].ob->setPos(m_pos.x + m_floor[i].relativePos.x, m_pos.y + m_floor[i].relativePos.y);
	}

	// 壁の位置を設置する
	for (int i = 0; i < (int)m_wall.size(); ++i)
	{
		m_wall[i].ob->setPos(m_pos.x + m_wall[i].relativePos.x, m_pos.y + m_wall[i].relativePos.y);
	}

	// すべて部品を移動させる
	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		m_pComponent[i]->SetPos(m_pos);
	}

	//プレイヤーを一緒に移動させる
	m_pPlayer[0]->SetPos(m_pos);
	m_pPlayer[1]->SetPos(m_pos);

	//操作装置を移動させる
	for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{

		m_pOperationDevice[i]->SetPos(m_pos);
	}

	m_pJetEngine->SetIsMoveingToFalse();


}

//━━━━━━━━━━━━━━━━━━━━━━━
// アイテムを取得した後の処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::GetItem(int _itemType)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラの移動処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::MoveCamera(float _deltaTime)
{
	m_pUI->SetPos();

	// カメラの座標を取得する
	XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

#if ShowDeltaTimeAndFPS
	if (pDeltaTimeText)pDeltaTimeText->setPos(cameraPos.x + DeltaTimeText_Pos_X, cameraPos.y + DeltaTimeText_Pos_Y);
#endif

	// カメラと潜水艦の間の距離を計算
	XMFLOAT2 distanceBetweenCameraAndSubmarine =
	{ m_pos.x - cameraPos.x, m_pos.y - cameraPos.y };

	cameraPos.x += distanceBetweenCameraAndSubmarine.x * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;
	cameraPos.y += distanceBetweenCameraAndSubmarine.y * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;

	static XMFLOAT2 max = {
		WINDOW_WIDTH * (SCREEN_MULTIPLE_X - 1.f),
		0.f
	};

	static XMFLOAT2 min = {
		0.f,
		 -WINDOW_HEIGHT * (SCREEN_MULTIPLE_Y - 1.f)
	};

	//カメラの制御
	if (cameraPos.x < min.x)cameraPos.x = min.x;
	else if (cameraPos.x > max.x)cameraPos.x = max.x;

	if (cameraPos.y > max.y)cameraPos.y = max.y;
	else if (cameraPos.y < min.y)cameraPos.y = min.y;

	m_pGameInfo->pCamera->get()->setPos(cameraPos);

}

float Submarine::GetHp()const
{
	return m_hp;
}


//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦の座標の取得
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT2 Submarine::GetPos()const
{
	XMFLOAT4 SubPos = m_pImg->getPos();
	return XMFLOAT2(SubPos.x, SubPos.y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ダメージを受けた後の処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::GetDamaged(float _damage)
{
	m_hp -= _damage;
	m_pUI->SetHP(m_hp);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦のバウンディングボックスを取得する
//━━━━━━━━━━━━━━━━━━━━━━━
BoundingBox* Submarine::GetBoundingBox()const
{
	return m_pCircleBoundingBox.get();
}

int Submarine::GetKilledEnemyCnt()const
{
	return killedEnemyCnt;
}