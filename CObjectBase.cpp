//����������������������������������������������
// �t�@�C�����@�@�FCObjectBase.cpp
// �T�v�@�@�@�@�@�F���ׂĉ�ʂɏo���I�u�W�F�N�g�̐e�N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F�쐬
//����������������������������������������������
#include "CObjectBase.h"
#include "CPicture.h"
#include "MediaResource.h"
#include "CCamera.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
//����������������������������������������������
CObjectBase::CObjectBase(GameInfo* _pGameInfo) 
	: m_pGameInfo(_pGameInfo)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
CObjectBase::~CObjectBase()
{
}

//����������������������������������������������
// �摜���쐬���郁�\�b�h
//����������������������������������������������
CPicture* CObjectBase::CreateSprite(LPCWSTR path_, float width_, float height_, std::vector <QuadrangleTexel> _texelsUV)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CPicture* object = NULL;

	// ��{�I�ȍ쐬
	object = CPicture::create(*(m_pGameInfo->pDevice), *(m_pGameInfo->pDeviceContext), (m_pGameInfo->pViewPort), HLSL_AlphaHLSL, path_,
		{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< �X�v���C�g�̈ʒu
		spriteSize,					//!< �X�v���C�g�̃T�C�Y
		_texelsUV);				//!< �w�肷��UV���W�̔z��
	return object;
}

//����������������������������������������������
// �摜��j�����郁�\�b�h
//����������������������������������������������
void CObjectBase::DisposeSprite(CPicture* object)
{
	if (object != NULL)
	{
		object->release();
	}
}

//����������������������������������������������
// �摜��`�悷�郁�\�b�h
//����������������������������������������������
void CObjectBase::RenderSprite(CPicture* object, XMFLOAT4 _col)
{
	XMFLOAT4X4	matView = (*m_pGameInfo->pCamera)->getViewMatrix();		 //!< �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	XMFLOAT4X4	matProj = (*m_pGameInfo->pCamera)->getProjectionMatrix();	 //!< �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	if (object != NULL)
	{
		object->render(matView, matProj, 0Ui64, _col);
	}
}

CFont* CObjectBase::createFont(LPCWSTR path_, int digits_, float width_, float height_, std::vector <QuadrangleTexel> _texelsUV)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CFont* objects = NULL;

	objects = CFont::create(*(m_pGameInfo->pDevice), *(m_pGameInfo->pDeviceContext), (m_pGameInfo->pViewPort), HLSL_PlaneHLSL, path_,
		{ 0.0f, 0.0f, 0.0f, 0.0f },	// �X�v���C�g�̈ʒu
		spriteSize,					// �X�v���C�g�̃T�C�Y
		_texelsUV,					// �w�肷��UV���W�̔z��
		digits_);					// ����

	return objects;
}

void CObjectBase::renderFont(CFont* object, int num_, XMFLOAT4 _col)
{
	XMFLOAT4X4	matView = (*m_pGameInfo->pCamera)->getViewMatrix();		 //!< �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	XMFLOAT4X4	matProj = (*m_pGameInfo->pCamera)->getProjectionMatrix();	 //!< �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	if (object != NULL)
	{
		object->render(matView, matProj, num_, 0Ui64, _col);
	}
}

void CObjectBase::disposeFont(CFont* object)
{
	if (object != NULL)
	{
		object->release();
	}
}

//����������������������������������������������
// ���͂��擾���郁�\�b�h
//����������������������������������������������
std::shared_ptr<CDirectInput> CObjectBase::GetInput()
{
	return *(m_pGameInfo->pDirectInput);
}