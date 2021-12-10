//����������������������������������������������
// �t�@�C�����@�@�FTurret.h
// �T�v�@�@�@�@�@�F�^���b�g�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/17 �쐬
// �@�@�@�@�@�@�@�F2021/11/21 �e��ł̃J�E���g�_�E����ǉ�
//����������������������������������������������
#pragma once
#include "Component.h"

class Bullet;

class Turret : public Component
{
	typedef Component Super;
public:
	Turret(GameInfo* _pGameInfo, int _turretFace = 0, XMFLOAT2 _pos = { 0.f, 0.f });
	~Turret();

	void InputProcess(int _playerIndex);			// �v���C���[�̓��͏���
	vector<shared_ptr<Bullet>>* GetBullet();	// �e�̔z��̃A�h���X���擾����

private:
	vector<shared_ptr<Bullet>> m_pBullet;		// �e�̔z��
	float m_angle;								// �^���b�g�̊p�x
	float m_rotationRange[2];					// �^���b�g����]�ł���͈�
	float m_coolDownCnt;						// �^���b�g�̃N�[���_�E���̃J�E���^�[
};