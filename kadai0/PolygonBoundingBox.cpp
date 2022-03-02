//����������������������������������������������
// �t�@�C�����@�@�FPolygonBoundingBox.cpp
// �T�v�@�@�@�@�@�F���p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
//����������������������������������������������
#include "Define.h"
#include "CPicture.h"
#include "CircleBoundingBox.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"
#include <math.h>

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�o�E���f�B���O�{�b�N�X�̒��S���W
// �����Q�F�o�E���f�B���O�{�b�N�X�̒��_���W�̔z��i��{�͎��v��菇�j
// �@�@�@�F�� �v�f�͓�ȏ�
// �����R�F�o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
//����������������������������������������������
PolygonBoundingBox::PolygonBoundingBox(XMFLOAT2 _pos, vector<XMFLOAT2>& _vertexPos, bool _bRelativePosActive, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_pVertexPos(new vector<XMFLOAT2>(_vertexPos))
	, m_pVector(new vector<XMFLOAT2>())
	, m_relativePos(_relativePos)
	, m_bRelativePosActive(_bRelativePosActive)
	, Super(3)
{
	// ���_���W�̔z��̗v�f�����擾���Ă���
	int arraySize = (int)m_pVertexPos->size();

	// �v�f�����R�ȏ�
	if (arraySize >= 3)
	{
		XMFLOAT2 pos;			// i�Ԗڂ̍��W
		XMFLOAT2 pos1;			// i+1�Ԗڂ̍��W
		for (int i = 0; i < arraySize; ++i)
		{
			// ���񏈗�������W��ۑ����Ă���
			if (i < arraySize - 1)
			{
				if (i == 0)
				{
					pos = (*m_pVertexPos)[i];
					pos1 = (*m_pVertexPos)[int(i + 1)];
				}
				else
				{
					pos = pos1;
					pos1 = (*m_pVertexPos)[int(i + 1)];
				}
			}
			else
			{
				pos = pos1;
				pos1 = (*m_pVertexPos)[0];
			}

			// ���W�̍ő�l�ƍŏ��l�̌v�Z
			if (i == 0)
			{
				m_maxPos = pos;
				m_minPos = pos;
			}
			else
			{
				// X���W
				if		(pos.x > m_maxPos.x)m_maxPos.x = pos.x;
				else if (pos.x < m_minPos.x)m_minPos.x = pos.x;

				// Y���W
				if		(pos.y > m_maxPos.y)m_maxPos.y = pos.y;
				else if (pos.y < m_minPos.y)m_minPos.y = pos.y;
			}

			// �x�N�g�����v�Z
			XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

			// �P�ʉ�
			float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= distance;
			vector.y /= distance;

			// �ۑ�����
			m_pVector->push_back(vector);
		}
	}
	else if (arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		XMFLOAT2 pos1 = (*m_pVertexPos)[1];

		// ���W�̍ő�l�ƍŏ��l�̌v�Z
		{
			m_maxPos = pos;
			m_minPos = pos;
			// X���W
			if		(pos1.x > m_maxPos.x)m_maxPos.x = pos1.x;
			else if (pos1.x < m_minPos.x)m_minPos.x = pos1.x;
			// Y���W
			if		(pos1.y > m_maxPos.y)m_maxPos.y = pos1.y;
			else if (pos1.y < m_minPos.y)m_minPos.y = pos1.y;
		}

		// �x�N�g�����v�Z
		XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

		// �P�ʉ�
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= distance;
		vector.y /= distance;

		// �ۑ�����
		m_pVector->push_back(vector);
	}
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
PolygonBoundingBox::~PolygonBoundingBox()
{
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W���擾
//����������������������������������������������
XMFLOAT2 PolygonBoundingBox::GetPos()const
{
	return m_pos;
}

//����������������������������������������������
// ���_���W�̒���ԑ傫��X���W��Y���W���擾
//����������������������������������������������
XMFLOAT2 PolygonBoundingBox::GetMaxPos()const
{
	return m_maxPos;
}

//����������������������������������������������
// ���_���W�̒���ԏ�����X���W��Y���W���擾
//����������������������������������������������
XMFLOAT2 PolygonBoundingBox::GetMinPos()const
{
	return m_minPos;
}

//����������������������������������������������
// ���_���W�̔z����擾
//����������������������������������������������
vector<XMFLOAT2>* PolygonBoundingBox::GetVertexPos()const
{
	return m_pVertexPos.get();
}

//����������������������������������������������
// ���_���W���璸�_���W�̃x�N�g���̔z����擾
//����������������������������������������������
vector<XMFLOAT2>* PolygonBoundingBox::GetVector()const
{
	return m_pVector.get();
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W��ݒu����
// �����P�F���̃o�E���f�B���O�{�b�N�X�����I�u�W�F�N�g�̐V�������W
//����������������������������������������������
void PolygonBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̒��_���W���Z�b�g���Ȃ���
// �����P�F�V�������_���W�̔z��
//����������������������������������������������
void PolygonBoundingBox::ResetVertexPos(vector<XMFLOAT2>& _vertexPos)
{
	// ���_���W�̔z��̗v�f�����擾���Ă���
	int arraySize = (int)m_pVertexPos->size();

	// �v�f�����R�ȏ�
	if (arraySize >= 3)
	{
		m_pVertexPos->clear();
		m_pVector->clear();

		XMFLOAT2 pos;			// i�Ԗڂ̍��W
		XMFLOAT2 pos1;			// i+1�Ԗڂ̍��W
		for (int i = 0; i < arraySize; ++i)
		{
			// ���񏈗�������W��ۑ����Ă���
			if (i < arraySize - 1)
			{
				if (i == 0)
				{
					pos = (*m_pVertexPos)[i];
					pos1 = (*m_pVertexPos)[i + 1];
				}
				else
				{
					pos = pos1;
					pos1 = (*m_pVertexPos)[i + 1];
				}
			}
			else
			{
				pos = pos1;
				pos1 = (*m_pVertexPos)[0];
			}

			// ���W�̍ő�l�ƍŏ��l�̌v�Z
			if (i == 0)
			{
				m_maxPos = pos;
				m_minPos = pos;
			}
			else
			{
				// X���W
				if (pos.x > m_maxPos.x)m_maxPos.x = pos.x;
				else if (pos.x < m_minPos.x)m_minPos.x = pos.x;

				// Y���W
				if (pos.y > m_maxPos.y)m_maxPos.y = pos.y;
				else if (pos.y < m_minPos.y)m_minPos.y = pos.y;
			}

			// �x�N�g�����v�Z
			XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

			// �P�ʉ�
			float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= distance;
			vector.y /= distance;

			// �ۑ�����
			m_pVector->push_back(vector);
		}
	}
	else if (arraySize == 2)
	{
		m_pVertexPos->clear();
		m_pVector->clear();

		XMFLOAT2 pos = (*m_pVertexPos)[0];
		XMFLOAT2 pos1 = (*m_pVertexPos)[1];

		// ���W�̍ő�l�ƍŏ��l�̌v�Z
		{
			m_maxPos = pos;
			m_minPos = pos;
			// X���W
			if (pos1.x > m_maxPos.x)m_maxPos.x = pos1.x;
			else if (pos1.x < m_minPos.x)m_minPos.x = pos1.x;
			// Y���W
			if (pos1.y > m_maxPos.y)m_maxPos.y = pos1.y;
			else if (pos1.y < m_minPos.y)m_minPos.y = pos1.y;
		}

		// �x�N�g�����v�Z
		XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

		// �P�ʉ�
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= distance;
		vector.y /= distance;

		// �ۑ�����
		m_pVector->push_back(vector);
	}
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W�Ƃ�������I�u�W�F�N�g�̍��W�̍���ς���
// �����P�F�V���������i���j
//����������������������������������������������
void PolygonBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X����]����
// �����P�F��]����p�x
//����������������������������������������������
void PolygonBoundingBox::RotateVertex(float _angle)
{
	// ���_���W�̔z��̗v�f�����擾���Ă���
	int arraySize = (int)m_pVertexPos->size();

	if (arraySize < 2)return;

	float radian = DegreeToRadian(_angle);

	{
		XMFLOAT2 pos;
		for (int i = 0; i < arraySize; ++i)
		{
			pos = (*m_pVertexPos)[i];

			(*m_pVertexPos)[i].x = pos.x * cosf(radian) - pos.y * sinf(radian);
			(*m_pVertexPos)[i].y = pos.x * sinf(radian) + pos.y * cosf(radian);
		}

		XMFLOAT2 newRelativePos;
		if (m_bRelativePosActive)
		{
			newRelativePos =
			{
				m_relativePos.x * cosf(radian) - m_relativePos.y * sinf(radian),
				m_relativePos.x * sinf(radian) + m_relativePos.y * cosf(radian)
			};
			m_relativePos = newRelativePos;
		}
	}

	// �v�f�����R�ȏ�
	if (arraySize >= 3)
	{
		m_pVector->clear();
		XMFLOAT2 pos;			// i�Ԗڂ̍��W
		XMFLOAT2 pos1;			// i+1�Ԗڂ̍��W
		for (int i = 0; i < arraySize; ++i)
		{
			// ���񏈗�������W��ۑ����Ă���
			if (i < arraySize - 1)
			{
				if (i == 0)
				{
					pos = (*m_pVertexPos)[i];
					pos1 = (*m_pVertexPos)[i + 1];
				}
				else
				{
					pos = pos1;
					pos1 = (*m_pVertexPos)[i + 1];
				}
			}
			else
			{
				pos = pos1;
				pos1 = (*m_pVertexPos)[0];
			}

			// ���W�̍ő�l�ƍŏ��l�̌v�Z
			if (i == 0)
			{
				m_maxPos = pos;
				m_minPos = pos;
			}
			else
			{
				// X���W
				if (pos.x > m_maxPos.x)m_maxPos.x = pos.x;
				else if (pos.x < m_minPos.x)m_minPos.x = pos.x;

				// Y���W
				if (pos.y > m_maxPos.y)m_maxPos.y = pos.y;
				else if (pos.y < m_minPos.y)m_minPos.y = pos.y;
			}

			// �x�N�g�����v�Z
			XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

			// �P�ʉ�
			float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= distance;
			vector.y /= distance;

			// �ۑ�����
			m_pVector->push_back(vector);
		}
	}
	else if (arraySize == 2)
	{
		m_pVector->clear();
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		XMFLOAT2 pos1 = (*m_pVertexPos)[1];

		// ���W�̍ő�l�ƍŏ��l�̌v�Z
		{
			m_maxPos = pos;
			m_minPos = pos;
			// X���W
			if (pos1.x > m_maxPos.x)m_maxPos.x = pos1.x;
			else if (pos1.x < m_minPos.x)m_minPos.x = pos1.x;
			// Y���W
			if (pos1.y > m_maxPos.y)m_maxPos.y = pos1.y;
			else if (pos1.y < m_minPos.y)m_minPos.y = pos1.y;
		}

		// �x�N�g�����v�Z
		XMFLOAT2 vector = { pos1.x - pos.x, pos1.y - pos.y };

		// ���K��
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= distance;
		vector.y /= distance;

		// �ۑ�����
		m_pVector->push_back(vector);
	}
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�����E���]�ɂ���
//����������������������������������������������
void PolygonBoundingBox::FlipHorizontal()
{
	if (m_bRelativePosActive)
	{
		m_pos.x -= m_relativePos.x * 2.f;
		m_relativePos.x = -m_relativePos.x;
	}

	float temp = m_maxPos.x;
	m_maxPos.x = -m_minPos.x;
	m_minPos.x = -temp;

	int arraySize = (int)m_pVertexPos->size();
	for (int i = 0; i < arraySize; ++i)
	{
		(*m_pVertexPos)[i].x = -(*m_pVertexPos)[i].x;
	}
	// ���ёւ�
	shared_ptr<vector<XMFLOAT2>> vertexPos(new vector<XMFLOAT2>);
	vertexPos->push_back((*m_pVertexPos)[0]);
	for (int i = 1; i < arraySize; ++i)
	{
		vertexPos->push_back((*m_pVertexPos)[arraySize - i]);
	}
	m_pVertexPos = vertexPos;

	// ���ёւ�
	shared_ptr<vector<XMFLOAT2>> vector(new vector<XMFLOAT2>);
	vector->push_back((*m_pVector)[0]);
	vector->back().y = -vector->back().y;
	for (int i = 1; i < arraySize; ++i)
	{
		vector->push_back((*m_pVector)[arraySize - i]);
		// �t�����ɂ���
		vector->back().y = -vector->back().y;
	}
	m_pVector = vector;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X���㉺���]�ɂ���
//����������������������������������������������
void PolygonBoundingBox::FlipVertical()
{
	if (m_bRelativePosActive)
	{
		m_pos.y -= m_relativePos.y * 2.f;
		m_relativePos.x = -m_relativePos.x;
	}

	float temp = m_maxPos.y;
	m_maxPos.y = -m_minPos.y;
	m_minPos.y = -temp;

	int arraySize = (int)m_pVertexPos->size();
	for (int i = 0; i < arraySize; ++i)
	{
		(*m_pVertexPos)[i].y = -(*m_pVertexPos)[i].y;
	}
	// ���ёւ�
	shared_ptr<vector<XMFLOAT2>> vertexPos(new vector<XMFLOAT2>);
	vertexPos->push_back((*m_pVertexPos)[0]);
	for (int i = 1; i < arraySize; ++i)
	{
		vertexPos->push_back((*m_pVertexPos)[arraySize - i]);
	}
	m_pVertexPos = vertexPos;

	// ���ёւ�
	shared_ptr<vector<XMFLOAT2>> vector(new vector<XMFLOAT2>);
	vector->push_back((*m_pVector)[0]);
	vector->back().x = -vector->back().x;
	for (int i = 1; i < arraySize; ++i)
	{
		vector->push_back((*m_pVector)[arraySize - i]);
		// �t�����ɂ���
		vector->back().x = -vector->back().x;
	}
	m_pVector = vector;
}

//����������������������������������������������
// ���o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
//����������������������������������������������
bool PolygonBoundingBox::Collision(const BoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	if (_target->m_boundingBoxType == 1)
	{
		return Collision((CircleBoundingBox*)_target, _pDirectionVector);
	}
	else if (_target->m_boundingBoxType == 2)
	{
		return Collision((RectangleBoundingBox*)_target, _pDirectionVector);
	}
	else if (_target->m_boundingBoxType == 3)
	{
		return Collision((PolygonBoundingBox*)_target, _pDirectionVector);
	}
	return false;
}

//����������������������������������������������
// �摜�Ƃ̓����蔻��
// �����P�F�Ώۂ̉摜
//����������������������������������������������
bool PolygonBoundingBox::Collision(CPicture* _target, XMFLOAT2* _pDirectionVector)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	/*if (m_pos.x + m_minPos.x > targetPos.x + targetSize.x / 2.f)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetSize.x / 2.f)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetSize.y / 2.f)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetSize.y / 2.f)return false;*/

	// �摜�̎l���_���v�Z����
	XMFLOAT2 vertex[4] = { XMFLOAT2(targetPos.x, targetPos.y) };
	{
		vertex[0].x += targetSize.x / 2.f;
		vertex[1].x += targetSize.x / 2.f;
		vertex[2].x -= targetSize.x / 2.f;
		vertex[3].x -= targetSize.x / 2.f;
		vertex[0].y += targetSize.y / 2.f;
		vertex[1].y -= targetSize.y / 2.f;
		vertex[2].y -= targetSize.y / 2.f;
		vertex[3].y += targetSize.y / 2.f;
	}

	int arraySize = (int)m_pVertexPos->size();
	if (arraySize >= 3)
	{
		{
			XMFLOAT2 vector;
			XMFLOAT2 pos;
			for (int i = 0; i < arraySize; ++i)
			{
				// ���v�Z���钸�_�̍��W��ۑ����Ă���
				pos = (*m_pVertexPos)[i];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				for (int j = 0; j < 4; ++j)
				{
					// �v�Z�p�̃x�N�g��
					vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

					// ���K��
					float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
					vector.x /= r;
					vector.y /= r;

					// �O��
					float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

					// �E�ɂ���ꍇ�͂���ȏ����Ă��Ӗ��Ȃ�����break
					if (z < 0.f)
					{
						break;
					}

					// �Ō�܂őS�����ɂ����false��return
					if (j == 3)
					{
						return false;
					}
				}
			}
		}

		// �����܂ł���Ă����ʂ��o�Ȃ��ꍇ
		// �^�[�Q�b�g���������x���

		// �摜�̒P�ʃx�N�g��
		XMFLOAT2 vector[4] = { {0.f, 0.f} };	
		vector[0].y = -1;
		vector[1].x = -1;
		vector[2].y = 1;
		vector[3].x = 1;

		// ���_���W
		XMFLOAT2 pos;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < arraySize; ++j)
			{
				// ����钸�_�̍��W��ۑ����Ă���
				pos = (*m_pVertexPos)[j];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				// �v�Z�p�̃x�N�g��
				XMFLOAT2 vector2 = { pos.x - vertex[i].x , pos.y - vertex[i].y };

				// ���K��
				float r = sqrtf(vector2.x * vector2.x + vector2.y * vector2.y);
				vector2.x /= r;
				vector2.y /= r;

				// �O��
				float z = vector[i].x * vector2.y - vector[i].y * vector2.x;

				// �E�ɂ���ꍇ�͂���ȏ����Ă��Ӗ��Ȃ�����break
				if (z < 0.f)
				{
					break;
				}

				// �Ō�܂őS�����ɂ����false��return
				if (j == arraySize - 1)
				{
					return false;
				}
			}
		}
		return true;
	}
	else if(arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		pos.x += m_pos.x;
		pos.y += m_pos.y;

		XMFLOAT2 vector;
		for (int j = 0; j < 4; ++j)
		{
			// �v�Z�p�̃x�N�g��
			vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

			// ���K��
			float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= r;
			vector.y /= r;

			// �O��
			float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

			// �E�ɂ���ꍇ��true
			if (z < 0.f)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

bool PolygonBoundingBox::CollisionWithCircle(const CircleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	float targetRadius = _target->GetRadius();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x + m_minPos.x > targetPos.x + targetRadius)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetRadius)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetRadius)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetRadius)return false;

	// ���_�����擾
	int arraySize = (int)m_pVertexPos->size();

	// ���_�����R�ȏ�i�}�`�j
	if (arraySize >= 3)
	{
		// �v�Z�p�̕ϐ�
		XMFLOAT2 targetVector;
		XMFLOAT2 pos;
		int cnt = 0;

		// �~�̒��S�_���ǂ̐��̍��ɂ��邩�𒲂ׂ�
		for (int i = 0; i < arraySize; ++i)
		{
			// ���ݏ������̒��_�̍��W���擾���Ă���
			pos = (*m_pVertexPos)[i];
			pos.x += m_pos.x;
			pos.y += m_pos.y;

			// ���ݏ������̒��_����~�̒��S�܂ł̃x�N�g��
			targetVector = { targetPos.x - pos.x,targetPos.y - pos.y };

			// �x�N�g���̐��K��
			XMFLOAT2 vector = targetVector;
			float d = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= d;
			vector.y /= d;

			// �O��
			float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

			// �E��������A����ȏ����Ă��Ӗ��Ȃ�
			if (z < 0)
			{
				++cnt;
				continue;
			}
			// ����������
			// �������̒������v�Z
			float d2 = d * z;

			// ���������~�̔��a��蒷��
			if (d2 > targetRadius)
			{
				return false;
			}

			// ���̒��_�̍��W���擾���Ă���
			XMFLOAT2 pos2 = (*m_pVertexPos)[((i == arraySize - 1) ? (0) : (i + 1))];
			pos2.x += m_pos.x;
			pos2.y += m_pos.y;

			XMFLOAT2 pos1ToPos2Vector = { pos2.x - pos.x, pos2.y - pos.y };
			XMFLOAT2 targetVector2 = { targetPos.x - pos2.x, targetPos.y - pos2.y };

			float lengthOfline = sqrtf(pos1ToPos2Vector.x * pos1ToPos2Vector.x + pos1ToPos2Vector.y * pos1ToPos2Vector.y);
			float d3 = sqrtf(targetVector2.x * targetVector2.x + targetVector2.y * targetVector2.y);

			/*if (d > lengthOfline + targetRadius)
			{
				return false;
			}*/
			/*if (d3 > lengthOfline + targetRadius)
			{
				return false;
			}*/
			if (d < targetRadius)
			{
				throw i;
				return true;
			}
			if (d3 < targetRadius)
			{
				throw i + arraySize;
				return true;
			}

			XMFLOAT2 vector4 = (*m_pVector)[i];
			XMFLOAT2 newVector;
			newVector.x = vector4.x * cosf(DegreeToRadian(90.f)) - vector4.y * sinf(DegreeToRadian(90.f));
			newVector.y = vector4.x * sinf(DegreeToRadian(90.f)) + vector4.y * cosf(DegreeToRadian(90.f));
			
			// ���K��
			targetVector2.x /= d3;
			targetVector2.y /= d3;

			float z2 = newVector.x * vector.y - newVector.y * vector.x;
			float z3 = newVector.x * targetVector2.y - newVector.y * targetVector2.x;

			if (z2 < 0.f && z3 > 0.f)
			{
				return true;
			}
			++cnt;
			//��������������������������������������������������������������������������
			// d			�Fi�Ԗڂ̒��_����~�̒��S�܂ł̋���
			// d2			�F�~�̒��S�ɒʂ銎��i�Ԗڂ̒��_��i+1�Ԗڂ̒��_�̊Ԃ̐��𐂒�������̒���
			// d3			�Fi+1�Ԗڂ̒��_����~�̒��S�܂ł̋���
			// lengthOfline	�Fi�Ԗڂ̒��_��i+1�Ԗڂ̒��_�̊Ԃ̐��̒���
			//��������������������������������������������������������������������������
		}
		if (cnt >= arraySize)
		{
			throw -1;
			return true;
		}
		else
		{
			return false;
		}
	}
	// ���_�����Q�i���j
	else if (arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];

		// �^�[�Q�b�g�ւ̃x�N�g��
		XMFLOAT2 targetVector = { targetPos.x - pos.x,targetPos.y - pos.y };

		// �x�N�g���̐��K��
		XMFLOAT2 vector = targetVector;
		float d = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= d;
		vector.y /= d;

		// �O��
		float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

		// �E��������A����ȏ����Ă��Ӗ��Ȃ�
		if (z < 0)return true;

		// ����������
		// �������̒������v�Z
		float d2 = d * z;

		// ���������~�̔��a��蒷��
		if (d2 > targetRadius)return true;

		// ���̒��_�̍��W���擾���Ă���
		XMFLOAT2 pos2 = (*m_pVertexPos)[1];
		pos2.x += m_pos.x;
		pos2.y += m_pos.y;

		XMFLOAT2 pos1ToPos2Vector = { pos2.x - pos.x, pos2.y - pos.y };
		XMFLOAT2 pos2ToPos1Vector = { -pos1ToPos2Vector.x, -pos1ToPos2Vector.y };
		XMFLOAT2 targetVector2 = { targetPos.x - pos2.x, targetPos.y - pos2.y };

		float lengthOfline = sqrtf(pos1ToPos2Vector.x * pos1ToPos2Vector.x + pos1ToPos2Vector.y * pos1ToPos2Vector.y);
		float d3 = sqrtf(targetVector2.x * targetVector2.x + targetVector2.y * targetVector2.y);

		if (d > lengthOfline + targetRadius)
		{
			return false;
		}
		if (d3 > lengthOfline + targetRadius)
		{
			return false;
		}

		if (d < targetRadius)
		{
			return true;
		}

		if (d3 < targetRadius)
		{
			return true;
		}
	}
	return false;
}

//����������������������������������������������
// �ۂ��o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̊ۂ��o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool PolygonBoundingBox::Collision(const CircleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	try
	{
		if (!CollisionWithCircle(_target))return false;
	}
	catch (int index)
	{
		if (!_pDirectionVector)return true;

		if (!((_pDirectionVector->y < 0.f && _target->GetPos().y < m_pos.y) ||
			(_pDirectionVector->y > 0.f && _target->GetPos().y > m_pos.y)))
			if (!((_pDirectionVector->x < 0.f && _target->GetPos().x < m_pos.x) ||
				(_pDirectionVector->x > 0.f && _target->GetPos().x > m_pos.x)))return true;

		if (index != -1)
		{
			int arraySize = (int)m_pVertexPos->size();
			if (index < arraySize)
			{
				// �x�N�g��������Ă���
				XMFLOAT2 vector = (*m_pVector)[index];

				// �x�N�g������]���A�ۑ����Ă���
				XMFLOAT2 newVector;
				newVector.x = vector.x * cosf(DegreeToRadian(-90.f)) - vector.y * sinf(DegreeToRadian(-90.f));
				newVector.y = vector.x * sinf(DegreeToRadian(-90.f)) + vector.y * cosf(DegreeToRadian(-90.f));

				// ���̕����x�N�g���̑傫����ۑ����Ă���
				float m = FindDistanceByCoordinateDifference(*_pDirectionVector);

				// ���̕����x�N�g���̒P�ʃx�N�g��
				XMFLOAT2 directionVector = *_pDirectionVector;
				directionVector.x /= m;
				directionVector.y /= m;

				float cosAngle = -directionVector.x * newVector.x + -directionVector.y * newVector.y;

				// ���̕����x�N�g����newVector��̓��e
				XMFLOAT2 vector2 = newVector;
				vector2.x *= cosAngle;
				vector2.y *= cosAngle;

				XMFLOAT2 newDirectionVector = directionVector;

				newDirectionVector.x = newDirectionVector.x + vector2.x * 2.f * m;
				newDirectionVector.y = newDirectionVector.y + vector2.y * 2.f * m;

				*_pDirectionVector = newDirectionVector;
			}
			else
			{
				index -= arraySize;

				// �x�N�g��������Ă���
				XMFLOAT2 vector = (*m_pVector)[index];

				// �x�N�g������]���A�ۑ����Ă���
				XMFLOAT2 newVector;
				newVector.x = vector.x * cosf(DegreeToRadian(-90.f)) - vector.y * sinf(DegreeToRadian(-90.f));
				newVector.y = vector.x * sinf(DegreeToRadian(-90.f)) + vector.y * cosf(DegreeToRadian(-90.f));

				// ���̕����x�N�g���̑傫����ۑ����Ă���
				float m = FindDistanceByCoordinateDifference(*_pDirectionVector);

				// ���̕����x�N�g���̒P�ʃx�N�g��
				XMFLOAT2 directionVector = *_pDirectionVector;
				directionVector.x /= m;
				directionVector.y /= m;

				float cosAngle = -directionVector.x * newVector.x + -directionVector.y * newVector.y;

				// ���̕����x�N�g����newVector��̓��e
				XMFLOAT2 vector2 = newVector;
				vector2.x *= cosAngle;
				vector2.y *= cosAngle;

				XMFLOAT2 newDirectionVector = directionVector;

				newDirectionVector.x = newDirectionVector.x + vector2.x * 2.f * m;
				newDirectionVector.y = newDirectionVector.y + vector2.y * 2.f * m;

				*_pDirectionVector = newDirectionVector;
			}
		}
		else
		{

		}
	}
	return true;
}


bool PolygonBoundingBox::CollisionWithRectangle(const RectangleBoundingBox* _target, vector<int>& hitLine)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	/*if (m_pos.x + m_minPos.x > targetPos.x + targetSize.x / 2.f)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetSize.x / 2.f)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetSize.y / 2.f)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetSize.y / 2.f)return false;*/

	// �^�[�Q�b�g�̎l���_���v�Z����
	XMFLOAT2 vertex[4] = { targetPos, targetPos, targetPos, targetPos };
	{
		vertex[0].x += targetSize.x / 2.f;
		vertex[1].x += targetSize.x / 2.f;
		vertex[2].x -= targetSize.x / 2.f;
		vertex[3].x -= targetSize.x / 2.f;
		vertex[0].y += targetSize.y / 2.f;
		vertex[1].y -= targetSize.y / 2.f;
		vertex[2].y -= targetSize.y / 2.f;
		vertex[3].y += targetSize.y / 2.f;
	}

	int arraySize = (int)m_pVertexPos->size();
	if (arraySize >= 3)
	{
		{
			XMFLOAT2 vector;
			XMFLOAT2 pos;
			for (int i = 0; i < arraySize; ++i)
			{
				// ���v�Z���钸�_�̍��W��ۑ����Ă���
				pos = (*m_pVertexPos)[i];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				int cnt = 0;

				for (int j = 0; j < 4; ++j)
				{
					// �v�Z�p�̃x�N�g��
					vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

					// ���K��
					float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
					vector.x /= r;
					vector.y /= r;

					// �O��
					float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

					// �E�ɂ���ꍇ�͂���ȏ����Ă��Ӗ��Ȃ�����break
					if (z < 0.f)
					{
						break;
					}

					// �Ō�܂őS�����ɂ����false��return
					if (j == 3)
					{
						return false;
					}
				}
			}
		}

		// �����܂ł���Ă����ʂ��o�Ȃ��ꍇ
		// �^�[�Q�b�g���������x���

		// �^�[�Q�b�g�̒P�ʃx�N�g��
		XMFLOAT2 vector[4] = { {0.f, 0.f} };
		vector[0].y = -1;
		vector[1].x = -1;
		vector[2].y = 1;
		vector[3].x = 1;

		// ���_���W
		XMFLOAT2 pos;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < arraySize; ++j)
			{
				// ����钸�_�̍��W��ۑ����Ă���
				pos = (*m_pVertexPos)[j];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				// �v�Z�p�̃x�N�g��
				XMFLOAT2 vector2 = { pos.x - vertex[i].x , pos.y - vertex[i].y };

				// ���K��
				float r = sqrtf(vector2.x * vector2.x + vector2.y * vector2.y);
				vector2.x /= r;
				vector2.y /= r;

				// �O��
				float z = vector[i].x * vector2.y - vector[i].y * vector2.x;

				// �E�ɂ���ꍇ�͂���ȏ����Ă��Ӗ��Ȃ�����break
				if (z < 0.f)
				{
					break;
				}

				// �Ō�܂őS�����ɂ����false��return
				if (j == arraySize - 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	else if (arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		pos.x += m_pos.x;
		pos.y += m_pos.y;

		XMFLOAT2 vector;
		for (int j = 0; j < 4; ++j)
		{
			// �v�Z�p�̃x�N�g��
			vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

			// ���K��
			float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= r;
			vector.y /= r;

			// �O��
			float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

			// �E�ɂ���ꍇ��true
			if (z < 0.f)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

//����������������������������������������������
// �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̎l�p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool PolygonBoundingBox::Collision(const RectangleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	vector<int> hitLine;

	if (!CollisionWithRectangle(_target, hitLine))return false;

	if (!_pDirectionVector)return true;

	if (((_pDirectionVector->y < 0.f && _target->GetPos().y > m_pos.y) ||
		(_pDirectionVector->y > 0.f && _target->GetPos().y < m_pos.y)))return true;

	if (((_pDirectionVector->x < 0.f && _target->GetPos().x > m_pos.x) ||
		(_pDirectionVector->x > 0.f && _target->GetPos().x < m_pos.x)))return true;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//! �ꎞ�I�Ɏg������
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	XMFLOAT2 d = _target->GetPos();
	d.x -= m_pos.x;
	d.y -= m_pos.y;
	if (Abs(d.x) > Abs(d.y))
	{
		_pDirectionVector->x = -_pDirectionVector->x;
	}
	else
	{
		_pDirectionVector->y = -_pDirectionVector->y;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/*int hitLineNum = (int)hitLine.size();

	if (hitLineNum % 2 == 1)
	{
		XMFLOAT2 vector = (*m_pVector)[hitLine[(hitLineNum - 1) / 2]];

		XMFLOAT2 newVector;
		newVector.x = vector.x * cosf(DegreeToRadian(90.f)) - vector.y * sinf(DegreeToRadian(90.f));
		newVector.y = vector.x * sinf(DegreeToRadian(90.f)) + vector.y * cosf(DegreeToRadian(90.f));

		// ���̕����x�N�g���̑傫����ۑ����Ă���
		float m = FindDistanceByCoordinateDifference(*_pDirectionVector);

		// ���̕����x�N�g���̒P�ʃx�N�g��
		XMFLOAT2 directionVector = *_pDirectionVector;
		directionVector.x /= m;
		directionVector.y /= m;

		float cosAngle = -directionVector.x * newVector.x + -directionVector.y * newVector.y;

		// ���̕����x�N�g����newVector��̓��e
		XMFLOAT2 vector2 = newVector;
		vector2.x *= cosAngle;
		vector2.y *= cosAngle;

		XMFLOAT2 newDirectionVector = directionVector;

		newDirectionVector.x = newDirectionVector.x + vector2.x * 2.f * m;
		newDirectionVector.y = newDirectionVector.y + vector2.y * 2.f * m;

		*_pDirectionVector = newDirectionVector;
	}
	else if (hitLineNum != 0)
	{

	}*/

	return true;
}

//����������������������������������������������
// ���p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̑��p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool PolygonBoundingBox::Collision(const PolygonBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetMaxPos = _target->GetMaxPos();
	XMFLOAT2 targetMinPos = _target->GetMinPos();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	/*if (m_pos.x + m_minPos.x > targetPos.x + targetMaxPos.x)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x + targetMinPos.x)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetMaxPos.y)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y + targetMaxPos.y)return false;*/

	// �^�[�Q�b�g�̒��_�����擾���A���_���W���v�Z����
	vector<XMFLOAT2> targetVertex = *(_target->GetVertexPos());
	int targetArraySize = (int)targetVertex.size();
	for (int i = 0; targetArraySize; ++i)
	{
		targetVertex[i].x += targetPos.x;
		targetVertex[i].y += targetPos.y;
	}
	
	// �����̒��_�����擾����
	int arraySize = (int)m_pVertexPos->size();

	// ���_���R�ȏゾ������i�}�`�j
	if (arraySize >= 3)
	{
		{
			XMFLOAT2 vector;
			XMFLOAT2 pos;
			for (int i = 0; i < arraySize; ++i)
			{
				// ���v�Z���钸�_�̍��W��ۑ����Ă���
				pos = (*m_pVertexPos)[i];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				for (int j = 0; j < targetArraySize; ++j)
				{
					// �v�Z�p�̃x�N�g��
					vector = { targetVertex[j].x - pos.x, targetVertex[j].y - pos.y };

					// ���K��
					float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
					vector.x /= r;
					vector.y /= r;

					// �O��
					float z = (*m_pVector)[i].x * vector.y - (*m_pVector)[i].y * vector.x;

					// �E�ɂ���ꍇ�͂���ȏ����Ă��Ӗ��Ȃ�����break
					if (z < 0.f)
					{
						break;
					}

					// �Ō�܂őS�����ɂ����false��return
					if (j == targetArraySize - 1)
					{
						return false;
					}
				}
			}
		}

		// �����܂ł���Ă����ʂ��o�Ȃ��ꍇ
		// �^�[�Q�b�g���������x���

		// �^�[�Q�b�g�̃x�N�g��
		vector<XMFLOAT2> targetVector = *(_target->GetVector());

		// ���_���W
		XMFLOAT2 pos;
		for (int i = 0; i < targetArraySize; ++i)
		{
			for (int j = 0; j < arraySize; ++j)
			{
				// ����钸�_�̍��W��ۑ����Ă���
				pos = (*m_pVertexPos)[j];
				pos.x += m_pos.x;
				pos.y += m_pos.y;

				// �v�Z�p�̃x�N�g��
				XMFLOAT2 vector2 = { pos.x - targetVertex[i].x , pos.y - targetVertex[i].y };

				// ���K��
				float r = sqrtf(vector2.x * vector2.x + vector2.y * vector2.y);
				vector2.x /= r;
				vector2.y /= r;

				// �O��
				float z = targetVector[i].x * vector2.y - targetVector[i].y * vector2.x;

				// �E�ɂ���ꍇ�͂���ȏ����Ă��Ӗ��Ȃ�����break
				if (z < 0.f)
				{
					break;
				}

				// �Ō�܂őS�����ɂ����false��return
				if (j == arraySize - 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	// ���_�����Q��������i���j
	else if (arraySize == 2)
	{
		XMFLOAT2 pos = (*m_pVertexPos)[0];
		pos.x += m_pos.x;
		pos.y += m_pos.y;

		XMFLOAT2 vector;
		for (int j = 0; j < 4; ++j)
		{
			// �v�Z�p�̃x�N�g��
			vector = { targetVertex[j].x - pos.x, targetVertex[j].y - pos.y };

			// ���K��
			float r = sqrtf(vector.x * vector.x + vector.y * vector.y);
			vector.x /= r;
			vector.y /= r;

			// �O��
			float z = (*m_pVector)[0].x * vector.y - (*m_pVector)[0].y * vector.x;

			// �E�ɂ���ꍇ��true
			if (z < 0.f)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}