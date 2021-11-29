//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Player.h
// 概要　　　　　：プレイヤーのクラス
// 作成者　　　　：20CU0332 フアンスアンズン
// 更新内容　　　：2021/11/24 作成（ズン）
//				   2021/11/25 基本のメソッドを追加（ズン）
//				   2021/11/26 基本のメソッドを修正（ズン）
//				   2021/11/28 移動メソッドを修正（ズン）
//							  プレイヤー数を分ける（ズン）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Define.h"
#include "CObjectBase.h"

class OperationDevice;

class Player : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Player(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, XMFLOAT2 _relativePos = { 0.f, 0.f }, int _index = 0);
	~Player();

	//毎フレームにやる処理
	void Tick(float _deltaTime);

	//画像を描画
	void RenderChara();

	//m_bMoveableの中身を変える
	void SetMoveAble(bool _b);

	//プレイーの座標を更新
	void SetPos(XMFLOAT2 _newPos);

	

private:
	//プレイヤーの入力処理
	void InputProcess();

	//プレイヤーキャラクターと各操作装置の当たり判定
	void CollisionWithOperationDevice(vector<shared_ptr<OperationDevice>>* _pOperationDevice);

	//プレイヤーの移動
	void Move(float _deltaTime, bool _right);

	//プレイヤーのジャンプ
	void Jump(float _deltaTime);

	CPicture*	m_pImg;				//プレイヤーキャラクターの画像
	bool		m_bMoveable;		//プレイヤーが移動できるかフラグ
	bool		m_pJumping;			//プレイヤーがジャンプしているかのフラグ
	XMFLOAT2	m_relativePos;		//プレイヤーの座標と潜水艦の座標の差
	
};

