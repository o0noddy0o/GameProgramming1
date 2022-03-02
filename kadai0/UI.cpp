//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：UI.cpp
// 概要　　　　　：UIのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/12/10 作成（ゴ）		   
//━━━━━━━━━━━━━━━━━━━━━━━
#include "UI.h"
#include "Define.h"
#include "GameResource.h"
#include <string>

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
UI::UI(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
	, m_pHpBar(NULL)
	, m_pFreamOfHpBar(NULL)
	, m_pNumOfEnemy(NULL)
	, m_pMap(NULL)
	, m_hpBarRelativePos(HP_BAR_RELATIVE_POS)
{
	XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

	//掲示板
	for (int i = 0; i < NUM_OF_BOARD; ++i)
	{
		pBoard[i] = NULL;
	}
	/*pBoard[0] = CreateSprite(Tex_Board, 300.f, 300.f);
	pBoard[0]->setPos(600.f, 300.f);
	pBoard[1] = CreateSprite(Tex_Board, 300.f, 300.f);
	pBoard[1]->setPos(1300.f, 180.f);*/
	/*pBoard[2] = CreateSprite(Tex_Board, 300.f, 300.f);
	pBoard[2]->setPos(3700.f, -500.f);
	pBoard[3] = CreateSprite(Tex_Board, 300.f, 300.f);
	pBoard[3]->setPos(1600.f, -1800.f);*/

	//掲示板の文章
	for (int i = 0; i < NUM_OF_TEXT; ++i)
	{
		pText[i] = NULL;
	}
	/*pText[0] = CreateSprite(Tex_Text_1, 300.f, 300.f);
	pText[0]->setPos(600.f, 300.f);
	pText[1] = CreateSprite(Tex_Text_2, 300.f, 300.f);
	pText[1]->setPos(1300.f, 180.f);*/
	/*pText[2] = CreateSprite(Tex_Text_3, 300.f, 300.f);
	pText[2]->setPos(3700.f, -500.f);
	pText[3] = CreateSprite(Tex_Text_4, 300.f, 300.f);
	pText[3]->setPos(1600.f, -1800.f);*/

	m_pHpBar = CreateSprite(Tex_HPBar, HP_BAR_SIZE_X, HP_BAR_SIZE_Y);
	m_pFreamOfHpBar = CreateSprite(Tex_HPBarFream, HP_BAR_FREAM_SIZE_X, HP_BAR_FREAM_SIZE_Y);
	m_pNumOfEnemy = new CText(m_pGameInfo, Tex_Text, kTexelText, XMFLOAT2(28.f, 28.f), ENEMY_NUM_POS, XMFLOAT2(5.f, 5.f));

	m_pHpBar->setPos(cameraPos.x + m_hpBarRelativePos.x, cameraPos.y + m_hpBarRelativePos.y);
	m_pFreamOfHpBar->setPos(cameraPos.x + HP_BAR_RELATIVE_POS_X, cameraPos.y + HP_BAR_RELATIVE_POS_Y);
	m_pNumOfEnemy->setPos(cameraPos.x + ENEMY_NUM_POS_X, cameraPos.y + ENEMY_NUM_POS_Y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
UI::~UI()
{
	DisposeSprite(m_pHpBar);
	DisposeSprite(m_pFreamOfHpBar);

	for (int i = 0; i < NUM_OF_BOARD; ++i)
	{
		DisposeSprite(pBoard[i]);
	}

	for (int i = 0; i < NUM_OF_TEXT; ++i)
	{
		DisposeSprite(pText[i]);
	}

	delete m_pNumOfEnemy;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦のHPをセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::SetHP(float _newHp)
{
	if (_newHp >= 0)
	{
		m_pHpBar->setScale(_newHp / SUBMARINE_MAX_HP, 1.f);
		m_hpBarRelativePos = { HP_BAR_RELATIVE_POS_X - (1.f - _newHp / SUBMARINE_MAX_HP) * HP_BAR_SIZE_X / 2.f, HP_BAR_RELATIVE_POS_Y };
	}
	else
	{
		m_pHpBar->setScale(0.f, 1.f);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 倒した敵の数(α版まで使うやつ)
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::SetNumOfKilledEnemy(int _numOfKilledEnemy)
{
	if (_numOfKilledEnemy > GOAL_ON_THRESHOLD)
	{
		m_text = "";
	}
	else if (_numOfKilledEnemy < 10)
	{
		m_text = " " + std::to_string(_numOfKilledEnemy) + "-" + std::to_string(GOAL_ON_THRESHOLD);
	}
	else
	{
		m_text = std::to_string(_numOfKilledEnemy) + "-" + std::to_string(GOAL_ON_THRESHOLD);
	}

	m_pNumOfEnemy->SetText(m_text);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画する
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::renderSprite()
{
	for (int i = 0; i < NUM_OF_BOARD; ++i)
	{
		RenderSprite(pBoard[i]);
	}

	for (int i = 0; i < NUM_OF_TEXT; ++i)
	{
		RenderSprite(pText[i]);
	}
	RenderSprite(m_pFreamOfHpBar);
	RenderSprite(m_pHpBar);

	

	m_pNumOfEnemy->SetText(m_text);
	m_pNumOfEnemy->RenderText();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// UIの位置を設置する
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::SetPos()
{
	XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

	m_pHpBar->setPos(cameraPos.x + m_hpBarRelativePos.x, cameraPos.y + m_hpBarRelativePos.y);
	m_pFreamOfHpBar->setPos(cameraPos.x + HP_BAR_RELATIVE_POS_X, cameraPos.y + HP_BAR_RELATIVE_POS_Y);
	m_pNumOfEnemy->setPos(cameraPos.x + ENEMY_NUM_POS_X, cameraPos.y + ENEMY_NUM_POS_Y);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 地図を更新する(MapのUpdateMap()を呼び出す
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::UpdateMap(XMFLOAT2 _submarinePos)
{
}