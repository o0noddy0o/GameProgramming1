//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CText.cpp
// 概要　　　　　：文字を表示するクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/10/27 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "CText.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
// 引数２：ファイルのパス
// 引数３：UV配列
// 引数４：一文字のサイズ
// 引数５：文字間隔
//━━━━━━━━━━━━━━━━━━━━━━━
CText::CText(GameInfo* _pGameInfo, LPCWSTR _path, vector<QuadrangleTexel> _uv, XMFLOAT2 _textSize, XMFLOAT2 _pos, XMFLOAT2 _letterSpacing)
	: Super(_pGameInfo)
	, m_path(_path)
	, m_UV(_uv)
	, m_textSize(_textSize)
	, m_letterSpacing(_letterSpacing)
	, m_pos(_pos)
	, m_digits(0)
	, m_renderDelayCnt(0)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
CText::~CText()
{
	for (unsigned int i = 0; i < m_pText.size(); ++i)
	{
		DisposeSprite(m_pText[i]);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 表示する文字列をセットする(string)
// 引数１：表示したい文字列
// ※ Ａ～Ｚ、０～９、スペースと特定な符号のみ表示できる
// 　（詳しいのはSetCharArrayメソッドを参考してください）
//━━━━━━━━━━━━━━━━━━━━━━━
void CText::SetText(string& _text)
{
	SetText(_text.c_str());
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 表示する文字列をセットする(char)
// 引数１：表示したい文字列
// ※ Ａ～Ｚ、０～９、スペースと特定な符号のみ表示できる
// 　（詳しいのはSetCharArrayメソッドを参考してください）
//━━━━━━━━━━━━━━━━━━━━━━━
void CText::SetText(const char* _text)
{
	m_digits = 0;
	m_renderDelayCnt = 0;
	
	SetCharArray(_text);

	while(m_pText.size() > m_digits)
	{
		m_pText.pop_back();
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// SetText()用のメソッド
// 引数１：表示したい文字
// 引数２：何番目の文字から表示する
// 引数３：何行目に表示する
// ※引数２と３は、再帰処理ためのもの、基本は使わない（このメソッド自体も）
//━━━━━━━━━━━━━━━━━━━━━━━
void CText::SetCharArray(const char* _text, unsigned int _start, unsigned int _lineIdx)
{
	int x = 0;
	for (unsigned int i = _start; _text[i + _lineIdx] != '\0'; ++i, ++x)
	{
		if (i >= m_pText.size())
		{
			m_pText.push_back(CreateSprite(m_path, m_textSize.x, m_textSize.y, m_UV));
		}
		++m_digits;
		int iChar = (int)_text[i + _lineIdx];

		// 改行
		if (iChar == '\n')
		{
			m_digits -= 1;
			return SetCharArray(_text, i, _lineIdx + 1);
		}
		// 数字（０～９）
		else if (iChar >= 48 && iChar <= 57)
		{
			iChar -= 48;
		}
		// アルファベット 大文字（Ａ～Ｚ）
		else if(iChar >= 65 && iChar <= 90)
		{
			iChar -= 55;
		}
		//// アルファベット 小文字（ａ～ｚ）
		//else if (iChar >= 97 && iChar <= 122)
		//{
		//	iChar -= 61;
		//}
		else if (iChar == '\"')
		{
			iChar = 36;
		}
		else if (iChar == ',')
		{
			iChar = 37;
		}
		else if (iChar == '.')
		{
			iChar = 38;
		}
		else if (iChar == '-')
		{
			iChar = 40;
		}
		else if (iChar == '!')
		{
			iChar = 41;
		}
		// 他は表示しない
		else
		{
			m_pText[i]->setActive(false);
			continue;
		}
		m_pText[i]->setActive(true);
		m_pText[i]->setAnimation(iChar);
		m_pText[i]->setPos(m_pos.x + (m_textSize.x + m_letterSpacing.x) * x, m_pos.y - (m_textSize.y + m_letterSpacing.y) * _lineIdx);
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 描画したい数字をセットする
// 引数１：描画したい数字
// 引数２：文字間隔
//━━━━━━━━━━━━━━━━━━━━━━━
void CText::SetNum(int _num, float _letterSpacing)
{
	if (_letterSpacing >= 0.f)
	{
		m_letterSpacing.x = _letterSpacing;
	}

	if (_num == 0)
	{
		m_digits = 2;

		// 桁数を調整
		while (m_pText.size() < m_digits)
		{
			m_pText.push_back(CreateSprite(m_path, m_textSize.x, m_textSize.y, m_UV));
		}

		for (int i = 0; i < m_digits; ++i)
		{
			m_pText[i]->setPos(m_pos.x - (m_letterSpacing.x + m_textSize.x) * i, m_pos.y);
			m_pText[i]->setAnimation(0);
		}
	}
	else
	{
		// 桁数を調べる
		m_digits = 0;

		for (int num = _num; num != 0; ++m_digits)
		{
			num /= 10;
		}

		// 桁数を調整
		while (m_pText.size() < m_digits)
		{
			m_pText.push_back(CreateSprite(m_path, m_textSize.x, m_textSize.y, m_UV));
		}

		int num = _num;
		for (int i = 0; i < m_digits; ++i)
		{
			m_pText[i]->setPos(m_pos.x - (m_letterSpacing.x + m_textSize.x) * i, m_pos.y);
			m_pText[i]->setAnimation(num % 10);
			num /= 10;
		}
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 文字列の描画する
// 引数１：一個文字を表示した後次の文字が表示されるまで何フレームかかるか
//         ゼロだったら最初から一気に描画する
// 引数２：表示させる色（デフォルトが全部）
//━━━━━━━━━━━━━━━━━━━━━━━
bool CText::RenderText(int _delay, XMFLOAT4 _color)
{
	if (m_renderDelayCnt < m_digits * _delay)
	{
		++m_renderDelayCnt;
	}
	for (int i = 0; i < m_digits; ++i)
	{
		if (i * _delay == 0)
		{
			RenderSprite(m_pText[i], _color);
		}
		else
		{
			if (m_renderDelayCnt / (i * _delay))
			{
				RenderSprite(m_pText[i], _color);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 文字列の位置をセットする
// 引数１：ｘ軸座標
// 引数２：ｙ軸座標
// ※文字をセットする前に使ってください！
//━━━━━━━━━━━━━━━━━━━━━━━
void CText::setPos(float x, float y)
{
	m_pos = XMFLOAT2(x, y);
	/*for (unsigned int i = 0; i < m_pText.size(); ++i)
	{
		m_pText[i]->setPos(m_pos.x + (m_textSize.x + m_letterSpacing.x) * i, m_pos.y);
	}*/
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 文字列の位置をセットする
// 引数１：新しい座標
// ※文字をセットする前に使ってください！
//━━━━━━━━━━━━━━━━━━━━━━━
void CText::setPos(XMFLOAT2 _pos)
{
	m_pos = _pos;
}

void CText::setOffset(XMFLOAT2 _pos)
{
	m_pos.x += _pos.x;
	m_pos.y += _pos.y;
}