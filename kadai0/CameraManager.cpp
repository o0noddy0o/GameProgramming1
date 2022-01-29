//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CameraManager.h
// 概要　　　　　：カメラを制御するクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/29 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "CameraManager.h"

std::shared_ptr<CameraManager> CameraManager::pCameraManager = NULL;

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：カメラのポインター
//━━━━━━━━━━━━━━━━━━━━━━━
CameraManager::CameraManager(std::unique_ptr<CCamera>* _pCamera)
	: pCamera(_pCamera)
{
	m_cameraPos = pCamera->get()->getPos();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
CameraManager::~CameraManager()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラの座標を取得する
//━━━━━━━━━━━━━━━━━━━━━━━
XMFLOAT3 CameraManager::GetCameraPos()
{
	return CameraManager::pCameraManager->m_cameraPos;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラをセットアップする
//━━━━━━━━━━━━━━━━━━━━━━━
void CameraManager::SetUpCamera(std::unique_ptr<CCamera>* _pCamera)
{
	CameraManager::pCameraManager = (std::shared_ptr<CameraManager>)new CameraManager(_pCamera);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラの座標をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
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

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラの座標をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void CameraManager::SetCameraPos(XMFLOAT3 _newPos)
{
	if (_newPos.x > CameraManager::pCameraManager->m_moveRangeMax.x)			_newPos.x = CameraManager::pCameraManager->m_moveRangeMax.x;
	else if (_newPos.x < CameraManager::pCameraManager->m_moveRangeMin.x)	_newPos.x = CameraManager::pCameraManager->m_moveRangeMin.x;

	if (_newPos.y > CameraManager::pCameraManager->m_moveRangeMax.y)		_newPos.y = CameraManager::pCameraManager->m_moveRangeMax.y;
	else if (_newPos.y < CameraManager::pCameraManager->m_moveRangeMin.y)	_newPos.y = CameraManager::pCameraManager->m_moveRangeMin.y;

	CameraManager::pCameraManager->m_cameraPos = _newPos;

	CameraManager::pCameraManager->pCamera->get()->setPos(_newPos);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラの移動範囲をセットする
//━━━━━━━━━━━━━━━━━━━━━━━
void CameraManager::SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max)
{
	CameraManager::pCameraManager->m_moveRangeMin = _min;
	CameraManager::pCameraManager->m_moveRangeMax = _max;
}