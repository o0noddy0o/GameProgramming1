//����������������������������������������������
// �t�@�C�����@�@�FOperationDevice.cpp
// �T�v�@�@�@�@�@�F���쑕�u�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0332 �t�A���X�A���Y��
// �X�V���e�@�@�@�F2021/11/29 �쐬�i�Y���j
//				  2021/12/01 �`�惁�\�b�h���`�i�Y���j
//����������������������������������������������
#include "OperationDevice.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
//����������������������������������������������
OperationDevice::OperationDevice(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _relativePos, int _index)
	: Super(_pGameInfo)
	, m_relativePos(_pos)
{
	switch (_index)
	{
	case 0:
		m_pImg = CreateSprite(Tex_Operation_Device_1, 64.f, 64.f);
		m_pImg->setPos(1500.f, 1500.f);
		break;
	case 1:
		m_pImg = CreateSprite(Tex_Operation_Device_2, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 2:
		m_pImg = CreateSprite(Tex_Operation_Device_3, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 3:
		m_pImg = CreateSprite(Tex_Operation_Device_4, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 4:
		m_pImg = CreateSprite(Tex_Operation_Device_5, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	/*case 5:
		m_pImg = CreateSprite(Tex_Operation_Device_4, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;*/
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
// ���t���[���ɂ�鏈��
//����������������������������������������������
void OperationDevice::Tick(float _deltaTime)
{
	
}

//����������������������������������������������
// �摜��`��
//����������������������������������������������
void OperationDevice::RenderDevice()
{
	RenderSprite(m_pImg);
}

//����������������������������������������������
// �v���C���[�Ƃ̓����蔻��
//����������������������������������������������
void OperationDevice::collisionWithPlayer(Player* _player)
{
	static bool b = false;
	if ((bool)m_pImg->collision(_player->GetImg()) == true)
	{
		if (GetInput()->isPressedOnce(DIK_M))
		{
			b = !b;
			_player->SetMoveAble(!b);
		}
		if (b)
		{
			m_pComponent->InputProcess();
		}
	}
}

//����������������������������������������������
// �Ή����镔�i�̃A�h���X�i�����̓N���X�p�j
//����������������������������������������������
void OperationDevice::SetComponent(shared_ptr<Component> _component)
{
	m_pComponent = _component.get();
}

//����������������������������������������������
// �摜�̈ʒu��ݒu
//����������������������������������������������
void OperationDevice::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos.x + m_relativePos.x, _newPos.y + m_relativePos.y);
}