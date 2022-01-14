//����������������������������������������������
// �t�@�C�����@�@�FMissileLauncher.cpp
// �T�v�@�@�@�@�@�F�~�T�C�����ˋ@�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/01/14 �쐬
//����������������������������������������������
#include "MissileLauncher.h"
#include "GameResource.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F����̍��W
// �����R�F����̊p�x
//����������������������������������������������
MissileLauncher::MissileLauncher(GameInfo* _pGameInfo, XMFLOAT2 _pedestalPos, float _pedestalAngle)
	: Super(_pGameInfo)
	, m_angle(_pedestalAngle)
{
	m_pImg = CreateSprite(Tex_MissileLauncherHead, MISSILELAUNCHER_HEAD_SIZE_X, MISSILELAUNCHER_HEAD_SIZE_Y);
	m_pImg2 = CreateSprite(Tex_MissileLauncherPedestal, MISSILELAUNCHER_PEDESTAL_SIZE_X, MISSILELAUNCHER_PEDESTAL_SIZE_Y);
	m_pImg2->setPos(_pedestalPos);
	m_pImg2->addAngleZ(_pedestalAngle);

	XMFLOAT2 headPos = AngleToDirectionVector(_pedestalAngle);
	headPos.x *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	headPos.y *= MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL;
	_pedestalPos.x += headPos.x;
	_pedestalPos.y += headPos.y;
	m_pImg->setPos(_pedestalPos);
	m_pImg->addAngleZ(_pedestalAngle);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
MissileLauncher::~MissileLauncher()
{
	if (m_pImg)delete m_pImg;
	m_pImg = NULL;
	if (m_pImg2)delete m_pImg2;
}

//����������������������������������������������
// �摜��`�悷��
//����������������������������������������������
void MissileLauncher::renderSprite()
{

}

//����������������������������������������������
// �G�l�~�[�̍U��
//����������������������������������������������
void MissileLauncher::AttackProcess(XMFLOAT2 _SubmarinePos)
{
	XMFLOAT4 vector = m_pImg->getPos();
	vector.x -= m_pImg2->getPos().x;
	vector.y -= m_pImg2->getPos().y;
	NormalizeVector(vector);

	XMFLOAT2 vector2 = _SubmarinePos;
	vector2.x -= m_pImg2->getPos().x;
	vector2.y -= m_pImg2->getPos().y;
	NormalizeVector(vector2);

	if()
}

//����������������������������������������������
// �G�l�~�[�̈ړ��i���̃G�l�~�[���Ɩ����j
//����������������������������������������������
void MissileLauncher::MoveProcess()
{
}