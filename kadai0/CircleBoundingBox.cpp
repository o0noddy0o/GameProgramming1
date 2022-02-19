//����������������������������������������������
// �t�@�C�����@�@�FCircleBoundingBox.cpp
// �T�v�@�@�@�@�@�F�ۂ��o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
// �@�@�@�@�@�@�@�F2022/02/17 �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻����C��
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
// �����Q�F�o�E���f�B���O�{�b�N�X�̔��a
// �����R�F�o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
//����������������������������������������������
CircleBoundingBox::CircleBoundingBox(XMFLOAT2 _pos, float _radius, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_radius(_radius)
	, m_relativePos(_relativePos)
	, Super(1)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
CircleBoundingBox::~CircleBoundingBox()
{
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̒��S���W���擾����
//����������������������������������������������
XMFLOAT2 CircleBoundingBox::GetPos()const
{
	return m_pos;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̔��a���擾����
//����������������������������������������������
float CircleBoundingBox::GetRadius()const
{
	return m_radius;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W��ݒu����
// �����P�F���̃o�E���f�B���O�{�b�N�X�����I�u�W�F�N�g�̐V�������W
//����������������������������������������������
void CircleBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̔��a��ς���
// �����P�F�V�������a
//����������������������������������������������
void CircleBoundingBox::ChangeRadius(float _newRadius)
{
	m_radius = _newRadius;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W�Ƃ�������I�u�W�F�N�g�̍��W�̍���ς���
// �����P�F�V���������i���j
//����������������������������������������������
void CircleBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//����������������������������������������������
// ���o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
//����������������������������������������������
bool CircleBoundingBox::Collision(const BoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	if (_target->m_boundingBoxType == 1)
	{
		return Collision((CircleBoundingBox*)_target, _pDirectionVector);
	}
	else if(_target->m_boundingBoxType == 2)
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
bool CircleBoundingBox::Collision(CPicture* _target, XMFLOAT2* _pDirectionVector)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + targetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < targetPos.x - targetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > targetPos.y + targetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < targetPos.y - targetSize.y / 2.f - m_radius)return false;

	// ���W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - targetPos.x, m_pos.y - targetPos.y };

	if (Abs(relativePos.x) <= targetSize.x / 2.f)return true;
	if (Abs(relativePos.y) <= targetSize.y / 2.f)return true;

	XMFLOAT2 pos = { Abs(relativePos.x) - targetSize.x / 2.f, Abs(relativePos.y) - targetSize.y };

	if (pos.x * pos.x + pos.y * pos.y <= m_radius * m_radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//����������������������������������������������
// �ۂ��o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̊ۂ��o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool CircleBoundingBox::Collision(const CircleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	// ��̍��W�̍����v�Z���Ă���
	XMFLOAT2 relativePos = { m_pos.x - _target->GetPos().x, m_pos.y - _target->GetPos().y };
	
	bool bResult = (sqrtf(relativePos.x * relativePos.x + relativePos.y * relativePos.y) <=
		(m_radius + _target->GetRadius()));

	if (_pDirectionVector && bResult)
	{
		XMFLOAT2 pos = _target->GetPos();
		pos.x -= m_pos.x;
		pos.y -= m_pos.y;

		if (!((_pDirectionVector->x < 0.f && pos.x < 0.f) ||
			(_pDirectionVector->x > 0.f && pos.x > 0.f)))
			if (!((_pDirectionVector->y < 0.f && pos.y < 0.f) ||
				(_pDirectionVector->y > 0.f && pos.y > 0.f)))
				return true;

		/*float targetRadius = _target->GetRadius();

		XMFLOAT2 point[2];

		float x = (1.f / ( 2.f * (pos.x * pos.x + pos.y * pos.y))) *
			(pos.x * pos.x * pos.x + sqrtf((-(pos.y * pos.y)) *
				(pos.x * pos.x * pos.x * pos.x + 2.f * pos.x * pos.x * m_radius * m_radius -
					2.f * pos.x * pos.x * targetRadius * targetRadius +
					pos.y * pos.y * pos.y * pos.y - 2.f * pos.y * pos.y * m_radius * m_radius -
					2.f * pos.y * pos.y * targetRadius * targetRadius +
					m_radius * m_radius * m_radius * m_radius - 2.f * m_radius * m_radius * targetRadius * targetRadius +
					targetRadius * targetRadius * targetRadius * targetRadius)) +
				pos.x * pos.y * pos.y + pos.x * m_radius * m_radius - pos.x * targetRadius * targetRadius);*/

		XMFLOAT2 vector = _target->GetPos();
		vector.x -= m_pos.x;
		vector.y -= m_pos.y;

		{
			float d = FindDistanceByCoordinateDifference(vector);
			vector.x /= d;
			vector.y /= d;
		}

		// ���̕����x�N�g���̑傫����ۑ����Ă���
		float m = FindDistanceByCoordinateDifference(*_pDirectionVector);

		// ���̕����x�N�g���̒P�ʃx�N�g��
		XMFLOAT2 directionVector = *_pDirectionVector;
		directionVector.x /= m;
		directionVector.y /= m;

		float cosAngle = -directionVector.x * vector.x + -directionVector.y * vector.y;

		// ���̕����x�N�g����newVector��̓��e
		XMFLOAT2 vector2 = vector;
		vector2.x *= cosAngle;
		vector2.y *= cosAngle;

		XMFLOAT2 newDirectionVector = directionVector;

		newDirectionVector.x = newDirectionVector.x + vector2.x * 2.f;
		newDirectionVector.y = newDirectionVector.y + vector2.y * 2.f;

		*_pDirectionVector = newDirectionVector;
	}

	return bResult;
}

bool CircleBoundingBox::CollisionWithRectangle(const RectangleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + targetSize.x / 2.f + m_radius)return false;
	if (m_pos.x < targetPos.x - targetSize.x / 2.f - m_radius)return false;
	if (m_pos.y > targetPos.y + targetSize.y / 2.f + m_radius)return false;
	if (m_pos.y < targetPos.y - targetSize.y / 2.f - m_radius)return false;

	if (Abs(m_pos.x - targetPos.x) < targetSize.x / 2.f &&
		Abs(m_pos.y - targetPos.y) < targetSize.y / 2.f)
		return true;

	if (Abs(targetPos.x - m_pos.x) < targetSize.x / 2.f)
	{
		if (Abs(targetPos.y - m_pos.y) < (targetSize.y / 2.f + m_radius))
		{
			throw 1;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (Abs(targetPos.y - m_pos.y) < targetSize.y / 2.f)
	{
		if (Abs(targetPos.x - m_pos.x) < (targetSize.x / 2.f + m_radius))
		{
			throw 2;
			return true;
		}
		else
		{
			return false;
		}
	}

	// �΂ߕ����ɂ���ꍇ
	XMFLOAT2 vertex;
	// �^�[�Q�b�g���E
	if (m_pos.x < targetPos.x)
	{
		// �^�[�Q�b�g����
		if (m_pos.y < targetPos.y)
		{
			vertex = { targetPos.x - targetSize.x / 2.f, targetPos.y - targetSize.y / 2.f };
		}
		// �^�[�Q�b�g����
		else
		{
			vertex = { targetPos.x - targetSize.x / 2.f, targetPos.y + targetSize.y / 2.f };
		}
	}
	// �^�[�Q�b�g����
	else
	{
		// �^�[�Q�b�g����
		if (m_pos.y < targetPos.y)
		{
			vertex = { targetPos.x + targetSize.x / 2.f, targetPos.y - targetSize.y / 2.f };
		}
		// �^�[�Q�b�g����
		else
		{
			vertex = { targetPos.x + targetSize.x / 2.f, targetPos.y + targetSize.y / 2.f };
		}
	}

	// ���_�ƃ^�[�Q�b�g�̍��W�̋������v�Z����
	XMFLOAT2 coordinateDifference = { m_pos.x - vertex.x, m_pos.y - vertex.y };
	float distance = FindDistanceByCoordinateDifference(coordinateDifference);

	// �������^�[�Q�b�g�̔��a���傫���ꍇ
	if (distance > m_radius)
	{
		return false;
	}
	// �����ł͂Ȃ��ꍇ
	else
	{
		throw 3;
		return true;
	}

	return false;
}

//����������������������������������������������
// �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̎l�p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool CircleBoundingBox::Collision(const RectangleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	try
	{
		// �������ĂȂ�������false��Ԃ�
		if (!CollisionWithRectangle(_target))return false;

		
	}
	// �������Ă��銎�ړ������̃|�C���^�[��NULL�ł͂Ȃ��ꍇ��
	// ����������̈ړ��������v�Z����
	catch (int num)
	{
		// �ړ��������Ȃ��ꍇ�͂��̂܂�true��Ԃ�
		if (!_pDirectionVector)return true;

		//������������������������������������
		// "num"�̐����F
		//������������������������������������
		// num ���P�̏ꍇ�F
		// �@�^�[�Q�b�g�������̏ォ�A���ɂ���
		// 
		// num ���Q�̏ꍇ�F
		// �@�^�[�Q�b�g�������̍����A�E�ɂ���
		// 
		// num ���R�̏ꍇ�F
		// �@�^�[�Q�b�g�������̎΂ߕ����ɂ���
		//������������������������������������
		switch (num)
		{
			case 1:
			{
				if ((_pDirectionVector->y < 0.f && _target->GetPos().y < m_pos.y) ||
					(_pDirectionVector->y > 0.f && _target->GetPos().y > m_pos.y))
				{
					_pDirectionVector->y = -_pDirectionVector->y;
				}
			}
			break;

		case 2:
			{
				if ((_pDirectionVector->x < 0.f && _target->GetPos().x < m_pos.x) ||
					(_pDirectionVector->x > 0.f && _target->GetPos().x > m_pos.x))
				{
					_pDirectionVector->x = -_pDirectionVector->x;
				}
			}
			break;

		case 3:
			{
				if (!((_pDirectionVector->y < 0.f && _target->GetPos().y < m_pos.y) ||
					(_pDirectionVector->y > 0.f && _target->GetPos().y > m_pos.y)))
					if (!((_pDirectionVector->x < 0.f && _target->GetPos().x < m_pos.x) ||
						(_pDirectionVector->x > 0.f && _target->GetPos().x > m_pos.x)))break;

				// �K�v�ȏ��𑵂���
				XMFLOAT2 targetRelativePos = _target->GetPos();
				targetRelativePos.x -= m_pos.x;
				targetRelativePos.y -= m_pos.y;

				bool up = targetRelativePos.y < 0.f;
				bool right = targetRelativePos.x < 0.f;

				targetRelativePos.x = Abs(targetRelativePos.x);
				targetRelativePos.y = Abs(targetRelativePos.y);

				XMFLOAT2 line = _target->GetSize();
				line.x /= 2.f;
				line.y /= 2.f;

				float x;
				float y;

				{
					float x1 = m_radius * m_radius - line.y * line.y - 2.f * line.y * targetRelativePos.y + targetRelativePos.y * targetRelativePos.y;
					x1 = Abs(x1);
					x = -sqrtf(x1) + targetRelativePos.x;
				}
				{
					float y1 = m_radius * m_radius - line.x * line.x - 2.f * line.x * targetRelativePos.x + targetRelativePos.x * targetRelativePos.x;
					y1 = Abs(y1);
					y = -sqrtf(y1) + targetRelativePos.y;
				}

				XMFLOAT2 point[2] = { { x, line.y }, { line.x, y} };
				if (!right)
				{
					point[0].x = -point[0].x;
					point[1].x = -point[1].x;
				}
				if (!up)
				{
					point[0].y = -point[0].y;
					point[1].y = -point[1].y;
				}

				// point[0]����point[1]�܂ł̃x�N�g�����v�Z����
				XMFLOAT2 vector = { point[1].x - point[0].x, point[1].y - point[0].y };

				// �P�ʉ�����
				float d = FindDistanceByCoordinateDifference(vector);
				vector.x /= d;
				vector.y /= d;

				// �x�N�g������]����
				XMFLOAT2 newVector;
				if (up)
				{
					if (right)
					{
						newVector.x = vector.x * cosf(DegreeToRadian(90.f)) - vector.y * sinf(DegreeToRadian(90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(90.f)) + vector.y * cosf(DegreeToRadian(90.f));
					}
					else
					{
						newVector.x = vector.x * cosf(DegreeToRadian(-90.f)) - vector.y * sinf(DegreeToRadian(-90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(-90.f)) + vector.y * cosf(DegreeToRadian(-90.f));
					}
				}
				else
				{
					if (right)
					{
						newVector.x = vector.x * cosf(DegreeToRadian(-90.f)) - vector.y * sinf(DegreeToRadian(-90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(-90.f)) + vector.y * cosf(DegreeToRadian(-90.f));
					}
					else
					{
						newVector.x = vector.x * cosf(DegreeToRadian(90.f)) - vector.y * sinf(DegreeToRadian(90.f));
						newVector.y = vector.x * sinf(DegreeToRadian(90.f)) + vector.y * cosf(DegreeToRadian(90.f));
					}
				}

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
			break;
		}
	}
	return true;
}

//����������������������������������������������
// ���p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̑��p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool CircleBoundingBox::Collision(const PolygonBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	//CircleBoundingBox ob(m_pos, m_radius, m_relativePos);

	return _target->Collision(this);
}