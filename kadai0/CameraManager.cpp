//����������������������������������������������
// �t�@�C�����@�@�FCameraManager.h
// �T�v�@�@�@�@�@�F�J�����𐧌䂷��N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/01/29 �쐬
//����������������������������������������������
#include "CameraManager.h"

std::shared_ptr<CameraManager> CameraManager::pCameraManager = NULL;

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�J�����̃|�C���^�[
//����������������������������������������������
CameraManager::CameraManager(std::unique_ptr<CCamera>* _pCamera)
	: pCamera(_pCamera)
{
	m_cameraPos = pCamera->get()->getPos();
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
CameraManager::~CameraManager()
{
}

//����������������������������������������������
// �J�����̍��W���擾����
//����������������������������������������������
XMFLOAT3 CameraManager::GetCameraPos()
{
	return CameraManager::pCameraManager->m_cameraPos;
}

//����������������������������������������������
// �J�������Z�b�g�A�b�v����
//����������������������������������������������
void CameraManager::SetUpCamera(std::unique_ptr<CCamera>* _pCamera)
{
	CameraManager::pCameraManager = (std::shared_ptr<CameraManager>)new CameraManager(_pCamera);
}

//����������������������������������������������
// �J�����̍��W���Z�b�g����
//����������������������������������������������
void CameraManager::SetCameraPos(XMFLOAT2 _newPos)
{
	if(_newPos.x > CameraManager::pCameraManager->m_moveRangeMax.x)			_newPos.x = CameraManager::pCameraManager->m_moveRangeMax.x;
	else if(_newPos.x < CameraManager::pCameraManager->m_moveRangeMin.x)	_newPos.x = CameraManager::pCameraManager->m_moveRangeMin.x;

	if (_newPos.y > CameraManager::pCameraManager->m_moveRangeMax.y)		_newPos.y = CameraManager::pCameraManager->m_moveRangeMax.y;
	else if (_newPos.y < CameraManager::pCameraManager->m_moveRangeMin.y)	_newPos.y = CameraManager::pCameraManager->m_moveRangeMin.y;

	CameraManager::pCameraManager->m_cameraPos.x = _newPos.x;
	CameraManager::pCameraManager->m_cameraPos.y = _newPos.y;

	CameraManager::pCameraManager->pCamera->get()->setPos(CameraManager::pCameraManager->m_cameraPos);
}

//����������������������������������������������
// �J�����̍��W���Z�b�g����
//����������������������������������������������
void CameraManager::SetCameraPos(XMFLOAT3 _newPos)
{
	if (_newPos.x > CameraManager::pCameraManager->m_moveRangeMax.x)			_newPos.x = CameraManager::pCameraManager->m_moveRangeMax.x;
	else if (_newPos.x < CameraManager::pCameraManager->m_moveRangeMin.x)	_newPos.x = CameraManager::pCameraManager->m_moveRangeMin.x;

	if (_newPos.y > CameraManager::pCameraManager->m_moveRangeMax.y)		_newPos.y = CameraManager::pCameraManager->m_moveRangeMax.y;
	else if (_newPos.y < CameraManager::pCameraManager->m_moveRangeMin.y)	_newPos.y = CameraManager::pCameraManager->m_moveRangeMin.y;

	CameraManager::pCameraManager->m_cameraPos = _newPos;

	CameraManager::pCameraManager->pCamera->get()->setPos(_newPos);
}

//����������������������������������������������
// �J�����̈ړ��͈͂��Z�b�g����
//����������������������������������������������
void CameraManager::SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max)
{
	CameraManager::pCameraManager->m_moveRangeMin = _min;
	CameraManager::pCameraManager->m_moveRangeMax = _max;
}