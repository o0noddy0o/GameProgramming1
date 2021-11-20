/**
 * @file ShootingGame.cpp
 * @brief アプリケーションのエントリ ポイントを定義します。
 * @author 織戸　喜隆
 * @date 日付（2017.02.14）
 */

#include "stdafx.h"
#include "ActionGame.h"

 //! グローバル変数:
std::unique_ptr<CActionGameApp> g_pApp = NULL;

/**
 * 関数プロトタイプの宣言
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * @fn INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
 * @brief アプリケーションのエントリー関数
 * @param hInstance_		WindowsAPIのインスタンス
 * @param 				WindowsAPIのインスタンス
 * @param 				WindowsAPIのインスタンス
 * @param 				WindowsAPIのインスタンス
 * @return				WindowsAPI 実行結果
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	/**
	 * XNA Mathライブラリのサポート チェック
	 */
	if (XMVerifyCPUSupport() != TRUE)
	{
		MessageBox(0, L"XNA Mathライブラリがサポートされていない。", NULL, MB_OK);
		return 0;
	}

	srand((unsigned int)time(NULL));

	g_pApp = unique_ptr<CActionGameApp>(new CActionGameApp());
	if (g_pApp != NULL)
	{
		if (SUCCEEDED(g_pApp->initWindow(hInstance, WndProc, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME)))
		{
			if (SUCCEEDED(g_pApp->initD3D()))
			{
				g_pApp->loop();
			}
		}
		/**
		 * アプリ終了
		 */
		//g_pApp->release();
	}
	return 0;
}

/**
 * @fn LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg_, WPARAM wParam_, LPARAM lParam_)
 * @brief OSから見たウィンドウプロシージャー（実際の処理はMAINクラスのプロシージャーで処理）
 * @param hWnd_		ウインドウハンドル
 * @param iMsg_		WindowsAPI
 * @param wParam_	WindowsAPI
 * @param lParam_	WindowsAPI
 * @return			WindowsAPI
 */
LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg_, WPARAM wParam_, LPARAM lParam_)
{
	return g_pApp->msgProc(hWnd_, uMsg_, wParam_, lParam_);
}
