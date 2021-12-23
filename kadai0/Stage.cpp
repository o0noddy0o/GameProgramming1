//����������������������������������������������
// �t�@�C�����@�@�FStage.cpp
// �T�v�@�@�@�@�@�F�X�e�[�W�ɏo�鑼�̕��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/01 �쐬
//			�@�@�@2021/12/08�@�G�̒e�𔭎ˋ@�\��ǉ�
//			�@�@�@2021/12/10�@�G�̈ړ�������ǉ�
//����������������������������������������������

#include "Stage.h"
#include "GameResource.h"
#include "SceneryObject.h"
#include "Submarine.h"
#include "Map.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Fish.h"
#include "Fish2.h"
#include <time.h>

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
//����������������������������������������������
Stage::Stage(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
	, m_pSubmarine(NULL)
{
	srand((unsigned)time(NULL));

	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(_pGameInfo);
	//
	int map[Map_Y_SIZE][Map_X_SIZE] = Stage01;
	//m_map = map;
	
#if HaveEnemy
	Enemy::ResetEnemyBullet();

	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish2(m_pGameInfo, XMFLOAT2((rand() % int(WINDOW_WIDTH * 2.f) + 960.f) * ((rand() % 2 == 0) ? (1) : (-1)), (rand() % int(WINDOW_HEIGHT * 2.f) + 540.f) * ((rand() % 2 == 0) ? (1) : (-1))), (float)rand()));

	m_pEnemyBullet = Enemy::GetBullet();
#endif

	m_lastFrameTime = clock();
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Stage::~Stage()
{
}

//����������������������������������������������
// �G�̉摜�̕`�揈��
//����������������������������������������������
void Stage::RenderProcess()
{
	m_pSubmarine->RenderProcess();
#if HaveEnemy
	for (int i = 0; i < (int)m_pEnemyBullet->size(); ++i)
	{
		(*m_pEnemyBullet)[i].get()->renderSprite();
	}

	for (int i = 0; i < (int)m_pEnemy.size(); ++i)
	{
		m_pEnemy[i]->renderSprite();
	}
#endif
}

//����������������������������������������������
// �����蔻��
//����������������������������������������������
void Stage::CollisionProcess()
{
}

//����������������������������������������������
// ���t���[���ɂ�鏈��
//����������������������������������������������
void Stage::Tick()
{
	{
		clock_t thisFrameTime = clock();
		m_deltaTime = (float)(thisFrameTime - m_lastFrameTime) / 1000.f;
		m_lastFrameTime = thisFrameTime;
	}

	m_pSubmarine->CollisionProcess(&m_pEnemy, m_pEnemyBullet, NULL, NULL);

	m_pSubmarine->Tick(m_deltaTime);
	{
		XMFLOAT2 SubmarinePos(m_pSubmarine->GetPos());
		for (int i = 0; i < (int)m_pEnemy.size(); ++i)
		{
			m_pEnemy[i]->AttackProcess();
			m_pEnemy[i]->MoveProcess(SubmarinePos, m_deltaTime);
		}
	}
#if HaveEnemy
	for (int i = 0; i < (int)m_pEnemyBullet->size(); ++i)
	{
		(*m_pEnemyBullet)[i].get()->MoveProcess(m_deltaTime);
	}
#endif
	m_pSubmarine->MoveProcess(m_deltaTime);

}

int Stage::GetKilledEnemyCnt()const
{
	return m_pSubmarine->GetKilledEnemyCnt();
}