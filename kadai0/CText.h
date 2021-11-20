//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CText.h
// 概要　　　　　：文字を表示するクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/10/27 作成
//━━━━━━━━━━━━━━━━━━━━━━━
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
	vector<CPicture*>		m_pText;			// 文字の画像
	LPCWSTR					m_path;				// 画像のパス
	XMFLOAT2				m_textSize;			// 一個文字のサイズ
	vector<QuadrangleTexel>	m_UV;				// UV
	XMFLOAT2				m_letterSpacing;	// 文字間隔
	XMFLOAT2				m_pos;				// 先頭文字の座標
	int						m_digits;			// 桁数
	int						m_renderDelayCnt;	// 
};