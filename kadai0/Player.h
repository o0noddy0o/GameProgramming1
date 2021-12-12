//����������������������������������������������
// �t�@�C�����@�@�FPlayer.h
// �T�v�@�@�@�@�@�F�v���C���[�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0332 �t�A���X�A���Y��
// �X�V���e�@�@�@�F2021/11/24 �쐬�i�Y���j
//				   2021/11/25 ��{�̃��\�b�h��ǉ��i�Y���j
//				   2021/11/26 ��{�̃��\�b�h���C���i�Y���j
//				   2021/11/28 �ړ����\�b�h���C���i�Y���j
//							  �v���C���[���𕪂���i�Y���j
//����������������������������������������������
#pragma once
#include "Define.h"
#include "CObjectBase.h"
#include "Submarine.h"

class OperationDevice;

class Player : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Player(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, XMFLOAT2 _relativePos = { 0.f, 0.f }, int _index = 0);
	~Player();

	//���t���[���ɂ�鏈��
	void Tick(float _deltaTime, vector<Submarine::Wall>* _pWall, vector<Submarine::Floor>* _pFloor);

	//�摜��`��
	void RenderChara();

	//m_bMoveable�̒��g��ς���
	void SetMoveAble(bool _b);

	//�v���C�[�̍��W���X�V
	void SetPos(XMFLOAT2 _newPos);

	XMFLOAT2 GetPos()const;

	void SetRelativePos(XMFLOAT2 _relativePos);

	XMFLOAT2 GetRelativePos()const;

	//�v���C���[�̃W�����v
	void Jump();

	//
	CPicture* GetImg() const;

	//
	int getPlayerIdx() const;

private:
	//�v���C���[�̓��͏���
	void InputProcess();

	//�v���C���[�L�����N�^�[�Ɗe���쑕�u�̓����蔻��
	void CollisionWithOperationDevice(vector<shared_ptr<OperationDevice>>* _pOperationDevice);

	void CollisionWithWallAndFloor(vector < Submarine::Wall>* _pWall, vector<Submarine::Floor>* _pFloor);

	//�v���C���[�̈ړ�
	void Move(float _deltaTime);

	

	CPicture*	m_pImg;				//�v���C���[�L�����N�^�[�̉摜
	bool		m_bMoveable;		//�v���C���[���ړ��ł��邩�t���O
	bool		m_bJumping;			//�v���C���[���W�����v���Ă��邩�̃t���O

	float		m_jumpPower;
	float		m_jumpTime;

	bool		m_bIsOnFloor;		// �v���C���[���ڒn���Ă��邩�̃t���O
	bool		m_bMovingRight;
	bool		m_bMovingLeft;

	XMFLOAT2	m_relativePos;		//�v���C���[�̍��W�Ɛ����͂̍��W�̍�
	int			m_playerIndex;		//�v���C���[�̔ԍ�
};

