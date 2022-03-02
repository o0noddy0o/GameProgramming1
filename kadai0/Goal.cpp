//����������������������������������������������
// �t�@�C�����@�@�FGoal.cpp
// �T�v�@�@�@�@�@�F�S�[���̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/02/16 �쐬�i���j
//����������������������������������������������
#include "Goal.h"
#include "RectangleBoundingBox.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
//����������������������������������������������
Goal::Goal(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _size)
	: Super(_pGameInfo)
	, m_pImg(NULL)
	, m_pBoundingBox(NULL)
{
	m_pImg = CreateSprite(Tex_TestImage1, _size.x, _size.y);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, _size);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Goal::~Goal()
{
	delete m_pBoundingBox;
	DisposeSprite(m_pImg);
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X���擾
//����������������������������������������������
BoundingBox* Goal::GetBoundingBox()const
{
	return (BoundingBox*)m_pBoundingBox;
}

void Goal::rendingSprite()
{
	RenderSprite(m_pImg);
}

//����������������������������������������������
// �S�[���̍��W���擾����
//����������������������������������������������
XMFLOAT2 Goal::GetPos()const
{
	return XMFLOAT2(m_pImg->getPos().x, m_pImg->getPos().y);
}