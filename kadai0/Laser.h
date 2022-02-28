//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Laser.cpp
// 概要　　　　　：レーザーのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/20 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "EnemyBullet.h"

class Laser : public EnemyBullet
{
	typedef EnemyBullet Super;
public:
	Laser(GameInfo* _pGameInfo, XMFLOAT2 _size, XMFLOAT2 _startPointPos, float _angle, bool _bMove = false);
	virtual ~Laser();

	virtual void SetPos(XMFLOAT2 _newStartPointPos)override;
	virtual void SetAngle(float _angle);
	virtual void SetOffsetAngle(float _angle);
	virtual void MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos = XMFLOAT2(0.f, 0.f))override;

	void renderSprite()override;

private:
	XMFLOAT2 m_pos;
	XMFLOAT2 m_size;
	float m_angle;
	bool m_bMove;
	std::vector<QuadrangleTexel> m_texels;
};