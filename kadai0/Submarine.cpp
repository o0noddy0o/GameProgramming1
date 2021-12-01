//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Submarine.cpp
// 概要　　　　　：潜水艦のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成（ゴ）
//				   2021/11/28 移動メソッドを修正（ズン）
//							  プレイヤー数を分ける（ズン）		   
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Submarine.h"
#include "GameResource.h"
#include "Turret.h"
#include "JetEngine.h"
#include "Player.h"
#include "Bullet.h"
#include "Barrier.h"
<<<<<<< HEAD
#include "OperationDevice.h"
=======
>>>>>>> e1c34234400996c219dc3fad9478311ade5f9f8b

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Submarine::Submarine(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_Submarine, 512.f, 512.f);
	m_pImg->setPos(m_pos);

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

	// 操作装置オブジェクトの作成
	for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{
		m_pOperationDevice[i] = shared_ptr<OperationDevice>(new OperationDevice(m_pGameInfo, { 0.f, 0.f}, m_pos, i));
		//m_pOperationDevice[i]->SetComponent(m_pComponent[i]);
	}
	
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Submarine::~Submarine()
{
	DisposeSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 毎フレームにやる処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::Tick(float _deltaTime)
{
	// テスト用
	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		m_pComponent[i]->InputProcess();
	}

	MoveProcess(_deltaTime);

	MoveCamera();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < (int)m_pBullet[i]->size(); ++j)
		{
			(*m_pBullet[i])[j]->MoveProcess(_deltaTime);
		}
	}

	m_pPlayer[0]->Tick(_deltaTime);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画する
//━━━━━━━━━━━━━━━━━━━━━━━
void Submarine::RenderProcess()
{
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
	
	//プレイヤーの画像を描画
	m_pPlayer[0]->RenderChara();
	m_pPlayer[1]->RenderChara();

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
	
	static JetEngine* pJetEngine = (JetEngine*)m_pComponent[4].get();

	// 移動中かをチェックする
	if (!pJetEngine->GetIsMoving())
	{
		//プレイヤーを一緒に移動させる
		m_pPlayer[0]->SetPos(m_pos);

		//操作装置を移動させる
		for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
		{
			m_pOperationDevice[i]->SetPos(m_pos);
		}
		
		return;
	}

	float moveDirection = pJetEngine->GetMoveDirection();

	// 潜水艦の新しい座標を計算
	XMFLOAT2 offsetPos = AngleToDirectionVector(moveDirection);
	m_pos.x += offsetPos.x * SUBMARINE_MOVE_SPEED;
	m_pos.y += offsetPos.y * SUBMARINE_MOVE_SPEED;

	// 潜水艦の位置を設置する
	m_pImg->setPos(m_pos);

	// すべて部品を移動させる
	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		m_pComponent[i]->SetPos(m_pos);
	}

	//プレイヤーを一緒に移動させる
	m_pPlayer[0]->SetPos(m_pos);

	//操作装置を移動させる
	for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{
		m_pOperationDevice[i]->SetPos(m_pos);
	}

	pJetEngine->SetIsMoveingToFalse();
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
	// カメラの座標を取得する
	XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

	// カメラと潜水艦の間の距離を計算
	XMFLOAT2 distanceBetweenCameraAndSubmarine = 
	{ m_pos.x - cameraPos.x, m_pos.y - cameraPos.y };

	cameraPos.x += distanceBetweenCameraAndSubmarine.x * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;
	cameraPos.y += distanceBetweenCameraAndSubmarine.y * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;

	m_pGameInfo->pCamera->get()->setPos(cameraPos);
}
