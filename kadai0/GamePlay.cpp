#include "Define.h"
#include "Stage.h"
#include "CActionGameApp.h"
#include "CText.h"
#include <string>
#include "GameResource.h"

// ゲームフロー用変数
ePhase GamePhase = (ePhase)eBegin;
eGameStatus goNextStatusFromPlaying = (eGameStatus)eNone;

shared_ptr<Stage> pStage = nullptr;

#if ShowGamePadInput
shared_ptr<CText> pText2 = nullptr;
#endif
#if ShowMousePos
shared_ptr<CText> mousePos = nullptr;
#endif

// カメラの初期座標を保存用変数
XMFLOAT3 cameraPos;

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が始まる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayBegin()
{
	renderSprite(pBackground);
	pText->setPos(-96.f, 200.f);
	pText->SetText("STAGE-1");

#if ShowGamePadInput
	pText->setPos(-900.f, 350.f);
	pText2 = shared_ptr<CText>(new CText(getGameInfo(), Tex_Text, kTexelText, XMFLOAT2(28.f, 28.f), XMFLOAT2(-900, 0.f), XMFLOAT2(5.f, 14.f)));
#endif
#if ShowMousePos
	mousePos = shared_ptr<CText>(new CText(getGameInfo(), Tex_Text, kTexelText, XMFLOAT2(28.f, 28.f), XMFLOAT2(500, 350.f), XMFLOAT2(5.f, 14.f)));
#endif

	pStage = shared_ptr<Stage>(new Stage(getGameInfo()));

	cameraPos = m_pCamera->getPos();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面のメイン処理
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayMain()
{
	renderSprite(pBackground);

#if ShowGamePadInput || ShowMousePos
	XMFLOAT3 camPos = m_pCamera->getPos();
#endif


//━━━━━━━━━━━━━━━━━━━━━━━
// 　　　↓↓↓　　メイン処理　　↓↓↓
//━━━━━━━━━━━━━━━━━━━━━━━
	{
		try
		{
			pStage->Tick();
		}
		catch (string _msg)
		{
			if (_msg == "GameClear")
			{
				GamePhase = eEnd;
				goNextStatusFromPlaying = eGameClear;
			}
			else if (_msg == "GameOver")
			{
				GamePhase = eEnd;
				goNextStatusFromPlaying = eGameOver;
			}
			else if (_msg == "Goal")
			{
				try
				{
					pStage->SetNextStage();
				}
				catch(string _msg)
				{
					if (_msg == "EndOfAllStage")
					{
						GamePhase = eEnd;
						goNextStatusFromPlaying = eGameClear;
					}
				}
			}
		}
		pStage->RenderProcess();
	}
//━━━━━━━━━━━━━━━━━━━━━━━
// 　　　↑↑↑　　メイン処理　　↑↑↑
//━━━━━━━━━━━━━━━━━━━━━━━

//━━━━━━━━━━━━━━━━━━━━━━━
// 　　　↓↓↓　　デバッグ用　　↓↓↓
//━━━━━━━━━━━━━━━━━━━━━━━
#if DEBUG
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

	static bool showText = false;
	if (getInput()->isPressedOnce(DIK_SEMICOLON))showText = !showText;
	if (showText)
	{
#if ShowGamePadInput
		{
			pText->setPos(camPos.x - 900.f, camPos.y + 350.f);
			pText2->setPos(camPos.x - 900, camPos.y);

			float x = getInput()->GetAnalogStickX(0);
			float y = getInput()->GetAnalogStickY(0);

			string text = "GAMEPAD 1\nX ";
			if (x < 0.f)text += "-";
			text += to_string(Abs(x)) + "\nY ";
			if (y < 0.f)text += "-";
			text += to_string(Abs(y));
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_A, 0))text += "\n\"A\"IS PRESSED!";
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_B, 0))text += "\n\"B\"IS PRESSED!";
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_X, 0))text += "\n\"X\"IS PRESSED!";
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_Y, 0))text += "\n\"Y\"IS PRESSED!";

			pText->SetText(text);


			x = getInput()->GetAnalogStickX(1);
			y = getInput()->GetAnalogStickY(1);

			text = "GAMEPAD 2\nX ";
			if (x < 0.f)text += "-";
			text += to_string(Abs(x)) + "\nY ";
			if (y < 0.f)text += "-";
			text += to_string(Abs(y));
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_A, 1))text += "\n\"A\"IS PRESSED!";
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_B, 1))text += "\n\"B\"IS PRESSED!";
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_X, 1))text += "\n\"X\"IS PRESSED!";
			if (getInput()->IsGamePadButtonPressed(GAMEPAD_Y, 1))text += "\n\"Y\"IS PRESSED!";

			pText2->SetText(text);

			pText->RenderText(0, COLOR_YELLOW);
			pText2->RenderText(0, COLOR_YELLOW);
	}
#endif
#if ShowMousePos
		{
			mousePos->setPos(camPos.x + 500.f, camPos.y + 350.f);
			string text = "CAMERA POS\nX ";
			if (camPos.x < 0.f)text += "-";
			text += to_string(Abs(camPos.x)) + "\nY ";
			if (camPos.y < 0.f)text += "-";
			text += to_string(Abs(camPos.y)) + "\n\nMOUSE POS\nX ";
			XMFLOAT2 MousePos = getInput()->getMousePos();
			if (!SchoolPC)
			{
				static XMFLOAT2 dpi = DPI;
				MousePos.x = (MousePos.x + 960.f) / dpi.x * 1920.f - 960.f;
				MousePos.y = (MousePos.y - 540.f) / dpi.y * 1080.f + 540.f;
			}
			if (MousePos.x < 0.f)text += "-";
			text += to_string(Abs(MousePos.x)) + "\nY ";
			if (MousePos.y < 0.f)text += "-";
			text += to_string(Abs(MousePos.y)) + "\n\nX ";
			MousePos.x += camPos.x;
			MousePos.y += camPos.y;
			if (MousePos.x < 0.f)text += "-";
			text += to_string(Abs(MousePos.x)) + "\nY ";
			if (MousePos.y < 0.f)text += "-";
			text += to_string(Abs(MousePos.y));

			mousePos->SetText(text);
			mousePos->RenderText(0, COLOR_YELLOW);
		}
#endif
	}
#endif
//━━━━━━━━━━━━━━━━━━━━━━━
// 　　　↑↑↑　　デバッグ用　　↑↑↑
//━━━━━━━━━━━━━━━━━━━━━━━
}

//━━━━━━━━━━━━━━━━━━━━━━━
// インゲーム画面が終わる時に呼び出すメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CActionGameApp::procPlayEnd()
{
	renderSprite(pBackground);

	// カメラの座標をリセットする
	m_pCamera->setPos(cameraPos);
	
	pStage = nullptr;
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