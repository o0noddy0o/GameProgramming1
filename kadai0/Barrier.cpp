//����������������������������������������������
// �t�@�C�����@�@�FBarrier.cpp
// �T�v�@�@�@�@�@�F�o���A�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/21 �쐬�i���j
// �@�@�@�@�@�@�@�F2021/12/23 InputProcess���\�b�h�̕ҏW�i�Q�[���p�b�h�̎����j�i���j
//����������������������������������������������
#include "Barrier.h"
#include "GameResource.h"
#include "Define.h"
#include "CircleBoundingBox.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�o���A�̌��������i�����̊p�x�j
// �����R�F�o���A�̏������W�i�����͂̍��W���̂܂܁j
//����������������������������������������������
Barrier::Barrier(GameInfo* _pGameInfo, float _angle, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_angle(_angle + 90.f)
	, m_bIsBarrierOn(true)
{
	m_pImg = CreateSprite(Tex_Barrier, BARRIER_SIZE_X, BARRIER_SIZE_Y, kTexelBarrier);
	m_pImg->setPos(_pos);
	m_pImg->setAngleZ(_angle);
	m_pBoundingBox = new CircleBoundingBox(_pos, BARRIER_SIZE_X / 2.f);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Barrier::~Barrier()
{
	if (m_pBoundingBox)delete m_pBoundingBox;
}

bool Barrier::IsBarrierOn()const
{
	return m_bIsBarrierOn;
}

//����������������������������������������������
// �v���C���[�̓��͏���
// �����P�F�v���C���[�̔ԍ�
// �����Q�F�O�̃t���[���̏�������
//����������������������������������������������
void Barrier::InputProcess(int _playerIndex, float _deltaTime)
{
	// �Q�[���p�b�h�̓��͂��擾
	float gamepadX = GetInput()->GetAnalogStickX(_playerIndex - 1);
	if (Abs(gamepadX) > 0.05f)
	{
		m_angle -= BARRIER_ROTATION_SPEED * _deltaTime * gamepadX;
		m_pImg->setAngleZ(m_angle - 90.f);
		//m_bIsBarrierOn = false;
	}

	switch (_playerIndex)
	{
	case 1:
		// ��
		if (GetInput()->isKeyPressed(DIK_LEFTARROW))
		{
			m_angle += BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// �E
		else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
		{
			m_angle -= BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// �ړ����ĂȂ�������A�o���A���I���ɂ���
		else
		{
			m_bIsBarrierOn = true;
		}
		break;

	case 2:
		// ��
		if (GetInput()->isKeyPressed(DIK_A))
		{
			m_angle += BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// �E
		else if (GetInput()->isKeyPressed(DIK_D))
		{
			m_angle -= BARRIER_ROTATION_SPEED * _deltaTime;
			m_pImg->setAngleZ(m_angle - 90.f);
			//m_bIsBarrierOn = false;
		}

		// �ړ����ĂȂ�������A�o���A���I���ɂ���
		else
		{
			m_bIsBarrierOn = true;
		}
		break;
	}
	
}

//����������������������������������������������
// �o���A�̉摜��`�悷��
//����������������������������������������������
void Barrier::renderSprite()
{
	if (m_bIsBarrierOn)
	{
		RenderSprite(m_pImg);
	}
}

float Barrier::GetBarrierAngle()const
{
	return m_angle;
}

BoundingBox* Barrier::GetBoundingBox()const
{
	return m_pBoundingBox;
}

void Barrier::SetPos(XMFLOAT2 _pos)
{
	m_pImg->setPos(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y);
	m_pBoundingBox->SetPos(XMFLOAT2(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y));
}