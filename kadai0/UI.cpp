//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：UI.cpp
// 概要　　　　　：UIのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/12/10 作成（ゴ）		   
//━━━━━━━━━━━━━━━━━━━━━━━
#include "UI.h"
#include "Define.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
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

	m_pHpBar = CreateSprite(Tex_HPBar, HP_BAR_SZIE_X, HP_BAR_SZIE_Y);
	m_pFreamOfHpBar = CreateSprite(Tex_HPBarFream, HP_BAR_SZIE_X, HP_BAR_SZIE_Y);
	m_pNumOfEnemy = new CText(m_pGameInfo, Tex_Text, kTexelText, XMFLOAT2(28.f, 28.f), ENEMY_NUM_POS, XMFLOAT2(5.f, 5.f));

}

//━━━━━━━━━━━━━━━━━━━━━━━
//━━━━━━━━━━━━━━━━━━━━━━━
UI::~UI()
{
	DisposeSprite(m_pHpBar);
	DisposeSprite(m_pFreamOfHpBar);
	delete m_pNumOfEnemy;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦のHPをセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::SetHP(float _newHp)
{
	if (_newHp >= 0)
	{
		m_pHpBar->setScale(1.f, _newHp / SUBMARINE_MAX_HP);
		m_hpBarRelativePos = { HP_BAR_RELATIVE_POS_X, HP_BAR_RELATIVE_POS_Y };
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 倒した敵の数(α版まで使うやつ)
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::SetNumOfKilledEnemy(int _numOfKilledEnemy)
{
	m_text = "";
	m_text += _numOfKilledEnemy;
	m_text += "-";
	m_text += MAX_ENEMY_NUM;

	m_pNumOfEnemy->SetText(m_text);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画する
//━━━━━━━━━━━━━━━━━━━━━━━
void UI::renderSprite()
{
	RenderSprite(m_pHpBar);
	RenderSprite(m_pFreamOfHpBar);
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