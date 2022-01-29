//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CameraManager.h
// 概要　　　　　：カメラを制御するクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/29 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "ActionGame.h"
#include "Stage.h"

class CameraManager
{
public:
	CameraManager(std::unique_ptr<CCamera>* _pCamera);
	~CameraManager();

	// カメラの座標を取得する
	static XMFLOAT3 GetCameraPos();

	friend Submarine::Submarine(GameInfo*, XMFLOAT2);
	friend void Submarine::MoveCamera(float);
	friend Stage::Stage(GameInfo*);
	friend void Stage::SetCameraPos(XMFLOAT2 _newPos);
	friend void Stage::SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max);

private:
	// カメラをセットアップする
	static void SetUpCamera(std::unique_ptr<CCamera>* _pCamera);

	// カメラの座標をセットする
	static void SetCameraPos(XMFLOAT2 _newPos);
	static void SetCameraPos(XMFLOAT3 _newPos);

	// カメラの移動範囲をセットする
	static void SetCameraMoveRange(XMFLOAT2 _min, XMFLOAT2 _max);

	// クラス変数
	static std::shared_ptr<CameraManager> pCameraManager;

private:
	std::unique_ptr<CCamera>* pCamera;	// カメラのポインター
	XMFLOAT3 m_cameraPos;				// カメラの座標
	XMFLOAT2 m_moveRangeMax;			// カメラの移動範囲（最大値）
	XMFLOAT2 m_moveRangeMin;			// カメラの移動範囲（最初値）
};

