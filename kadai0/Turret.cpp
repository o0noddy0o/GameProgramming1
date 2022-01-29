//����������������������������������������������
// �t�@�C�����@�@�FTurret.cpp
// �T�v�@�@�@�@�@�F�^���b�g�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/17 �쐬�i���j
// �@�@�@�@�@�@�@�F2021/11/21 �e��ł̃J�E���g�_�E����ǉ��i���j
// �@�@�@�@�@�@�@�F2021/12/23 InputProcess���\�b�h�̕ҏW�i�Q�[���p�b�h�̎����j�i���j
//����������������������������������������������
#include "Turret.h"
#include "Define.h"
#include "GameResource.h"
#include "Bullet.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�^���b�g�������Ă�������i�O�|���E�A�P�|����A�Q�[�����A�R�[�����j
// �����R�F�����͂̍��W
//����������������������������������������������
Turret::Turret(GameInfo* _pGameInfo, int _turretFace, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_coolDownCnt(0)
{
	m_pImg = CreateSprite(Tex_Turret, TURRET_SIZE_X, TURRET_SIZE_Y);

	switch(_turretFace % 4)
	{
	case 0:
		m_relativePos.x += TURRET_DISTANCE;
		m_angle = 0.f;
		break;
	case 1:
		m_relativePos.y -= TURRET_DISTANCE;
		m_angle = 270.f;
		break;
	case 2:
		m_relativePos.x -= TURRET_DISTANCE;
		m_angle = 180.f;
		break;
	case 3:
		m_relativePos.y += TURRET_DISTANCE;
		m_angle = 90.f;
		break;
	}

	m_pImg->setAngleZ(m_angle);

	m_rotationRange[0] = m_angle - TURRET_ROTATION_RANGE / 2.f;
	m_rotationRange[1] = m_angle + TURRET_ROTATION_RANGE / 2.f;

	m_pImg->setPos(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Turret::~Turret()
{
}

//����������������������������������������������
// �v���C���[�̓��͏���
// �����P�F�v���C���[�̔ԍ�
// �����Q�F�O�̃t���[���̏�������
//����������������������������������������������
void Turret::InputProcess(int _playerIndex, float _deltaTime)
{
	// �^���b�g�̉�]
	// �Q�[���p�b�h�̓��͂��擾
	float gamepadX = GetInput()->GetLeftAnalogStickX(_playerIndex - 1);
	if (Abs(gamepadX) > 0.05f)
	{
		m_angle -= TURRET_ROTATION_SPEED * _deltaTime * gamepadX;
		if (m_angle > m_rotationRange[1])
		{
			m_angle = m_rotationRange[1];
		}
		else if (m_angle < m_rotationRange[0])
		{
			m_angle = m_rotationRange[0];
		}
		m_pImg->setAngleZ(m_angle);
	}
	// �L�[�{�[�h����
	else
	{
		switch (_playerIndex)
		{
		case 1:
			// ��
			if (GetInput()->isKeyPressed(DIK_LEFTARROW))
			{
				if ((m_angle += TURRET_ROTATION_SPEED * _deltaTime) > m_rotationRange[1])
				{
					// �͈͂̐���
					m_angle = m_rotationRange[1];
				}
				m_pImg->setAngleZ(m_angle);
			}
			// �E
			else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
			{
				if ((m_angle -= TURRET_ROTATION_SPEED * _deltaTime) < m_rotationRange[0])
				{
					// �͈͂̐���
					m_angle = m_rotationRange[0];
				}
				m_pImg->setAngleZ(m_angle);
			}
			break;
		case 2:
			// ��
			if (GetInput()->isKeyPressed(DIK_A))
			{
				if ((m_angle += TURRET_ROTATION_SPEED * _deltaTime) > m_rotationRange[1])
				{
					// �͈͂̐���
					m_angle = m_rotationRange[1];
				}
				m_pImg->setAngleZ(m_angle);
			}
			// �E
			else if (GetInput()->isKeyPressed(DIK_D))
			{
				if ((m_angle -= TURRET_ROTATION_SPEED * _deltaTime) < m_rotationRange[0])
				{
					// �͈͂̐���
					m_angle = m_rotationRange[0];
				}
				m_pImg->setAngleZ(m_angle);
			}
			break;
		}
	}

	// �e��ł��x�̐���
	if (m_coolDownCnt < TURRET_COOL_DOWN)
	{
		m_coolDownCnt += _deltaTime;
	}
	else
	{
		if ((GetInput()->isKeyPressed(DIK_NUMPAD0) && _playerIndex == 1) ||
			(GetInput()->isKeyPressed(DIK_SPACE) && _playerIndex == 2) ||
			 GetInput()->IsGamePadButtonPressed(GAMEPAD_KEY_Action, _playerIndex - 1))
		{
			// �J�E���^�[�����Z�b�g����
			m_coolDownCnt = 0;

			// �e�̍��W���v�Z
			XMFLOAT4 pos = m_pImg->getPos();
			{
				XMFLOAT2 pos2 = AngleToDirectionVector(m_angle);
				pos.x += pos2.x * (TURRET_SIZE_X / 2.f) + pos2.x * 10.f;
				pos.y += pos2.y * (TURRET_SIZE_X / 2.f) + pos2.y * 10.f;
			}

			// �g����e��T��
			if (m_pBullet.size() >= 1)
			{
				for (unsigned int i = 0; i < m_pBullet.size(); ++i)
				{
					if (m_pBullet[i]->GetActive())
					{
						// �Ȃ�������V�����̂����
						if (i >= m_pBullet.size() - 1)
						{
							m_pBullet.push_back(shared_ptr<Bullet>(new Bullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
							break;
						}
					}
					else
					{
						// �������炻����g��
						m_pBullet[i]->SetActive(true);
						m_pBullet[i]->SetPos(XMFLOAT2(pos.x, pos.y));
						m_pBullet[i]->SetMoveDirection(m_angle);
						break;
					}
				}
			}
			else
			{
				m_pBullet.push_back(shared_ptr<Bullet>(new Bullet(m_pGameInfo, XMFLOAT2(pos.x, pos.y), m_angle)));
			}

		}
	}
}

//����������������������������������������������
// �e�̔z��̃A�h���X���擾����
//����������������������������������������������
vector<shared_ptr<Bullet>>* Turret::GetBullet()
{
	return &m_pBullet;
}

