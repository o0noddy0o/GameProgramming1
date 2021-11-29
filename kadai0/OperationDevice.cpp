//����������������������������������������������
// �t�@�C�����@�@�FOperationDevice.cpp
// �T�v�@�@�@�@�@�F���쑕�u�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0332 �t�A���X�A���Y��
// �X�V���e�@�@�@�F2021/11/29 �쐬�i�Y���j
//����������������������������������������������
#include "OperationDevice.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
//����������������������������������������������
OperationDevice::OperationDevice(GameInfo* _pGameInfo, XMFLOAT2 _pos, int _index)
	: Super(_pGameInfo)
{
	switch (_index)
	{
	case 1:
		m_pImg = CreateSprite(Tex_Operation_Device_1, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 2:
		m_pImg = CreateSprite(Tex_Operation_Device_2, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 3:
		m_pImg = CreateSprite(Tex_Operation_Device_3, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 4:
		m_pImg = CreateSprite(Tex_Operation_Device_4, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	}
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
OperationDevice::~OperationDevice()
{
	DisposeSprite(m_pImg);
}

//����������������������������������������������
// �v���C���[�Ƃ̓����蔻��
//����������������������������������������������
void OperationDevice::collisionWithPlayer(Player _player)
{

}

//����������������������������������������������
// �Ή����镔�i�̃A�h���X�i�����̓N���X�p�j
//����������������������������������������������
void OperationDevice::SetComponent(shared_ptr<Component> _component)
{

}

//����������������������������������������������
// �摜�̈ʒu��ݒu
//����������������������������������������������
void OperationDevice::SetPos(XMFLOAT2 _newPos)
{

}