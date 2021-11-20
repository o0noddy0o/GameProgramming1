//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Component.h
// 概要　　　　　：潜水艦の部品
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/17 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "CObjectBase.h"

class Component : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Component(GameInfo* _pGameInfo, XMFLOAT2 _relativePos = {0.f, 0.f});
	virtual ~Component();

	CPicture* GetImg();						// 画像を取得する
	virtual void renderSprite();			// 画像を描画する
	virtual void InputProcess() = 0;		// プレイヤーの入力処理
	virtual void SetPos(XMFLOAT2 _pos);		// 画像の位置を設置する

protected:
	CPicture* m_pImg;						// 部品の画像
	XMFLOAT2 m_relativePos;					// 部品の座標と潜水艦の座標の差
};