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
	, m_movePower(1.f)
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
	m_movePower = 1.f;
	if (_playerIndex != SPECIAL_MOVE_PLAYER_INDEX)
	{
		// �Q�[���p�b�h�̓��͂��擾
		float gamepadX = GetInput()->GetLeftAnalogStickX(_playerIndex - 1);
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
	else
	{
		// �Q�[���p�b�h�̓��͂��擾
		XMFLOAT2 gamepad = { GetInput()->GetLeftAnalogStickX(_playerIndex - 1), GetInput()->GetLeftAnalogStickY(_playerIndex - 1) };
		if (Abs(gamepad.x) > 0.05f || Abs(gamepad.y) > 0.05f)
		{
			m_moveDirection = DirectionVectorToAngle(gamepad);
			m_pImg->setAngleZ(m_moveDirection);
			m_bIsMoving = true;
			m_movePower = Abs(gamepad.x) + Abs(gamepad.y);
			if (m_movePower > 1.f)m_movePower = 1.f;
		}

		// �L�[�{�[�h�̓���
		switch (_playerIndex)
		{
		case 1:
			// ��
			if (GetInput()->isKeyPressed(DIK_LEFTARROW))
			{
				if (GetInput()->isKeyPressed(DIK_UPARROW))
				{
					m_moveDirection = 135.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else if (GetInput()->isKeyPressed(DIK_DOWNARROW))
				{
					m_moveDirection = 225.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else
				{
					m_moveDirection = 180.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				m_bIsMoving = true;
			}
			// �E
			else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
			{
				if (GetInput()->isKeyPressed(DIK_UPARROW))
				{
					m_moveDirection = 45.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else if (GetInput()->isKeyPressed(DIK_DOWNARROW))
				{
					m_moveDirection = 315.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else
				{
					m_moveDirection = 0.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				m_bIsMoving = true;
			}
			// ��
			else if (GetInput()->isKeyPressed(DIK_UPARROW))
			{
				m_moveDirection = 90.f;
				m_pImg->setAngleZ(m_moveDirection);
				m_bIsMoving = true;
			}
			// ��
			else if (GetInput()->isKeyPressed(DIK_DOWNARROW))
			{
				m_moveDirection = 270.f;
				m_pImg->setAngleZ(m_moveDirection);
				m_bIsMoving = true;
			}

			break;

		case 2:
			// ��
			if (GetInput()->isKeyPressed(DIK_A))
			{
				if (GetInput()->isKeyPressed(DIK_W))
				{
					m_moveDirection = 135.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else if (GetInput()->isKeyPressed(DIK_S))
				{
					m_moveDirection = 225.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else
				{
					m_moveDirection = 180.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				m_bIsMoving = true;
			}
			// �E
			else if (GetInput()->isKeyPressed(DIK_D))
			{
				if (GetInput()->isKeyPressed(DIK_W))
				{
					m_moveDirection = 45.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else if (GetInput()->isKeyPressed(DIK_S))
				{
					m_moveDirection = 315.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				else
				{
					m_moveDirection = 0.f;
					m_pImg->setAngleZ(m_moveDirection);
				}
				m_bIsMoving = true;
			}
			// ��
			else if (GetInput()->isKeyPressed(DIK_W))
			{
				m_moveDirection = 90.f;
				m_pImg->setAngleZ(m_moveDirection);
				m_bIsMoving = true;
			}
			// ��
			else if (GetInput()->isKeyPressed(DIK_S))
			{
				m_moveDirection = 270.f;
				m_pImg->setAngleZ(m_moveDirection);
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

float JetEngine::GetMovePower()const
{
	return m_movePower;
}
