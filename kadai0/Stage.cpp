//����������������������������������������������
// �t�@�C�����@�@�FStage.cpp
// �T�v�@�@�@�@�@�F�X�e�[�W�ɏo�鑼�̕��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/12/01 �쐬
//����������������������������������������������

#include "Stage.h"
#include "GameResource.h"
#include "SceneryObject.h"
#include "Submarine.h"
#include "Map.h"
#include "Enemy.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
//����������������������������������������������
Stage::Stage(GameInfo* _pGameInfo)
	: Super(_pGameInfo)
{
	//
	int map[Map_Y_SIZE][Map_X_SIZE] = Stage01;
	//m_map = map;

}

void Stage::RenderProcess()
{
	XMFLOAT3 cameraPoa = m_pGameInfo->pCamera->get()->getPos();





}