//����������������������������������������������
// �t�@�C�����@�@�FSceneryObject.h
// �T�v�@�@�@�@�@�F�X�e�[�W�ɏo�鑼�̕��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/11/26 �쐬
// �@�@�@�@�@�@�@�F2021/01/12 �R���X�g���N�^��ҏW
// �@�@�@�@�@�@�@�@           GetBoundingBox���\�b�h�ǉ�
//����������������������������������������������
#pragma once
#include "CObjectBase.h"
#include "Define.h"
#include "BoundingBox.h"

class SceneryObject : public CObjectBase
{
public:
	SceneryObject(GameInfo* _pGameInfo);
	virtual ~SceneryObject();

	// �摜���擾����i�����蔻��p�j
	CPicture* GetImg() const;

	// �����蔻��
	virtual BoundingBox* GetBoundingBox()const;

	// �摜��`�悷��
	virtual void renderSprite();


protected:
	// �摜
	CPicture* m_pImg;
	BoundingBox* m_pBoundingBox;
};

