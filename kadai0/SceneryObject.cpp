//����������������������������������������������
// �t�@�C�����@�@�FSceneryObject.cpp
// �T�v�@�@�@�@�@�F�X�e�[�W�ɏo�鑼�̕��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#include "SceneryObject.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�u���b�N�̏������W
// �����R�F�u���b�N�̏����p�x
//����������������������������������������������
SceneryObject::SceneryObject(GameInfo* _pGameInfo,XMFLOAT2 _pos,float _angle)
	:CObjectBase(_pGameInfo)
{
	m_pImg = CreateSprite(Tex_Rock,Block_X_SIZE,Block_Y_SIZE);
	m_pImg->setPos(_pos);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
SceneryObject::~SceneryObject()
{
	DisposeSprite(m_pImg);
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
void SceneryObject::Collision(CPicture* _pImg)
{

}