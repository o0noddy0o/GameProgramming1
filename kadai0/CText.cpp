//����������������������������������������������
// �t�@�C�����@�@�FCText.cpp
// �T�v�@�@�@�@�@�F������\������N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/10/27 �쐬
//����������������������������������������������
#include "CText.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�t�@�C���̃p�X
// �����R�FUV�z��
// �����S�F�ꕶ���̃T�C�Y
// �����T�F�����Ԋu
//����������������������������������������������
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

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
CText::~CText()
{
	for (unsigned int i = 0; i < m_pText.size(); ++i)
	{
		DisposeSprite(m_pText[i]);
	}
}

//����������������������������������������������
// �\�����镶������Z�b�g����(string)
// �����P�F�\��������������
// �� �`�`�y�A�O�`�X�A�X�y�[�X�Ɠ���ȕ����̂ݕ\���ł���
// �@�i�ڂ����̂�SetCharArray���\�b�h���Q�l���Ă��������j
//����������������������������������������������
void CText::SetText(string& _text)
{
	SetText(_text.c_str());
}

//����������������������������������������������
// �\�����镶������Z�b�g����(char)
// �����P�F�\��������������
// �� �`�`�y�A�O�`�X�A�X�y�[�X�Ɠ���ȕ����̂ݕ\���ł���
// �@�i�ڂ����̂�SetCharArray���\�b�h���Q�l���Ă��������j
//����������������������������������������������
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

//����������������������������������������������
// SetText()�p�̃��\�b�h
// �����P�F�\������������
// �����Q�F���Ԗڂ̕�������\������
// �����R�F���s�ڂɕ\������
// �������Q�ƂR�́A�ċA�������߂̂��́A��{�͎g��Ȃ��i���̃��\�b�h���̂��j
//����������������������������������������������
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

		// ���s
		if (iChar == '\n')
		{
			m_digits -= 1;
			return SetCharArray(_text, i, _lineIdx + 1);
		}
		// �����i�O�`�X�j
		else if (iChar >= 48 && iChar <= 57)
		{
			iChar -= 48;
		}
		// �A���t�@�x�b�g �啶���i�`�`�y�j
		else if(iChar >= 65 && iChar <= 90)
		{
			iChar -= 55;
		}
		//// �A���t�@�x�b�g �������i���`���j
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
		// ���͕\�����Ȃ�
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

//����������������������������������������������
// �`�悵�����������Z�b�g����
// �����P�F�`�悵��������
// �����Q�F�����Ԋu
//����������������������������������������������
void CText::SetNum(int _num, float _letterSpacing)
{
	if (_letterSpacing >= 0.f)
	{
		m_letterSpacing.x = _letterSpacing;
	}

	if (_num == 0)
	{
		m_digits = 2;

		// �����𒲐�
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
		// �����𒲂ׂ�
		m_digits = 0;

		for (int num = _num; num != 0; ++m_digits)
		{
			num /= 10;
		}

		// �����𒲐�
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

//����������������������������������������������
// ������̕`�悷��
// �����P�F�������\�������㎟�̕������\�������܂ŉ��t���[�������邩
//         �[����������ŏ������C�ɕ`�悷��
// �����Q�F�\��������F�i�f�t�H���g���S���j
//����������������������������������������������
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

//����������������������������������������������
// ������̈ʒu���Z�b�g����
// �����P�F�������W
// �����Q�F�������W
// ���������Z�b�g����O�Ɏg���Ă��������I
//����������������������������������������������
void CText::setPos(float x, float y)
{
	m_pos = XMFLOAT2(x, y);
	/*for (unsigned int i = 0; i < m_pText.size(); ++i)
	{
		m_pText[i]->setPos(m_pos.x + (m_textSize.x + m_letterSpacing.x) * i, m_pos.y);
	}*/
}

//����������������������������������������������
// ������̈ʒu���Z�b�g����
// �����P�F�V�������W
// ���������Z�b�g����O�Ɏg���Ă��������I
//����������������������������������������������
void CText::setPos(XMFLOAT2 _pos)
{
	m_pos = _pos;
}

void CText::setOffset(XMFLOAT2 _pos)
{
	m_pos.x += _pos.x;
	m_pos.y += _pos.y;
}