//����������������������������������������������
// �t�@�C�����@�@�FSubmarine.cpp
// �T�v�@�@�@�@�@�F�����͂̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/17 �쐬
//����������������������������������������������
#include "Submarine.h"
#include "GameResource.h"
#include "Turret.h"
#include "JetEngine.h"
#include "Player.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
//����������������������������������������������
Submarine::Submarine(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_Submarine, 512.f, 512.f);
	m_pImg->setPos(m_pos);

	// �v���C���[�I�u�W�F�N�g�̍쐬
	m_pPlayer[0] = shared_ptr<Player>(new Player(m_pGameInfo));
	m_pPlayer[1] = shared_ptr<Player>(new Player(m_pGameInfo));

	// ���i�I�u�W�F�N�g�̂̍쐬
	m_pComponent[0] = shared_ptr<Component>(new Turret(m_pGameInfo, 0, m_pos));
	m_pComponent[1] = shared_ptr<Component>(new Turret(m_pGameInfo, 1, m_pos));
	m_pComponent[2] = shared_ptr<Component>(new Turret(m_pGameInfo, 2, m_pos));
	m_pComponent[3] = shared_ptr<Component>(new Turret(m_pGameInfo, 3, m_pos));
	m_pComponent[4] = shared_ptr<Component>(new JetEngine(m_pGameInfo));
	/*m_pComponent[5] = shared_ptr<Component>(new Barrier());*/

	// �e�̔z��̃A�h���X�ۑ����Ă���
	for (int i = 0; i < 4; ++i)
	{
		m_pBullet[i] = ((Turret*)(m_pComponent[i].get()))->GetBullet();
	}

	// ���쑕�u�I�u�W�F�N�g�̍쐬
	/*for (int i = 0; i < NUM_OF_OPERATION_DEVICE; ++i)
	{
		m_pOperationDevice[i] = shared_ptr<OperationDevice>(new OperationDevice());
		m_pOperationDevice[i]->SetComponent(m_pComponent[i]);
	}*/
	
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Submarine::~Submarine()
{
	DisposeSprite(m_pImg);
}

//����������������������������������������������
// ���t���[���ɂ�鏈��
//����������������������������������������������
void Submarine::Tick(float _deltaTime)
{
	// �e�X�g�p
	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		m_pComponent[i]->InputProcess();
	}

	MoveProcess(_deltaTime);

	MoveCamera();
}

//����������������������������������������������
// �摜��`�悷��
//����������������������������������������������
void Submarine::RenderProcess()
{
	m_pComponent[4]->renderSprite();
	RenderSprite(m_pImg);
	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		// �W�F�b�g�G���W���͐����͂̉��̕`�悷��
		if (i == 4)
		{
			continue;
		}
		m_pComponent[i]->renderSprite();
	}
	m_pPlayer[0]->RenderChara();
	m_pPlayer[1]->RenderChara();
}

//����������������������������������������������
// �����蔻��
//����������������������������������������������
void Submarine::CollisionProcess(
	vector < shared_ptr < Enemy> >* _pEnemy,
	vector < shared_ptr < SceneryObject > >* _pSceneryObject,
	vector < shared_ptr < Bullet > >** _pBullet,
	vector < shared_ptr < Item > >* _pItem)
{
}

//����������������������������������������������
// �����͑S�̂̈ړ�
//����������������������������������������������
void Submarine::MoveProcess(float _deltaTime)
{
	static JetEngine* pJetEngine = (JetEngine*)m_pComponent[4].get();

	// �ړ��������`�F�b�N����
	if (!pJetEngine->GetIsMoving())return;

	float moveDirection = pJetEngine->GetMoveDirection();

	// �����͂̐V�������W���v�Z
	XMFLOAT2 offsetPos = AngleToDirectionVector(moveDirection);
	m_pos.x += offsetPos.x * SUBMARINE_MOVE_SPEED;
	m_pos.y += offsetPos.y * SUBMARINE_MOVE_SPEED;

	// �����͂̈ʒu��ݒu����
	m_pImg->setPos(m_pos);

	// ���ׂĕ��i���ړ�������
	for (int i = 0; i < NUM_OF_COMPONENT; ++i)
	{
		m_pComponent[i]->SetPos(m_pos);
	}

	pJetEngine->SetIsMoveingToFalse();
}

//����������������������������������������������
// �A�C�e�����擾������̏���
//����������������������������������������������
void Submarine::GetItem(int _itemType)
{
}

//����������������������������������������������
// �J�����̈ړ�����
//����������������������������������������������
void Submarine::MoveCamera()
{
	// �J�����̍��W���擾����
	XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();

	// �J�����Ɛ����͂̊Ԃ̋������v�Z
	XMFLOAT2 distanceBetweenCameraAndSubmarine = 
	{ m_pos.x - cameraPos.x, m_pos.y - cameraPos.y };

	cameraPos.x += distanceBetweenCameraAndSubmarine.x * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;
	cameraPos.y += distanceBetweenCameraAndSubmarine.y * PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE;

	m_pGameInfo->pCamera->get()->setPos(cameraPos);
}