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
class BoundingBox;
class CircleBoundingBox;

class Barrier : public Component
{
	typedef Component Super;
public:
	Barrier(GameInfo* _pGameInfo, float _angle = 0.f, XMFLOAT2 _pos = { 0.f, 0.f });
	~Barrier();
	bool IsBarrierOn()const;
	void InputProcess(int _playerIndex, float _deltaTime);
	void renderSprite();
	float GetBarrierAngle()const;
	BoundingBox* GetBoundingBox()const;
	void SetPos(XMFLOAT2 _pos)override;

private:
	bool m_bIsBarrierOn;
	float m_angle;
	CircleBoundingBox* m_pBoundingBox;
};

