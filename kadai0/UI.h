//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：UI.h
// 概要　　　　　：UIのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/12/10 作成（ゴ）		   
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "CObjectBase.h"
#include "CText.h"

class Map;

class UI : public CObjectBase
{
	typedef CObjectBase Super;
public:
	UI(GameInfo* _pGameInfo);
	~UI();

	void SetHP(float _newHp);
	void SetNumOfKilledEnemy(int _numOfKilledEnemy); // 一時的に使うやつ

	// 画像を描画する
	void renderSprite();

	// UIの位置を設置する
	void SetPos();

	// 地図を更新する(MapのUpdateMap()を呼び出す
	void UpdateMap(XMFLOAT2 _submarinePos);

private:
	CPicture* m_pHpBar;
	CPicture* m_pFreamOfHpBar;
	Map*      m_pMap;
	CText*	  m_pNumOfEnemy;
	XMFLOAT2  m_hpBarRelativePos;
	string m_text;
};