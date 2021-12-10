//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：JetEngine.h
// 概要　　　　　：ジェットエンジンのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/19 作成
//━━━━━━━━━━━━━━━━━━━━━━━
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

