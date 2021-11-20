/**
 * @file ShootingGame.cpp
 * @brief �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */

#include "stdafx.h"
#include "ActionGame.h"

 //! �O���[�o���ϐ�:
std::unique_ptr<CActionGameApp> g_pApp = NULL;

/**
 * �֐��v���g�^�C�v�̐錾
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * @fn INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
 * @brief �A�v���P�[�V�����̃G���g���[�֐�
 * @param hInstance_		WindowsAPI�̃C���X�^���X
 * @param 				WindowsAPI�̃C���X�^���X
 * @param 				WindowsAPI�̃C���X�^���X
 * @param 				WindowsAPI�̃C���X�^���X
 * @return				WindowsAPI ���s����
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	/**
	 * XNA Math���C�u�����̃T�|�[�g �`�F�b�N
	 */
	if (XMVerifyCPUSupport() != TRUE)
	{
		MessageBox(0, L"XNA Math���C�u�������T�|�[�g����Ă��Ȃ��B", NULL, MB_OK);
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
		 * �A�v���I��
		 */
		//g_pApp->release();
	}
	return 0;
}

/**
 * @fn LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg_, WPARAM wParam_, LPARAM lParam_)
 * @brief OS���猩���E�B���h�E�v���V�[�W���[�i���ۂ̏�����MAIN�N���X�̃v���V�[�W���[�ŏ����j
 * @param hWnd_		�E�C���h�E�n���h��
 * @param iMsg_		WindowsAPI
 * @param wParam_	WindowsAPI
 * @param lParam_	WindowsAPI
 * @return			WindowsAPI
 */
LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg_, WPARAM wParam_, LPARAM lParam_)
{
	return g_pApp->msgProc(hWnd_, uMsg_, wParam_, lParam_);
}
