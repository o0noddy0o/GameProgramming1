//����������������������������������������������
// �t�@�C�����@�@�FSceneryObject.h
// �T�v�@�@�@�@�@�F�X�e�[�W�ɏo�鑼�̕��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#pragma once
#include "CObjectBase.h"
#include "Define.h"

class SceneryObject : public CObjectBase
{
public:
	SceneryObject(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f,0.f }, float _angle = 0.f);
	~SceneryObject();

	// �摜���擾����i�����蔻��p�j
	CPicture* GetImg() const;

	// �����蔻��
	virtual void Collision(CPicture* _pImg);

	// �摜��`�悷��
	virtual void renderSprite();


protected:
	// �摜
	CPicture* m_pImg;
};

