//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Boss.cpp
// 概要　　　　　：ボスのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/17 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Boss.h"
#include "BoundingBox.h"
#include "GameResource.h"
#include "CameraManager.h"

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
	if(m_pFreamOfHpBar)DisposeSprite(m_pFreamOfHpBar);
	if(m_pHpBar)DisposeSprite(m_pHpBar);
}

// 画像の描画
void Boss::renderSprite()
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)
	{
		if(m_pImg[i])RenderSprite(m_pImg[i]);
	}
	if (m_pFreamOfHpBar)RenderSprite(m_pFreamOfHpBar);
	if (m_pHpBar)RenderSprite(m_pHpBar);
}

vector<BoundingBox*>* Boss::GetBoundingBox()const
{
	return (vector<BoundingBox*>*)&m_pBoundingBox;
}

// 弾の配列を取得する
shared_ptr<vector<shared_ptr<EnemyBullet>>>	Boss::GetBossBullet()
{
	return m_pBullet;
}

void Boss::ResetBossBullet()
{
	Boss::m_pBullet = (shared_ptr<vector<shared_ptr<EnemyBullet>>>)new vector<shared_ptr<EnemyBullet>>();
}

void Boss::GetDamege(int _damage)
{
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();
	m_hp -= _damage;
	float percents = (float)m_hp / (float)m_maxHp;
	if (m_hp < 0.f)throw (string)"GameClear";
	m_pHpBar->setScale(percents, 1.f);
	m_pHpBar->setPos(cameraPos.x + m_hpBarRelativePos.x - m_hpBarSize.x / 2.f + m_hpBarSize.x * percents / 2.f, cameraPos.y + m_hpBarRelativePos.y);
}