//����������������������������������������������
// �t�@�C�����@�@�FPlayer.cpp
// �T�v�@�@�@�@�@�F�v���C���[�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0332 �t�A���X�A���Y��
// �X�V���e�@�@�@�F2021/11/24 �쐬�i�Y���j
//				   2021/11/25 ��{�̃��\�b�h��ǉ��i�Y���j
//				   2021/11/26 ��{�̃��\�b�h���C���i�Y���j
//				   2021/11/28 �ړ����\�b�h���C���i�Y���j
//							  �v���C���[���𕪂���i�Y���j
//				   2021/12/03 �ړ����\�b�h���C���i�Y���j
//	
//����������������������������������������������
#include "Player.h"
#include "Define.h"
#include "GameResource.h"
#include "Submarine.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�v���C���[�̏������W
// �����R�F�v���C���[�̍��W�Ɛ����͂̍��W�̍�
// �����S�F�v���C���[�̔ԍ�
//����������������������������������������������
Player::Player(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _relativePos, int _index)
	: Super(_pGameInfo)
	, m_bMoveable(true)
	, m_pJumping(false)
	, m_relativePos(_pos)
	, m__playerIndex(_index)
{
	switch (_index)
	{
	//�v���C���[�P�̉摜���쐬
	case 1:
		m_pImg = CreateSprite(Tex_Player1, PLAYER_1_SIZE_X, PLAYER_1_SIZE_Y);
		m_pImg->setPos(_pos);
		break;
	//�v���C���[�P�̉摜���쐬
	case 2:
		m_pImg = CreateSprite(Tex_Player2, PLAYER_2_SIZE_X, PLAYER_2_SIZE_Y);
		m_pImg->setPos(_pos);
		break;
	}

}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Player::~Player()
{
	DisposeSprite(m_pImg);
}

//����������������������������������������������
// ���t���[���ɂ�鏈��
//����������������������������������������������
void Player::Tick(float _deltaTime)
{
	InputProcess();
}

//����������������������������������������������
// �摜��`��
//����������������������������������������������
void Player::RenderChara()
{
	RenderSprite(m_pImg);
}

//����������������������������������������������
// m_bMoveable�̒��g��ς���
//����������������������������������������������
void Player::SetMoveAble(bool _b)
{
	if (_b == false)
	{
		m_bMoveable = false;
	}
	else
	{
		m_bMoveable = true;
	}
}

//����������������������������������������������
// �v���C�[�̍��W���X�V
//����������������������������������������������
void Player::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos.x + m_relativePos.x, _newPos.y + m_relativePos.y);
}

//����������������������������������������������
// �v���C���[�̓��͏���
//����������������������������������������������
void Player::InputProcess()
{
	switch (getPlayerIdx())
	{
	case 1:
		if (m_bMoveable)
		{
			//���Ɉړ�
			if (GetInput()->isKeyPressed(DIK_LEFTARROW))
			{
				m_relativePos.x -= PLAYER_1_MOVE_SPEED;
			}
			//�E�Ɉړ�
			else if (GetInput()->isKeyPressed(DIK_RIGHTARROW))
			{
				m_relativePos.x += PLAYER_1_MOVE_SPEED;
			}
		}
		break;
	case 2:
		if (m_bMoveable)
		{
			//���Ɉړ�
			if (GetInput()->isKeyPressed(DIK_A))
			{
				m_relativePos.x -= PLAYER_2_MOVE_SPEED;
			}
			//�E�Ɉړ�
			else if (GetInput()->isKeyPressed(DIK_D))
			{
				m_relativePos.x += PLAYER_2_MOVE_SPEED;
			}
		}
		break;
	}
	
	
}

//����������������������������������������������
// �v���C���[�L�����N�^�[�Ɗe���쑕�u�̓����蔻��
//����������������������������������������������
void Player::CollisionWithOperationDevice(vector<shared_ptr<OperationDevice>>* _pOperationDevice)
{

}

//����������������������������������������������
// �v���C���[�̈ړ�
//����������������������������������������������
void Player::Move(float _deltaTime, bool _right)
{
	
}

//����������������������������������������������
// �v���C���[�̃W�����v
//
//����������������������������������������������
void Player::Jump(float _deltaTime)
{

}

//
CPicture* Player::GetImg() const
{
	return m_pImg;
}

//
int Player::getPlayerIdx() const
{
	return m__playerIndex;
}