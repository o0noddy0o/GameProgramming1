//����������������������������������������������
// �t�@�C�����@�@�FBoss.cpp
// �T�v�@�@�@�@�@�F�{�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/17 �쐬�i���j
//����������������������������������������������
#include "Boss.h"
#include "BoundingBox.h"

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

// �摜�̕`��
void Boss::renderSprite()
{
	for (int i = 0; i < (int)m_pImg.size(); ++i)
	{
		if(m_pImg[i])RenderSprite(m_pImg[i]);
	}
}

vector<BoundingBox*>* Boss::GetBoundingBox()const
{
	return (vector<BoundingBox*>*)&m_pBoundingBox;
}

// �e�̔z����擾����
shared_ptr<vector<shared_ptr<EnemyBullet>>>	Boss::GetBossBullet()
{
	return m_pBullet;
}

void Boss::ResetBossBullet()
{
	Boss::m_pBullet = (shared_ptr<vector<shared_ptr<EnemyBullet>>>)new vector<shared_ptr<EnemyBullet>>();
}