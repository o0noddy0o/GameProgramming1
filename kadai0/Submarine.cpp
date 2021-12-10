//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Submarine.cpp
// 概要　　　　　：潜水艦のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成（ゴ）
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

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Submarine::Submarine(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
	, m_pos(0.f, 0.f)
	, m_hp(SUBMARINE_MAX_HP)
	, m_pBullet{nullptr}
{
	m_pGameInfo->pCamera->get()->setPos(m_pos.x, m_pos.y, m_pGameInfo->pCamera->get()->getPos().z);

	m_pImg = CreateSprite(Tex_Submarine, 512.f, 512.f);
	m_pImg->setPos(m_pos);

	m_pFloor = CreateSprite(Tex_Yuka, 400.f, 10.f);
	m_pFloor->setPos(m_pos.x, m_pos.y - YUKA_POSITION);

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
		{ 202.f, -2.f },
		{ 0.f, -206.f },
		{ -196.f, -4.f },
		{ 15.f, 190.f },
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
	m_pUI->SetNumOfKilledEnemy(10);

	m_pJetEngine = (JetEngine*)m_pComponent[4].get();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Submarine::~Submarine()
{
	DisposeSprite(m_pImg);
	DisposeSprite(m_pFloor);
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
#endif

	MoveProcess(_deltaTime);

	MoveCamera();

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
			m_pOperationDevice[i]->collisionWithPlayer(m_pPlayer[j].get());
		}
	}

	m_pPlayer[0]->Tick(_deltaTime);
	m_pPlayer[1]->Tick(_deltaTime);

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
	RenderSprite(m_pFloor);
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
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::CollisionProcess(
	vector < shared_ptr < Enemy> >* _pEnemy,
	vector < shared_ptr < SceneryObject > >* _pSceneryObject,
	vector < shared_ptr < Bullet > >** _pBullet,
	vector < shared_ptr < Item > >* _pItem)
{
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

		//操作装置を移動させる
		for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
		{
			m_pOperationDevice[i]->SetPos(m_pos);
		}
		
		return;
	}

	float moveDirection = m_pJetEngine->GetMoveDirection();

	// 潜水艦の新しい座標を計算
	XMFLOAT2 offsetPos = AngleToDirectionVector(moveDirection);
	m_pos.x += offsetPos.x * SUBMARINE_MOVE_SPEED;
	m_pos.y += offsetPos.y * SUBMARINE_MOVE_SPEED;

	// 潜水艦の位置を設置する
	m_pImg->setPos(m_pos);
	m_pFloor->setPos(m_pos.x, m_pos.y - YUKA_POSITION);

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
void Submarine::MoveCamera()
{
	m_pUI->SetPos();
	// カメラの座標を取得する
	XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

	// カメラと潜水艦の間の距離を計算
	XMFLOAT2 distanceBetweenCameraAndSubmarine = 
	{ m_pos.x - cameraPos.x, m_pos.y - cameraPos.y };

	cameraPos.x += distanceBetweenCameraAndSubmarine.x * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;
	cameraPos.y += distanceBetweenCameraAndSubmarine.y * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;

	m_pGameInfo->pCamera->get()->setPos(cameraPos);

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