//����������������������������������������������
// �t�@�C�����@�@�FUI.h
// �T�v�@�@�@�@�@�FUI�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/12/10 �쐬�i�S�j		   
//����������������������������������������������
#pragma once

#include "CObjectBase.h"
#include "CText.h"

class Map;

class UI : public CObjectBase
{
	typedef CObjectBase Super;
public:
	UI(GameInfo* _pGameInfo);
	~UI();

	void SetHP(float _newHp);
	void SetNumOfKilledEnemy(int _numOfKilledEnemy); // �ꎞ�I�Ɏg�����

	// �摜��`�悷��
	void renderSprite();

	// UI�̈ʒu��ݒu����
	void SetPos();

	// �n�}���X�V����(Map��UpdateMap()���Ăяo��
	void UpdateMap(XMFLOAT2 _submarinePos);

private:
	CPicture* m_pHpBar;
	CPicture* m_pFreamOfHpBar;
	Map*      m_pMap;
	CText*	  m_pNumOfEnemy;
	XMFLOAT2  m_hpBarRelativePos;
	string m_text;
};