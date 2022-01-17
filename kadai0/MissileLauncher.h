//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：MissileLauncher.h
// 概要　　　　　：ミサイル発射機のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2022/01/14 作成（呉）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Enemy.h"

class CircleBoundingBox;

class MissileLauncher : public Enemy
{
	typedef Enemy Super;
public:
	MissileLauncher(GameInfo* _pGameInfo, XMFLOAT2 _pedestalPos, float _pedestalAngle = 0.f);
	virtual ~MissileLauncher();

	virtual void renderSprite()override;

	virtual void AttackProcess(XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f))override;

	virtual void MoveProcess(XMFLOAT2 _SubmarinePos, float _deltaTime)override;

	virtual BoundingBox* GetBoundingBox()const override;

	void SetPosAndAngle(XMFLOAT2 _newPos, float _newAngle);

private:
	CPicture* m_pImg2;
	float m_angle;
	int m_coolDownCnt;
	int m_coolDown;
	CircleBoundingBox* m_pBoundingBox;
};