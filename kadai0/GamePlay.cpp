#include "Define.h"
#include "CActionGameApp.h"
#include "kadai0/GameResource.h"
#include "CText.h"
#include "Submarine.h"
#include "Fish.h"
#include "CircleBoundingBox.h"
#include "RectangleBoundingBox.h"
#include "Bullet.h"

// ゲームフロー用変数
ePhase GamePhase = (ePhase)eBegin;
eGameStatus goNextStatusFromPlaying = (eGameStatus)eNone;

shared_ptr<Submarine> pSubmarine = nullptr;

// カメラの初期座標を保存用変数
XMFLOAT3 cameraPos;

//
Fish* enemy[10] = {NULL};

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が始まる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayBegin()
{
	renderSprite(pBackground);
	pText->setPos(-96.f, 200.f);
	pText->SetText("INGAME");

	if (!pSubmarine)pSubmarine = shared_ptr<Submarine>(new Submarine(getGameInfo()));

	enemy[0] = new Fish(getGameInfo(), XMFLOAT2( 600.f,850.f ));
	enemy[1] = new Fish(getGameInfo(), XMFLOAT2( 810.f,10.f ));
	enemy[2] = new Fish(getGameInfo(), XMFLOAT2( -800.f,200.f ));
	enemy[3] = new Fish(getGameInfo(), XMFLOAT2( 720.f,-900.f ));
	enemy[4] = new Fish(getGameInfo(), XMFLOAT2( -720.f,90.f ));
	enemy[5] = new Fish(getGameInfo(), XMFLOAT2( 580.f,450.f ));
	enemy[6] = new Fish(getGameInfo(), XMFLOAT2( 360.f,180.f ));
	enemy[7] = new Fish(getGameInfo(), XMFLOAT2( 410.f,680.f ));
	enemy[8] = new Fish(getGameInfo(), XMFLOAT2( -860.f,210.f ));
	enemy[9] = new Fish(getGameInfo(), XMFLOAT2( 380.f,70.f ));

	cameraPos = m_pCamera->getPos();
}

//PhanXuanDung

//ズン

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面のメイン処理
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayMain()
{
	renderSprite(pBackground);
	pText->RenderText();

	pSubmarine->RenderProcess();
	pSubmarine->Tick(1.f);

	// Xキーを押したら、インゲーム画面からゲームクリア画面へ移す
	if (getInput()->isPressedOnce(DIK_X))
	{
		GamePhase = eEnd;
		goNextStatusFromPlaying = eGameClear;
	}
	else if (getInput()->isPressedOnce(DIK_Z))
	{
		GamePhase = eEnd;
		goNextStatusFromPlaying = eGameOver;
	}
	for (int i = 0; i < 10; ++i)
	{
		if(enemy[i])enemy[i]->renderSprite();
	}
	
}

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が終わる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayEnd()
{
	renderSprite(pBackground);

	// カメラの座標をリセットする
	m_pCamera->setPos(cameraPos);

	for (int i = 0; i < 10; ++i)
	{
		delete enemy[i];
	}
	
}

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面のフロー
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procGame()
{
	switch (GamePhase)
	{
	case eBegin:

		// インゲーム画面が始まる時の処理
		procPlayBegin();

		// 次のフェーズに設定する
		GamePhase = eMain;

		break;

	case eMain:

		// インゲーム画面のメイン処理
		procPlayMain();

		break;

	case eEnd:

		// インゲーム画面が終わる時の処理
		procPlayEnd();

		// フェーズをリセットする
		GamePhase = eBegin;

		// 次のゲームステータスを設定する
		SetNextGameStatus(goNextStatusFromPlaying);

		break;
	}
}