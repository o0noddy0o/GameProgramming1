//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Stage.cpp
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/12/01 作成
//━━━━━━━━━━━━━━━━━━━━━━━

#include "Stage.h"
#include "GameResource.h"
#include "SceneryObject.h"
#include "Submarine.h"
#include "Map.h"
#include "Enemy.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
Stage::Stage(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
{
	//
	int map[Map_Y_SIZE][Map_X_SIZE] = Stage01;
	//m_map = map;

}

void Stage::RenderProcess()
{
	XMFLOAT3 cameraPoa = m_pGameInfo->pCamera->get()->getPos();





}