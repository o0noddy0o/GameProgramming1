//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Fire.h
// 概要　　　　　：火の弾のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/19 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "EnemyBullet.h"

class Fire : public EnemyBullet
{
	typedef EnemyBullet Super;
public:
	Fire(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _moveDirection, int _disappearCnt);
	virtual ~Fire();
	virtual void renderSprite()override;
	virtual void MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f))override;
	void SetDisappearTime(int _newDisappearTime);
	virtual void SetMoveDirection(float _angle)override;
	virtual void SetMoveDirection(XMFLOAT2 _moveDirection)override;

private:
	int m_disappearCnt;
	int m_disappearTime;
};