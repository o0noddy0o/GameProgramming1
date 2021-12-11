//����������������������������������������������
// �t�@�C�����@�@�FOperationDevice.h
// �T�v�@�@�@�@�@�F���쑕�u�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0332 �t�A���X�A���Y��
// �X�V���e�@�@�@�F2021/11/29 �쐬�i�Y���j
//				  2021/12/01 �`�惁�\�b�h���`�i�Y���j
//����������������������������������������������
#pragma once
#include "Define.h"
#include "Component.h"
#include "CObjectBase.h"
#include "Player.h"


class OperationDevice : public CObjectBase
{
	typedef CObjectBase Super;
public:
	OperationDevice(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, XMFLOAT2 _relativePos = { 0.f, 0.f }, int _index = 0);
	~OperationDevice();

	//���t���[���̍X�V����
	void Tick(float _deltaTime);

	//�摜��`��
	void RenderDevice();

	//�v���C���[�Ƃ̓����蔻��
	void collisionWithPlayer(Player* _player, float _deltaTime);

	//�Ή����镔�i�̃A�h���X�i�����̓N���X�p�j
	void SetComponent(shared_ptr<Component> _component);

	//�摜�̈ʒu��ݒu
	void SetPos(XMFLOAT2 _newPos);

private:
	//���쑕�u�̉摜
	CPicture* m_pImg;

	//���쑕�u�̍��W�Ɛ����͂̍��W�̍�
	XMFLOAT2 m_relativePos;

	//�Ή����镔�i�̃A�h���X
	Component* m_pComponent;

	bool m_bPlayer1IsUsing;
	bool m_bPlayer2IsUsing;
};