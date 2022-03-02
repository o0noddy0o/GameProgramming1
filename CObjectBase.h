//����������������������������������������������
// �t�@�C�����@�@�FCObjectBase.h
// �T�v�@�@�@�@�@�F���ׂĉ�ʂɏo���I�u�W�F�N�g�̐e�N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F�쐬
//����������������������������������������������
#pragma once
#include "GameConst.h"
#include "CActionGameApp.h"
#include "kadai0/UV.h"

class CPicture;

class CObjectBase
{
protected:
	// �R���X�g���N�^
	CObjectBase(GameInfo* _pGameInfo);

	// �f�X�g���N�^
	~CObjectBase();

	// �摜���쐬���郁�\�b�h
	CPicture* CreateSprite(LPCWSTR path_, float width_ = WINDOW_WIDTH, float height_ = WINDOW_HEIGHT, std::vector <QuadrangleTexel> _texelsUV = singleTexels);
	
	// �摜��j�����郁�\�b�h
	void DisposeSprite(CPicture* object);
	
	// �摜��`�悷�郁�\�b�h
	void RenderSprite(CPicture* object, XMFLOAT4 _col = XMFLOAT4(1.f, 1.f, 1.f, 1.f));

	CFont* createFont(LPCWSTR path_, int digits_, float width_, float height_, std::vector <QuadrangleTexel> _texelsUV = kTexelNumber);
	void renderFont(CFont* object, int num_, XMFLOAT4 _col = XMFLOAT4(1.f, 1.f, 1.f, 1.f));
	void disposeFont(CFont* object);

	void SetTexels(CPicture* _object, std::vector<QuadrangleTexel> _texels, XMFLOAT2 _size = { 0.f, 0.f });

	// ���͂��擾���郁�\�b�h
	std::shared_ptr<CDirectInput> GetInput();

protected:
	// �Q�[���̏��
	GameInfo* m_pGameInfo;
};