//����������������������������������������������
// �t�@�C�����@�@�FBarrier.h
// �T�v�@�@�@�@�@�F�o���A�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/21 �쐬
//����������������������������������������������
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
	/*bool Collision(vector<shared_ptr<Enemy>>* _target);*/				// �e�̓����蔻��i�G�Ƃ́j
	/*bool Collision(vector<shared_ptr<SceneryObject>>* _target);*/		// �e�̓����蔻��i��Q���Ƃ́j

private:
	bool m_bIsBarrierOn;
	float m_angle;
};

