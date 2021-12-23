#include "CActionGameApp.h"
#include "kadai0/GameResource.h"
#include "CText.h"
#include "Define.h"

// ゲームフロー用変数
ePhase TitlePhase = eBegin;
eGameStatus goNextStatusFromTitle = eNone;

//━━━━━━━━━━━━━━━━━━━━━━━
// タイトルのフロー
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procTitle()
{
	switch (TitlePhase)
	{
	case eBegin:

		// タイトル画面が始まる時の処理
		procTitleBegin();

		// 次のフェーズに設定する
		TitlePhase = eMain;

		break;

	case eMain:

		// タイトル画面のメイン処理
		procTitleMain();

		break;

	case eEnd:

		// タイトル画面が終わる時の処理
		procTitleEnd();
		
		// フェーズをリセットする
		TitlePhase = eBegin;

		// 次のゲームステータスを設定する
		SetNextGameStatus(goNextStatusFromTitle);

		break;
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// タイトル画面が始まる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procTitleBegin()
{
	if (!pBackground) pBackground = createSprite(Tex_Ingame, 1920.f * SCREEN_MULTIPLE_X, 1080.f * SCREEN_MULTIPLE_Y);
	pBackground->setPos(1920.f, -1620.f);
	renderSprite(pBackground);
	pText->setPos(-80.f, 200.f);
	pText->SetText("TITLE");
}

//━━━━━━━━━━━━━━━━━━━━━━━
// タイトル画面のメイン処理
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procTitleMain()
{
	renderSprite(pBackground);
	
	pText->RenderText(30, COLOR_YELLOW);

	// キーを押したら、タイトル画面から次の画面へ移す
	if (getInput()->isPressedOnce(DIK_X) ||
		getInput()->isPressedOnce(DIK_SPACE) ||
		getInput()->isPressedOnce(DIK_RETURN))
	{
		TitlePhase = eEnd;
		goNextStatusFromTitle = ePlaying;
	}

}

//━━━━━━━━━━━━━━━━━━━━━━━
// タイトル画面が終わる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procTitleEnd()
{
	renderSprite(pBackground);
}