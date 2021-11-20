//����������������������������������������������
// �t�@�C�����@�@�FCText.h
// �T�v�@�@�@�@�@�F������\������N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/10/27 �쐬
//����������������������������������������������
#pragma once

#include "CObjectBase.h"

class CText : public CObjectBase
{
	typedef CObjectBase Super;
public:

	CText(GameInfo* _pGameInfo, LPCWSTR _path, vector<QuadrangleTexel> _uv, XMFLOAT2 _textSize, XMFLOAT2 _pos, XMFLOAT2 _letterSpacing = {0.f, 0.f});
	~CText();

	void SetText(string& _text);
	void SetText(const char* _text);
	void SetNum(int _num, float _letterSpacing = -1.f);
	bool RenderText(int _delay = 0, XMFLOAT4 _color = XMFLOAT4(1.f, 1.f, 1.f, 1.f));

	void setPos(float x, float y);
	void setPos(XMFLOAT2 _pos);
	void setOffset(XMFLOAT2 _pos);

private:
	void SetCharArray(const char* _text, unsigned int _start = 0, unsigned int _lineIdx = 0);

private:
	vector<CPicture*>		m_pText;			// �����̉摜
	LPCWSTR					m_path;				// �摜�̃p�X
	XMFLOAT2				m_textSize;			// ������̃T�C�Y
	vector<QuadrangleTexel>	m_UV;				// UV
	XMFLOAT2				m_letterSpacing;	// �����Ԋu
	XMFLOAT2				m_pos;				// �擪�����̍��W
	int						m_digits;			// ����
	int						m_renderDelayCnt;	// 
};