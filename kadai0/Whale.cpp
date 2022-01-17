//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Whale.cpp
// 概要　　　　　：クジラ（ステージ１のボス）のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/17 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Whale.h"
#include "MissileLauncher.h"

Whale::Whale(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
{
	//m_pMissileLauncher[0] = new MissileLauncher(m_pGameInfo, )
}

Whale::~Whale()
{
}

// 行動パターンを決める
void Whale::DecideActionPattern(XMFLOAT2 _SubmarinePos)
{

}

// 毎フレームの処理
void Whale::Tick(XMFLOAT2 _SubmarinePos)
{

}

// 画像の描画
void Whale::renderSprite()
{

}