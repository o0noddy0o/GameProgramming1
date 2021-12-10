#include "Define.h"
#include "Stage.h"
#include "CActionGameApp.h"
#include "CText.h"

// ゲームフロー用変数
ePhase GamePhase = (ePhase)eBegin;
eGameStatus goNextStatusFromPlaying = (eGameStatus)eNone;

shared_ptr<Stage> pStage = nullptr;

// カメラの初期座標を保存用変数
XMFLOAT3 cameraPos;

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が始まる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayBegin()
{
	renderSprite(pBackground);
	pText->setPos(-96.f, 200.f);
	pText->SetText("INGAME");

	pStage = shared_ptr<Stage>(new Stage(getGameInfo()));

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

	pStage->Tick();
	pStage->CollisionProcess();
	pStage->RenderProcess();

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
}

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が終わる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayEnd()
{
	renderSprite(pBackground);

	// カメラの座標をリセットする
	m_pCamera->setPos(cameraPos);
	
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