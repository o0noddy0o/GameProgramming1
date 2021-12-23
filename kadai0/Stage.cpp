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

	//�����͂��쐬
	m_pSubmarine = (shared_ptr<Submarine>)new Submarine(_pGameInfo);

	//��Q�����쐬
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new SceneryObject(m_pGameInfo, XMFLOAT2(0.f, -2500.f), (float)0.f));
	m_pSceneryObject.push_back((shared_ptr<SceneryObject>)new SceneryObject(m_pGameInfo, XMFLOAT2(2500.f, 500.f), (float)0.f));

	
	//
	int map[Map_Y_SIZE][Map_X_SIZE] = Stage01;
	//m_map = map;
	
	//�G���쐬
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(600.f,  850.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(810.f,   10.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-800.f, 200.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(720.f, -900.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-720.f,  90.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(580.f,  450.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(360.f,  180.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(410.f,  680.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(-860.f, 210.f), (float)rand()));
	m_pEnemy.push_back((shared_ptr<Enemy>)new Fish(m_pGameInfo, XMFLOAT2(380.f,   70.f), (float)rand()));

	for (int i = 0; i < (int)m_pEnemy.size(); ++i)
	{
		m_pEnemyBullet.push_back((shared_ptr<vector<shared_ptr<EnemyBullet>>>)(m_pEnemy[i])->GetBullet());
	}

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

	for (int i = 0; i < (int)m_pSceneryObject.size(); ++i)
	{
		m_pSceneryObject[i]->renderSprite();
	}

	for (int i = 0; i < (int)m_pEnemyBullet.size(); ++i)
	{
		for (int j = 0; j < (int)m_pEnemyBullet[i]->size(); ++j)
		{
			(*m_pEnemyBullet[i])[j].get()->renderSprite();
		}
	}

	for (int i = 0; i < (int)m_pEnemy.size(); ++i)
	{
		m_pEnemy[i]->renderSprite();
	}
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

	m_pSubmarine->CollisionProcess(&m_pEnemy, &m_pEnemyBullet, NULL, NULL);

	m_pSubmarine->Tick(m_deltaTime);
	{
		XMFLOAT2 SubmarinePos(m_pSubmarine->GetPos());
		for (int i = 0; i < (int)m_pEnemy.size(); ++i)
		{
			m_pEnemy[i]->AttackProcess();
			m_pEnemy[i]->MoveProcess(SubmarinePos, m_deltaTime);
		}
	}
	for (int i = 0; i < (int)m_pEnemyBullet.size(); ++i)
	{
		for (int j = 0; j < (int)m_pEnemyBullet[i].get()->size(); ++j)
		{
			(*m_pEnemyBullet[i])[j].get()->MoveProcess(m_deltaTime);
		}
	}
	m_pSubmarine->MoveProcess(m_deltaTime);

	
}