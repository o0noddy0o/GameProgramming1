#include "CText.h"
#include "CActionGameApp.h"
#include "kadai0/GameResource.h"
#include "Define.h"

// ゲームフロー用変数
ePhase GameClearPhase = eBegin;
eGameStatus goNextStatusFromGameClear = eNone;

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームクリアのフロー
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procClear()
{
	switch (GameClearPhase)
	{
	case eBegin:

		// ゲームクリア画面が始まる時の処理
		procClearBegin();

		// 次のフェーズに設定する
		GameClearPhase = eMain;

		break;

	case eMain:

		// ゲームクリア画面のメイン処理
		procClearMain();

		break;

	case eEnd:

		// ゲームクリア画面が終わる時の処理
		procClearEnd();

		// フェーズをリセットする
		GameClearPhase = eBegin;

		// 次のゲームステータスを設定する
		SetNextGameStatus(goNextStatusFromGameClear);

		break;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームクリア画面が始まる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procClearBegin()
{
	renderSprite(pBackground);
	pText->setPos(-162.5f, 200.f);
	pText->SetText("GAME CLEAR");
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームクリア画面のメイン処理
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procClearMain()
{
	renderSprite(pBackground);
	pText->RenderText();

	if (getInput()->isPressedOnce(DIK_X) ||
		getInput()->isPressedOnce(DIK_SPACE) ||
		getInput()->isPressedOnce(DIK_RETURN))
	{
		GameClearPhase = eEnd;
		goNextStatusFromGameClear = eGameOver;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームクリア画面が終わる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procClearEnd()
{
	renderSprite(pBackground);
}

// 0:26