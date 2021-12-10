//����������������������������������������������
// �t�@�C�����@�@�FJetEngine.h
// �T�v�@�@�@�@�@�F�W�F�b�g�G���W���̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/19 �쐬
//����������������������������������������������
#pragma once
#include "Component.h"

class Submarine;

class JetEngine : public Component
{
	typedef Component Super;

public:
	JetEngine(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, float m_moveDirection = 0.f);
	~JetEngine();

	void InputProcess(int _playerIndex);
	bool GetIsMoving()const;
	void SetIsMoveingToFalse();
	float GetMoveDirection()const;

private:
	float m_moveDirection;
	bool m_bIsMoving;
};

