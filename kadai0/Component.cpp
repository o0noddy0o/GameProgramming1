//����������������������������������������������
// �t�@�C�����@�@�FComponent.cpp
// �T�v�@�@�@�@�@�F�����͂̕��i
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/17 �쐬
//����������������������������������������������
#include "Component.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F���i�̍��W�Ɛ����͂̍��W�̍�
//����������������������������������������������
Component::Component(GameInfo* _pGameInfo, XMFLOAT2 _relativePos)
	: Super(_pGameInfo)
	, m_pImg(nullptr)
	, m_relativePos(_relativePos)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Component::~Component()
{
	if (m_pImg)delete m_pImg;
}

//����������������������������������������������
// ���i�̉摜���擾����
//����������������������������������������������
CPicture* Component::GetImg()
{
	return m_pImg;
}

void Component::renderSprite(float _alpha)
{
	RenderSprite(m_pImg, XMFLOAT4(1.f, 1.f, 1.f, _alpha));
}

//����������������������������������������������
// �摜�̈ʒu��ݒu����
//����������������������������������������������
void Component::SetPos(XMFLOAT2 _pos)
{
	m_pImg->setPos(_pos.x + m_relativePos.x, _pos.y + m_relativePos.y);
}