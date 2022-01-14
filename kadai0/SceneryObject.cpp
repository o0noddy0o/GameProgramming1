//����������������������������������������������
// �t�@�C�����@�@�FSceneryObject.cpp
// �T�v�@�@�@�@�@�F�X�e�[�W�ɏo�鑼�̕��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/11/26 �쐬
// �@�@�@�@�@�@�@�F2021/01/12 �R���X�g���N�^��ҏW
// �@�@�@�@�@�@�@�@           GetBoundingBox���\�b�h�ǉ�
//����������������������������������������������
#include "SceneryObject.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�u���b�N�̏������W
// �����R�F�u���b�N�̏����p�x
//����������������������������������������������
SceneryObject::SceneryObject(GameInfo* _pGameInfo)
	:CObjectBase(_pGameInfo)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
SceneryObject::~SceneryObject()
{
	DisposeSprite(m_pImg);
	if (m_pBoundingBox)delete m_pBoundingBox;
}

//����������������������������������������������
// �u���b�N�̉摜���擾
//����������������������������������������������
CPicture* SceneryObject::GetImg()const
{
	return m_pImg;
}

//����������������������������������������������
// �u���b�N�̉摜��`��
//����������������������������������������������
void SceneryObject::renderSprite()
{
	RenderSprite(m_pImg);
}

//����������������������������������������������
// �u���b�N�̉摜��`��
//����������������������������������������������
BoundingBox* SceneryObject::GetBoundingBox()const
{
	return m_pBoundingBox;
}