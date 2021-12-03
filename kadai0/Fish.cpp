//����������������������������������������������
// �t�@�C�����@�@�FFish.h
// �T�v�@�@�@�@�@�F�G�N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/03 �쐬
//����������������������������������������������
#include "Fish.h"
#include "GameResource.h"
#include "RectangleBoundingBox.h"

// ����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�G�̏������W
//����������������������������������������������
Fish::Fish(GameInfo* _pGameInfo, XMFLOAT2 _pos)
	:Enemy(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_Enemy, Enemy_X_SIZE, Enemy_Y_SIZE);
	m_pImg->setPos(_pos);
	m_pBoundingBox = new RectangleBoundingBox(_pos, XMFLOAT2(Enemy_X_SIZE, Enemy_Y_SIZE));
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Fish::~Fish()
{
	delete m_pBoundingBox;
}

//����������������������������������������������
// �U���̏���
//����������������������������������������������
void Fish::AttackProcess()
{
}

//����������������������������������������������
// �ړ�����
//����������������������������������������������
void Fish::MoveProcess()
{
}

BoundingBox* Fish::GetBoundingBox()const
{
	return (BoundingBox*)m_pBoundingBox;
}