//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Boss.cpp
// 概要　　　　　：ボスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/17 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Boss.h"

shared_ptr<vector<shared_ptr<EnemyBullet>>> Boss::m_pBullet;

Boss::Boss(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
{
}

Boss::~Boss()
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)
	{
		DisposeSprite(m_pImg[i]);
	}
	m_pImg.clear();
}

// 画像の描画
void Boss::renderSprite()
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)
	{
		RenderSprite(m_pImg[i]);
	}
}

// 弾の配列を取得する
shared_ptr<vector<shared_ptr<EnemyBullet>>>	Boss::GetEnemyBullet()
{
	return m_pBullet;
}

void Boss::ResetBossBullet()
{
	Boss::m_pBullet = (shared_ptr<vector<shared_ptr<EnemyBullet>>>)new vector<shared_ptr<EnemyBullet>>();
}