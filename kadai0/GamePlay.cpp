#include "Define.h"
#include "CActionGameApp.h"
#include "kadai0/GameResource.h"
#include "CText.h"
#include "Submarine.h"

// ゲームフロー用変数
ePhase GamePhase = (ePhase)eBegin;
eGameStatus goNextStatusFromPlaying = (eGameStatus)eNone;

shared_ptr<Submarine> pSubmarine = nullptr;

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が始まる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayBegin()
{
	renderSprite(pBackground);
	pText->setPos(-96.f, 200.f);
	pText->SetText("INGAME");

	if (!pSubmarine)pSubmarine = shared_ptr<Submarine>(new Submarine(getGameInfo()));
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
}

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が終わる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayEnd()
{
	renderSprite(pBackground);

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