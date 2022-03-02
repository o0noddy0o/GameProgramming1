/**
* @file CActionGameApp.h
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CApplication.h"
#include "CPicture.h"
#include "MediaResource.h"
#include "UVAnimation.h"
#include "CFont.h"
#include "CSourceVoice.h"

struct GameInfo
{
	ID3D11Device** pDevice;
	ID3D11DeviceContext** pDeviceContext;
	D3D11_VIEWPORT* pViewPort;
	std::unique_ptr<CCamera>* pCamera;
	std::shared_ptr<CDirectInput>* pDirectInput;
};

struct Data
{
	string dataName;
	string dataType;
	union
	{
		int     iData;
		float   fData;
		XMINT2	i2Data;
		XMFLOAT2 f2Data;
		XMFLOAT4 f4Data;
	};
	Data() {}
	Data(string _dataName, int _data) :dataName(_dataName), iData(_data), dataType("i") {}
	Data(string _dataName, float _data) :dataName(_dataName), fData(_data), dataType("f") {}
	Data(string _dataName, XMINT2 _data) :dataName(_dataName), i2Data(_data), dataType("i2") {}
	Data(string _dataName, XMFLOAT2 _data) :dataName(_dataName), f2Data(_data), dataType("f2") {}
	Data(string _dataName, XMFLOAT4 _data) :dataName(_dataName), f4Data(_data), dataType("f4") {}
	
	bool operator>(Data& _data)
	{
		if (((this->dataType == "f") ? (this->fData) : ((this->dataType == "i") ? ((float)this->iData):(this->i2Data.x))) >
			((_data.dataType == "f") ? (_data.fData) : ((_data.dataType == "i") ? ((float)_data.iData) : (_data.i2Data.x))))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class CText;
class InOutputFile;

class CActionGameApp :
	public CApplication
{
	typedef CApplication super;
private:
	//*****************************************************************
	//�yMethod�z <Private>
	//*****************************************************************
	int m_activeEnemies										= 0;

	CPicture* createSprite(LPCWSTR path_, float width_ = WINDOW_WIDTH, float height_ = WINDOW_HEIGHT);
	void renderSprite( CPicture* object);
	void renderSprite(CPicture* object, XMFLOAT3 color);
	void renderSprite(CPicture* object, float r, float g, float b);
	void renderSprite(CPicture* object, XMFLOAT4 color);
	void disposeSprite( CPicture* object);
	CFont* createFont(LPCWSTR path_, int digits_, float width_, float height_);
	void renderFont(CFont* object, int num_);
	void disposeFont(CFont* object);
	bool createSpaceship(void);
	void initCameraInfo();
	
	void doOpenning();
	void doPlaying();
	void doGameClear();
	void doGameOver();
	void doEnding();

	// �e��ʂ̃t���[
	void procTitle();
	void procGame();
	void procClear();
	void procGameOver();

	// �^�C�g����ʂ̃t�F�[�Y
	void procTitleBegin();
	void procTitleMain();
	void procTitleEnd();

	// �C���Q�[����ʂ̃t�F�[�Y
	void procPlayBegin();
	void procPlayMain();
	void procPlayEnd();

	// �Q�[���N���A��ʂ̃t�F�[�Y
	void procClearBegin();
	void procClearMain();
	void procClearEnd();

	// �Q�[���I�[�o�[��ʂ̃t�F�[�Y
	void procOverBegin();
	void procOverMain();
	void procOverEnd();

public:
	CActionGameApp();
	~CActionGameApp();
	void render(XMFLOAT4X4 matView, XMFLOAT4X4 matProj);
	void release();
	GameInfo* getGameInfo();

private:
	CXAudio2* pAudio = new CXAudio2;
	CPicture* pBackground = nullptr;

	

	// �X�e�[�W���Ǘ�����I�u�W�F�N�g
	CText* pText  = nullptr;
	InOutputFile* pInOutFile = nullptr;

	GameInfo gameInfo;
};
