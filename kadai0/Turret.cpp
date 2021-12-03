//����������������������������������������������
// �t�@�C�����@�@�FTurret.cpp
// �T�v�@�@�@�@�@�F�^���b�g�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/17 �쐬
// �@�@�@�@�@�@�@�F2021/11/21 �e��ł̃J�E���g�_�E����ǉ�
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
	
	m_angle = (float)_turretFace * 90.f;
	m_pImg->setAngleZ(m_angle);

	m_rotationRange[0] = m_angle - TURRET_ROTATION_RANGE / 2.f;
	m_rotationRange[1] = m_angle + TURRET_ROTATION_RANGE / 2.f;

	switch(_turretFace % 4)
	{
	case 0:
		m_relativePos.x += TURRET_DISTANCE;
		break;
	case 1:
		m_relativePos.y += TURRET_DISTANCE;
		break;
	case 2:
		m_relativePos.x -= TURRET_DISTANCE;
		break;
	case 3:
		m_relativePos.y -= TURRET_DISTANCE;
		break;
	}

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
//����������������������������������������������
void Turret::InputProcess()
{
	if (GetInput()->isKeyPressed(DIK_LEFTARROW))
	{
		if ((m_angle += TURRET_ROTATION_SPEED) > m_rotationRange[1])
		{
			m_angle = m_rotationRange[1];
		}
		m_pImg->setAngleZ(m_angle);
	}
	else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
	{
		if ((m_angle -= TURRET_ROTATION_SPEED) < m_rotationRange[0])
		{
			m_angle = m_rotationRange[0];
		}
		m_pImg->setAngleZ(m_angle);
	}

	// �e��ł��x�̐���
	if (m_coolDownCnt < TURRET_COOL_DOWN)
	{
		++m_coolDownCnt;
	}
	else
	{
		if (GetInput()->isKeyPressed(DIK_SPACE))
		{
			// �J�E���^�[�����Z�b�g����
			m_coolDownCnt = 0;

			// �e�̍��W���v�Z
			XMFLOAT4 pos = m_pImg->getPos();
			{
				XMFLOAT2 pos2 = AngleToDirectionVector(m_angle);
				pos.x += pos2.x * (TURRET_SIZE_X / 2.f);
				pos.y += pos2.y * (TURRET_SIZE_X / 2.f);
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

