//����������������������������������������������
// �t�@�C�����@�@�FEnemy.cpp
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//			�@�@�@2021/12/08�@�G�̒e�𔭎ˋ@�\��ǉ�
//			�@�@�@2021/12/10�@�G�̈ړ�������ǉ�
//����������������������������������������������
#include "GameResource.h"
#include "Enemy.h"
#include "BoundingBox.h"

// ����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
//����������������������������������������������
Enemy::Enemy(GameInfo* _pGameInfo, float _damage)
	: CObjectBase(_pGameInfo)
	, m_pImg(NULL)
	, m_damage(_damage)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Enemy::~Enemy()
{
	DisposeSprite(m_pImg);
}

shared_ptr<vector<shared_ptr<EnemyBullet>>> Enemy::m_pEnemyBullet;

//����������������������������������������������
// �G�̉摜��`��
//����������������������������������������������
void Enemy::renderSprite()
{
	RenderSprite(m_pImg);
}

//����������������������������������������������
// �e�̎擾
//����������������������������������������������
shared_ptr<vector<shared_ptr<EnemyBullet>>> Enemy::GetBullet()
{
	return m_pEnemyBullet;
}

float Enemy::GetDamage()const
{
	return m_damage;
}

void Enemy::ResetEnemyBullet()
{
	m_pEnemyBullet = (shared_ptr<vector<shared_ptr<EnemyBullet>>>)new vector<shared_ptr<EnemyBullet>>;
}
