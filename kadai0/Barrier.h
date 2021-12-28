//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Barrier.h
// 概要　　　　　：バリアのクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/11/21 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Component.h"

class Enemy;
class SceneryObject;

class Barrier : public Component
{
	typedef Component Super;
public:
	Barrier(GameInfo* _pGameInfo, float _angle = 0.f, XMFLOAT2 _pos = { 0.f, 0.f });
	~Barrier();
	void InputProcess(int _playerIndex, float _deltaTime);
	void renderSprite();
	/*bool Collision(vector<shared_ptr<Enemy>>* _target);*/				// 弾の当たり判定（敵との）
	/*bool Collision(vector<shared_ptr<SceneryObject>>* _target);*/		// 弾の当たり判定（障害物との）

private:
	bool m_bIsBarrierOn;
	float m_angle;
};

