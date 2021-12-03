//����������������������������������������������
// �t�@�C�����@�@�FBarrier.cpp
// �T�v�@�@�@�@�@�F�o���A�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/21 �쐬
//����������������������������������������������
#include "Barrier.h"
#include "GameResource.h"
#include "Define.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�o���A�̌��������i�����̊p�x�j
// �����R�F�o���A�̏������W�i�����͂̍��W���̂܂܁j
//����������������������������������������������
Barrier::Barrier(GameInfo* _pGameInfo, float _angle, XMFLOAT2 _pos)
	: Super(_pGameInfo)
	, m_angle(_angle)
	, m_bIsBarrierOn(true)
{
	m_pImg = CreateSprite(Tex_Barrier, BARRIER_SIZE_X, BARRIER_SIZE_Y, kTexelBarrier);
	m_pImg->setPos(_pos);
	m_pImg->setAngleZ(_angle);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Barrier::~Barrier()
{
}

//����������������������������������������������
// �v���C���[�̓��͏���
//����������������������������������������������
void Barrier::InputProcess()
{
	if (GetInput()->isKeyPressed(DIK_LEFTARROW))
	{
		m_angle += BARRIER_ROTATION_SPEED;
		m_pImg->addAngleZ(m_angle);
		m_bIsBarrierOn = false;
	}
	else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
	{
		m_angle -= BARRIER_ROTATION_SPEED;
		m_pImg->addAngleZ(m_angle);
		m_bIsBarrierOn = false;
	}
	else
	{
		m_bIsBarrierOn = true;
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

//����������������������������������������������
// �e�̓����蔻��i�G�Ƃ́j
//����������������������������������������������
bool Barrier::Collision(vector<shared_ptr<Enemy>>* _target)
{
	return false;
}

//����������������������������������������������
// �e�̓����蔻��i��Q���Ƃ́j
//����������������������������������������������
bool Barrier::Collision(vector<shared_ptr<SceneryObject>>* _target)
{
	return false;
}
