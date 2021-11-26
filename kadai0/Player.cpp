//����������������������������������������������
// �t�@�C�����@�@�FPlayer.cpp
// �T�v�@�@�@�@�@�F�v���C���[�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0332 �t�A���X�A���Y��
// �X�V���e�@�@�@�F2021/11/24 �쐬
//����������������������������������������������
#include "Player.h"
#include "Define.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
//����������������������������������������������
Player::Player(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _relativePos)
	: Super(_pGameInfo)
	, m_bMoveable(true)
	, m_pJumping(false)
	, m_relativePos(_pos)
{
	m_pImg = CreateSprite(Tex_Player1, 256.f, 256.f);
	m_pImg->setPos(_pos);

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
//����������������������������������������������
void Player::Jump(float _deltaTime)
{

}
