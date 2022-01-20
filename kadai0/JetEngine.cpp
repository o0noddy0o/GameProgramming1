//����������������������������������������������
// �t�@�C�����@�@�FJetEngine.cpp
// �T�v�@�@�@�@�@�F�W�F�b�g�G���W���̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/19 �쐬�i���j
// �@�@�@�@�@�@�@�F2021/12/23 InputProcess���\�b�h�̕ҏW�i�Q�[���p�b�h�̎����j�A�R�����g�̒ǉ��i���j
//����������������������������������������������
#include "Define.h"
#include "JetEngine.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�������W
// �����R�F�����͂̏����ړ�����
//����������������������������������������������
JetEngine::JetEngine(GameInfo* _pGameInfo, XMFLOAT2 _pos, float m_moveDirection)
	: Super(_pGameInfo)
	, m_moveDirection(m_moveDirection)
	, m_bIsMoving(false)
{
	m_pImg = CreateSprite(Tex_JetEngine, JET_ENGINE_SIZE_X, JET_ENGINE_SIZE_Y);
	m_pImg->setPos(_pos);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
JetEngine::~JetEngine()
{
}

//����������������������������������������������
// �v���C���[�̓��͏���
// �����P�F�v���C���[�̔ԍ�
// �����Q�F�O�̃t���[���̏�������
//����������������������������������������������
void JetEngine::InputProcess(int _playerIndex, float _deltaTime)
{
	// �^���b�g�̉�]
	// �Q�[���p�b�h�̓��͂��擾
	float gamepadX = GetInput()->GetAnalogStickX(_playerIndex - 1);
	if (Abs(gamepadX) > 0.05f)
	{
		m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime * gamepadX;
		m_pImg->setAngleZ(m_moveDirection);
	}
	if (GetInput()->IsGamePadButtonPressed(GAMEPAD_KEY_Action, _playerIndex - 1))
	{
		m_bIsMoving = true;
	}

	// �L�[�{�[�h�̓���
	switch (_playerIndex)
	{
	case 1:
		// ��
		if (GetInput()->isKeyPressed(DIK_LEFTARROW))
		{
			m_moveDirection += JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		// �E
		else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
		{
			m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		// �ړ�
		if (GetInput()->isKeyPressed(DIK_NUMPAD0))
		{
			m_bIsMoving = true;
		}
		break;

	case 2:
		// ��
		if (GetInput()->isKeyPressed(DIK_A))
		{
			m_moveDirection += JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}
		// �E
		else if (GetInput()->isKeyPressed(DIK_D))
		{
			m_moveDirection -= JET_ENGINE_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_moveDirection);
		}

		// �ړ�
		if (GetInput()->isKeyPressed(DIK_SPACE))
		{
			m_bIsMoving = true;
		}
		break;
	}
	if (Degree(m_moveDirection) > 90.f && Degree(m_moveDirection) < 270.f)
	{
		m_pImg->setAngle(180.f, 0.f, m_moveDirection);
	}
	else
	{
		m_pImg->setAngle(0.f, 0.f, m_moveDirection);
	}
}

//����������������������������������������������
// �����͂̈ړ��t���O���擾
//����������������������������������������������
bool JetEngine::GetIsMoving()const
{
	return m_bIsMoving;
}

//����������������������������������������������
// �����͂̈ړ��t���O��false�ɂ���
//����������������������������������������������
void JetEngine::SetIsMoveingToFalse()
{
	m_bIsMoving = false;
}

//����������������������������������������������
// �ړ��������擾����
//����������������������������������������������
float JetEngine::GetMoveDirection()const
{
	return m_moveDirection;
}