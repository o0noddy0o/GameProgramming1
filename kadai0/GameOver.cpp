#include "CActionGameApp.h"
#include "kadai0/GameResource.h"
#include "CText.h"

// ゲームフロー用変数
ePhase GameOverPhase = eBegin;
eGameStatus goNextStatusFromGameOver = eNone;

// 画像を管理する変数
CPicture* pGameOverBackground = nullptr;
CPicture* pGameOverImg = nullptr;


//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームオーバーのフロー
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procGameOver()
{
	switch (GameOverPhase)
	{
	case eBegin:

		// ゲームオーバー画面が始まる時の処理
		procOverBegin();

		// 次のフェーズに設定する
		GameOverPhase = eMain;

		break;

	case eMain:

		// ゲームオーバー画面のメイン処理
		procOverMain();

		break;

	case eEnd:

		// ゲームオーバー画面が終わる時の処理
		procOverEnd();

		// フェーズをリセットする
		GameOverPhase = eBegin;

		// 次のゲームステータスを設定する
		SetNextGameStatus(goNextStatusFromGameOver);

		break;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームオーバー画面が始まる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procOverBegin()
{
	renderSprite(pBackground);
	pText->setPos(-146.f, 200.f);
	pText->SetText("GAME OVER");
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームオーバー画面のメイン処理
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procOverMain()
{
	renderSprite(pBackground);
	pText->RenderText();

	// キーを押したら、ゲームオーバー画面から次の画面へ移す
	if (getInput()->isPressedOnce(DIK_X) ||
		getInput()->isPressedOnce(DIK_SPACE) ||
		getInput()->isPressedOnce(DIK_RETURN))
	{
		GameOverPhase = eEnd;
		goNextStatusFromGameOver = eTitle;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームオーバー画面が終わる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procOverEnd()
{
	renderSprite(pBackground);
}