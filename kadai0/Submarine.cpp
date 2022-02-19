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
#include "Rock.h"
#include "Whale.h"
#include "CameraManager.h"
#include "Goal.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Submarine::Submarine(GameInfo* _pGameInfo, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_pos(_pos)
	, m_hp(SUBMARINE_MAX_HP)
	, m_pBullet{ nullptr }
	, killedEnemyCnt(0)
	, m_invincibleCnt(0)
	, m_bInvincible(false)
{
	CameraManager::SetCameraPos(m_pos);

	m_pImg = CreateSprite(Tex_Submarine, SUBMARINE_SIZE_X, SUBMARINE_SIZE_Y);
	m_pImg->setPos(m_pos);

	// 床の作成
	m_floor.push_back(Floor(CreateSprite(Tex_Yuka, YUKA_SIZE_X, YUKA_SIZE_Y), XMFLOAT2(0.f, YUKA_POSITION)));
	m_floor.push_back(Floor(CreateSprite(Tex_Yuka, YUKA_UP_SIZE_X, YUKA_UP_SIZE_Y), XMFLOAT2(0.f, YUKA_UP_POSITION)));
	m_floor.push_back(Floor(CreateSprite(Tex_Yuka, YUKA_DOWN_SIZE_X, YUKA_DOWN_SIZE_Y), XMFLOAT2(0.f, YUKA_DOWN_POSITION)));


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

	//ハシゴの画像を作成
	m_ladder.push_back(Ladder(CreateSprite(Tex_Ladder, LADDER_1_SIZE_X, LADDER_1_SIZE_Y), XMFLOAT2(LADDER_1_X, LADDER_1_Y)));
	m_ladder.push_back(Ladder(CreateSprite(Tex_Ladder, LADDER_2_SIZE_X, LADDER_2_SIZE_Y), XMFLOAT2(LADDER_2_X, LADDER_2_Y)));

	//ハシゴの位置を設定する
	for (int i = 0; i < (int)m_ladder.size(); ++i)
	{
		m_ladder[i].ob->setPos(m_pos.x + m_ladder[i].relativePos.x, m_pos.y + m_ladder[i].relativePos.y);
	}

	// プレイヤーオブジェクトの作成
	m_pPlayer[0] = shared_ptr<Player>(new Player(m_pGameInfo, { 0.f, 0.f }, m_pos, 1));
	m_pPlayer[1] = shared_ptr<Player>(new Player(m_pGameInfo, { 0.f, 0.f }, m_pos, 2));

	// 部品オブジェクトのの作成
	m_pComponent[0] = shared_ptr<Component>(new Turret(m_pGameInfo, 0, m_pos));
	m_pComponent[1] = shared_ptr<Component>(new Turret(m_pGameInfo, 1, m_pos));
	m_pComponent[2] = shared_ptr<Component>(new Turret(m_pGameInfo, 2, m_pos));
	m_pComponent[3] = shared_ptr<Component>(new Turret(m_pGameInfo, 3, m_pos));
	m_pComponent[4] = shared_ptr<Component>(new JetEngine(m_pGameInfo, m_pos));
	m_pComponent[5] = shared_ptr<Component>(new Barrier(m_pGameInfo, 0.f, m_pos));

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
		{ 98.f, 0.f },
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

	for (int i = 0; i < (int)m_ladder.size(); ++i)
	{
		DisposeSprite(m_ladder[i].ob);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 毎フレームにやる処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::Tick(float _deltaTime)
{
	if (m_bInvincible)
	{
		if (m_invincibleCnt-- <= 0)
		{
			m_invincibleCnt = 0;
			m_bInvincible = false;
		}
	}

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

	m_pPlayer[0]->Tick(_deltaTime, &m_wall, &m_floor, &m_ladder);
	m_pPlayer[1]->Tick(_deltaTime, &m_wall, &m_floor, &m_ladder);
  
	m_pUI->UpdateMap(GetPos());
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画する
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::RenderProcess()
{
	m_pUI->renderSprite();

	float alphaValue = 1.f;

	if (m_bInvincible && InvincibleFlashingOn)
	{
		alphaValue = INVINCIBLE_ALPHA_VALUE_MIN + Abs(cos(DegreeToRadian((float)(m_invincibleCnt * INVINCIBLE_FLASHING_SPEED)))) * (1.f - INVINCIBLE_ALPHA_VALUE_MIN);
	}

	m_pComponent[4]->renderSprite(alphaValue);
	m_pComponent[5]->renderSprite(alphaValue);
	RenderSprite(m_pImg, XMFLOAT4(1.f, 1.f, 1.f, alphaValue));

	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		// ジェットエンジンとバリアは潜水艦の下の描画する
		if (i == 4 || i == 5)
		{
			continue;
		}
		m_pComponent[i]->renderSprite(alphaValue);
	}

	//操作装置の画像を描画
	for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{
		m_pOperationDevice[i]->RenderDevice(alphaValue);
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
		RenderSprite(m_floor[i].ob, XMFLOAT4(1.f, 1.f, 1.f, alphaValue));
	}

	// 壁
	for (int i = 0; i < (int)m_wall.size(); ++i)
	{
		RenderSprite(m_wall[i].ob, XMFLOAT4(1.f, 1.f, 1.f, alphaValue));
	}

	//ハシゴ
	for (int i = 0; i < (int)m_ladder.size(); ++i)
	{
		RenderSprite(m_ladder[i].ob, XMFLOAT4(1.f, 1.f, 1.f, alphaValue));
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
	Boss*													_pBoss,
	shared_ptr<vector<shared_ptr<EnemyBullet>>>				_pBossBullet,
	Goal*													_pGoal,
	vector < shared_ptr < Item > >*							_pItem)
{
	XMFLOAT2 moveDirection = AngleToDirectionVector(m_pJetEngine->GetMoveDirection());
	Barrier* pBarrier = ((Barrier*)m_pComponent[5].get());
	XMFLOAT2 barrierVector = AngleToDirectionVector(pBarrier->GetBarrierAngle());
	static float cosAngle = cosf(DegreeToRadian(BARRIER_RANGE / 2.f));
	BoundingBox* pBarrierBoundingBox = pBarrier->GetBoundingBox();

	// NULLチェック
	if (_pEnemy)
	{
		for (auto i = _pEnemy->begin(); i != _pEnemy->end();)
		{
			// 敵のバウンディングボックスを取得しておく
			BoundingBox* boundingBox = i->get()->GetBoundingBox();
			XMFLOAT2 moveDirection = i->get()->GetMoveDirection();

			// 敵と潜水艦の当たり判定
			if (pBarrier->IsBarrierOn())
			{
				if (boundingBox->Collision(pBarrierBoundingBox, &moveDirection))
				{
					// 潜水艦から敵までのベクトルを計算
					XMFLOAT2 vectorToEnemy = i->get()->GetBoundingBox()->GetPos();
					vectorToEnemy.x -= m_pos.x;
					vectorToEnemy.y -= m_pos.y;

					// 正規化する
					NormalizeVector(vectorToEnemy);

					// バリアにあたった
					if (barrierVector.x * vectorToEnemy.x + barrierVector.y * vectorToEnemy.y > cosAngle)
					{
						i->get()->HitSubmarineProcess(moveDirection);
					}
					// バリアにあたってない
					else
					{
						// 潜水艦の本体との当たり判定
						if (boundingBox->Collision(m_pCircleBoundingBox.get(), &moveDirection))
						{
							GetDamaged(DAMAGE_WHEN_ENEMY_HIT_SUBMARINE);
							i->get()->HitSubmarineProcess(moveDirection);
						}
					}
				}
			}
			else
			{
				if (boundingBox->Collision(pBarrierBoundingBox, &moveDirection))
				{
					GetDamaged(DAMAGE_WHEN_ENEMY_HIT_SUBMARINE);
					i->get()->SetMoveDirection(moveDirection);
				}
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
		for (auto i = _pEnemyBullet->begin(); i != _pEnemyBullet->end();)
		{
			if (!i->get()->ImgActive()) 
			{
				++i;
				continue;
			}
			if (pBarrier->IsBarrierOn() && i->get()->GetBulletType() != 1)
			{
				if (i->get()->GetBoundingBox()->Collision(pBarrierBoundingBox))
				{
					XMFLOAT2 vectorToEnemyBullet = i->get()->GetBoundingBox()->GetPos();
					vectorToEnemyBullet.x -= m_pos.x;
					vectorToEnemyBullet.y -= m_pos.y;

					float d = FindDistanceByCoordinateDifference(vectorToEnemyBullet);
					vectorToEnemyBullet.x /= d;
					vectorToEnemyBullet.y /= d;

					// 内積
					if (barrierVector.x * vectorToEnemyBullet.x + barrierVector.y * vectorToEnemyBullet.y > cosAngle)
					{
						i->get()->Hit();
					}
					else
					{
						if (i->get()->GetBoundingBox()->Collision(m_pCircleBoundingBox.get()))
						{
							GetDamaged(DAMAGE_WHEN_ENEMY_BULLET_HIT_SUBMARINE);
							i->get()->Hit();
						}
					}
				}
			}
			else if (i->get()->GetBoundingBox()->Collision(m_pCircleBoundingBox.get()))
			{
				GetDamaged(DAMAGE_WHEN_ENEMY_BULLET_HIT_SUBMARINE);
				i->get()->Hit();
			}
			++i;
		}
	}

	// NULLチェック
	if (_pSceneryObject)
	{
		for (int i = 0; i < (int)_pSceneryObject->size(); ++i)
		{
			// 障害物のバウンディングボックスを取得しておく
			BoundingBox* boundingBox = (*_pSceneryObject)[i]->GetBoundingBox();

			if (_pEnemyBullet)
			{
				// 敵の弾と障害物の当たり判定
				for (auto j = _pEnemyBullet->begin(); j != _pEnemyBullet->end();)
				{
					if (j->get()->GetBoundingBox()->Collision(boundingBox))
					{
						j->get()->Hit();
					}
					++j;
				}
			}
			
			for(int j = 0;j < 4;++j)
			{
				for (auto k = m_pBullet[j]->begin(); k != m_pBullet[j]->end();)
				{
					if (k->get()->GetBoundingBox()->Collision(boundingBox))
					{
						if (k == m_pBullet[j]->begin())
						{
							m_pBullet[j]->erase(k);
							k = m_pBullet[j]->begin();
						}
						else
						{
							--k;
							m_pBullet[j]->erase(k + 1);
							++k;
						}
						continue;
					}
					++k;
				}
			}
			if (m_pCircleBoundingBox->Collision(boundingBox))
			{
				if (m_pJetEngine->GetIsMoving())
				{
					XMFLOAT2 targetPos = boundingBox->GetPos();
					if ((moveDirection.x > 0.f && targetPos.x > m_pos.x) ||
						(moveDirection.x < 0.f && targetPos.x < m_pos.x) ||
						(moveDirection.y > 0.f && targetPos.y > m_pos.y) ||
						(moveDirection.y < 0.f && targetPos.y < m_pos.y))
					{
						m_pJetEngine->SetIsMoveingToFalse();
					}
				}
			}
		}	
	}

	// NULLチェック
	if (_pBoss)
	{
		vector<BoundingBox*> bossBoundingBox = *_pBoss->GetBoundingBox();
		// 弾との当たり判定
		for (int i = 0; i < 4; ++i)
		{
			for (auto iterator = m_pBullet[i]->begin(); iterator != m_pBullet[i]->end();)
			{
				try
				{
					for (int j = 0; j < (int)bossBoundingBox.size(); ++j)
					{
						if (bossBoundingBox[j]->Collision((*iterator)->GetBoundingBox()))
						{
							_pBoss->GetDamege(DAMAGE_OF_SUBMARINE_BULLET);
							throw 1;
						}
					}
				}
				catch (int)
				{
					if (iterator == m_pBullet[i]->begin())
					{
						m_pBullet[i]->erase(iterator);
						iterator = m_pBullet[i]->begin();
					}
					else
					{
						--iterator;
						m_pBullet[i]->erase(iterator + 1);
						++iterator;
					}
					continue;
				}
				++iterator;
			}
		}

		for (int i = 0; i < (int)bossBoundingBox.size(); ++i)
		{
			if (bossBoundingBox[i]->Collision(m_pCircleBoundingBox.get()))
			{
   				GetDamaged(DAMAGE_WHEN_SUBMARINE_HIT_BOSS);
				break;
			}
		}
	}

	// NULLチェック
	if (_pBossBullet)
	{
		// 敵の弾と潜水艦の当たり判定
		for (auto i = _pBossBullet->begin(); i != _pBossBullet->end();)
		{
			if (!i->get()->ImgActive())
			{
				++i;
				continue;
			}
			if (!(*i)->GetActive()) { ++i; continue; }
			if (m_pCircleBoundingBox.get()->Collision((*i)->GetBoundingBox()))
			{
				try
				{
					switch ((*i)->GetBulletType())
					{
					case TypeOfEnemyBullet::fire:	GetDamaged(DAMAGE_WHEN_SUBMARINE_HIT_BOSS_FIRE);	break;
					case TypeOfEnemyBullet::laser:	GetDamaged(DAMAGE_WHEN_SUBMARINE_HIT_BOSS_LASER);	break;
					default: throw 1; break;
					}
				}
				catch (int)
				{
					GetDamaged(DAMAGE_WHEN_ENEMY_BULLET_HIT_SUBMARINE);
					throw (string)"delete";
				}
				catch(string _msg)
				{
					if (_msg == "delete")
					{
						i->get()->Hit();
					}
					else
					{
						throw _msg;
					}
				}
			}
			++i;
		}
	}

	// NULLチェック
	if (_pGoal)
	{
		if (killedEnemyCnt >= GOAL_ON_THRESHOLD)
		{
			if (m_pCircleBoundingBox->Collision(_pGoal->GetBoundingBox()))
			{
				throw (string)"Goal";
			}
		}
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
	float movePower = m_pJetEngine->GetMovePower();

	// 潜水艦の新しい座標を計算
	XMFLOAT2 offsetPos = AngleToDirectionVector(moveDirection);
	m_pos.x += offsetPos.x * SUBMARINE_MOVE_SPEED / 30.f/* * _deltaTime*/ * movePower;
	m_pos.y += offsetPos.y * SUBMARINE_MOVE_SPEED / 30.f/* * _deltaTime*/ * movePower;

	//潜水艦の移動制御
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();
	XMFLOAT2 d = { (WINDOW_WIDTH - SUBMARINE_SIZE_X) / 2.f, (WINDOW_HEIGHT - SUBMARINE_SIZE_Y) / 2.f};
	if (m_pos.x > cameraPos.x + d.x)		m_pos.x = cameraPos.x + d.x;
	else if (m_pos.x < cameraPos.x - d.x)	m_pos.x = cameraPos.x - d.x;
	if (m_pos.y > cameraPos.y + d.y)		m_pos.y = cameraPos.y + d.y;
	else if (m_pos.y < cameraPos.y - d.y)	m_pos.y = cameraPos.y - d.y;

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

	// ハシゴの位置を設置する
	for (int i = 0; i < (int)m_ladder.size(); ++i)
	{
		m_ladder[i].ob->setPos(m_pos.x + m_ladder[i].relativePos.x, m_pos.y + m_ladder[i].relativePos.y);
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
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();

#if ShowDeltaTimeAndFPS
	if (pDeltaTimeText)pDeltaTimeText->setPos(cameraPos.x + DeltaTimeText_Pos_X, cameraPos.y + DeltaTimeText_Pos_Y);
#endif

	// カメラと潜水艦の間の距離を計算
	XMFLOAT2 distanceBetweenCameraAndSubmarine =
	{ m_pos.x - cameraPos.x, m_pos.y - cameraPos.y };

	cameraPos.x += distanceBetweenCameraAndSubmarine.x * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;
	cameraPos.y += distanceBetweenCameraAndSubmarine.y * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;

	CameraManager::SetCameraPos(cameraPos);
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
	if (m_invincibleCnt > 0)return;
	m_hp -= _damage;

#if GameOverActive
	if (m_hp < 0.f)throw (string)"GameOver";
#endif

	m_pUI->SetHP(m_hp);

	if (InvincibleTimeActive)
	{
		m_invincibleCnt = INVINCIBLE_TIME;
		m_bInvincible = true;
	}
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