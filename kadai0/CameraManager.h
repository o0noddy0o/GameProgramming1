//����������������������������������������������
// �t�@�C�����@�@�FCameraManager.h
// �T�v�@�@�@�@�@�F�J�����𐧌䂷��N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/29 �쐬
//����������������������������������������������
#pragma once
#include "ActionGame.h"
#include "Stage.h"

class CameraManager
{
public:
	CameraManager(std::unique_ptr<CCamera>* _pCamera);
	~CameraManager();

	// �J�����̍��W���擾����
	static XMFLOAT3 GetCameraPos();

	friend Submarine::Submarine(GameInfo*, XMFLOAT2);
	friend void Submarine::MoveCamera(float);
	friend Stage::Stage(GameInfo*);
	friend void Stage::SetCameraPos(XMFLOAT2 _newPos);
	friend void Stage::SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max);

private:
	// �J�������Z�b�g�A�b�v����
	static void SetUpCamera(std::unique_ptr<CCamera>* _pCamera);

	// �J�����̍��W���Z�b�g����
	static void SetCameraPos(XMFLOAT2 _newPos);
	static void SetCameraPos(XMFLOAT3 _newPos);

	// �J�����̈ړ��͈͂��Z�b�g����
	static void SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max);

	// �N���X�ϐ�
	static std::shared_ptr<CameraManager> pCameraManager;

private:
	std::unique_ptr<CCamera>* pCamera;	// �J�����̃|�C���^�[
	XMFLOAT3 m_cameraPos;				// �J�����̍��W
	XMFLOAT2 m_moveRangeMax;			// �J�����̈ړ��͈́i�ő�l�j
	XMFLOAT2 m_moveRangeMin;			// �J�����̈ړ��͈́i�ŏ��l�j
};

