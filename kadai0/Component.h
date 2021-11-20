//����������������������������������������������
// �t�@�C�����@�@�FComponent.h
// �T�v�@�@�@�@�@�F�����͂̕��i
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/17 �쐬
//����������������������������������������������
#pragma once
#include "CObjectBase.h"

class Component : public CObjectBase
{
	typedef CObjectBase Super;
public:
	Component(GameInfo* _pGameInfo, XMFLOAT2 _relativePos = {0.f, 0.f});
	virtual ~Component();

	CPicture* GetImg();						// �摜���擾����
	virtual void renderSprite();			// �摜��`�悷��
	virtual void InputProcess() = 0;		// �v���C���[�̓��͏���
	virtual void SetPos(XMFLOAT2 _pos);		// �摜�̈ʒu��ݒu����

protected:
	CPicture* m_pImg;						// ���i�̉摜
	XMFLOAT2 m_relativePos;					// ���i�̍��W�Ɛ����͂̍��W�̍�
};