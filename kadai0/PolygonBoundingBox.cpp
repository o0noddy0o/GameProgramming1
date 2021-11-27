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
PolygonBoundingBox::PolygonBoundingBox(XMFLOAT2 _pos, vector<XMFLOAT2>& _vertexPos, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_pVertexPos(new vector<XMFLOAT2>(_vertexPos))
	, m_pVector(new vector<XMFLOAT2>())
	, m_relativePos(_relativePos)
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

	float radian = DegreeToRadian(-_angle);

	{
		XMFLOAT2 newRelativePos;
		if (m_relativePos.x != 0.f && m_relativePos.y != 0.f)
		{
			newRelativePos =
			{
				m_relativePos.x * cosf(radian) - m_relativePos.y * sinf(radian),
				m_relativePos.x * sinf(radian) + m_relativePos.y * cosf(radian)
			};
		}

		XMFLOAT2 pos;
		for (int i = 0; i < arraySize; ++i)
		{
			pos = (*m_pVertexPos)[i];

			if (m_relativePos.x != 0.f && m_relativePos.y != 0.f)
			{
				pos.x += m_relativePos.x;
				pos.y += m_relativePos.y;
			}

			(*m_pVertexPos)[i].x = pos.x * cosf(radian) - pos.y * sinf(radian);
			(*m_pVertexPos)[i].y = pos.x * sinf(radian) + pos.y * cosf(radian);

			if (m_relativePos.x != 0.f && m_relativePos.y != 0.f)
			{
				pos.x -= newRelativePos.x;
				pos.y -= newRelativePos.y;
			}
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

		// �P�ʉ�
		float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
		vector.x /= distance;
		vector.y /= distance;

		// �ۑ�����
		m_pVector->push_back(vector);
	}
}

//����������������������������������������������
// �摜�Ƃ̓����蔻��
// �����P�F�Ώۂ̉摜
//����������������������������������������������
bool PolygonBoundingBox::Collision(CPicture* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x + m_minPos.x > targetPos.x + targetSize.x / 2.f)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetSize.x / 2.f)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetSize.y / 2.f)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetSize.y / 2.f)return false;

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

					// �W����
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

		// �摜�̕W�����x�N�g��
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

				// �W����
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

			// �W����
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
// �ۂ��o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̊ۂ��o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool PolygonBoundingBox::Collision(const CircleBoundingBox* _target)const
{
	return false;
}

//����������������������������������������������
// �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̎l�p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool PolygonBoundingBox::Collision(const RectangleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x + m_minPos.x > targetPos.x + targetSize.x / 2.f)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x - targetSize.x / 2.f)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetSize.y / 2.f)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y - targetSize.y / 2.f)return false;

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

				for (int j = 0; j < 4; ++j)
				{
					// �v�Z�p�̃x�N�g��
					vector = { vertex[j].x - pos.x, vertex[j].y - pos.y };

					// �W����
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

		// �^�[�Q�b�g�̕W�����x�N�g��
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

				// �W����
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

			// �W����
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
// ���p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̑��p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool PolygonBoundingBox::Collision(const PolygonBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetMaxPos = _target->GetMaxPos();
	XMFLOAT2 targetMinPos = _target->GetMinPos();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x + m_minPos.x > targetPos.x + targetMaxPos.x)return false;
	if (m_pos.x + m_maxPos.x < targetPos.x + targetMinPos.x)return false;
	if (m_pos.y + m_minPos.y > targetPos.y + targetMaxPos.y)return false;
	if (m_pos.y + m_maxPos.y < targetPos.y + targetMaxPos.y)return false;

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

					// �W����
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

				// �W����
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

			// �W����
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