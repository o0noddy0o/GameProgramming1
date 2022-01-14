//����������������������������������������������
// �t�@�C�����@�@�FRectangleBoundingBox.cpp
// �T�v�@�@�@�@�@�F�l�p�`�o�E���f�B���O�{�b�N�X�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/26 �쐬
// �@�@�@�@�@�@�@�F2021/11/27 �R���W�����̎���
// �@�@�@�@�@�@�@�F2021/12/26 �ۂ��o�E���f�B���O�{�b�N�X�Ƃ̓����蔻����C��
// �@�@�@�@�@�@�@�F2021/12/26 �S���̃R���W�������\�b�h�ɓ�ڂ̈�����ǉ�
//����������������������������������������������
#include "Define.h"
#include "CPicture.h"
#include "CircleBoundingBox.h"
#include "RectangleBoundingBox.h"
#include "PolygonBoundingBox.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�o�E���f�B���O�{�b�N�X�̒��S���W
// �����Q�F�o�E���f�B���O�{�b�N�X�̃T�C�Y
// �����R�F�o�E���f�B���O�{�b�N�X�Ƃ���������Ă���I�u�W�F�N�g�̍��W�̍�
//����������������������������������������������
RectangleBoundingBox::RectangleBoundingBox(XMFLOAT2 _pos, XMFLOAT2 _size, XMFLOAT2 _relativePos)
	: m_pos(_pos)
	, m_size(_size)
	, m_relativePos(_relativePos)
	, Super(2)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
RectangleBoundingBox::~RectangleBoundingBox()
{
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W���擾
//����������������������������������������������
XMFLOAT2 RectangleBoundingBox::GetPos()const
{
	return m_pos;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̃T�C�Y���擾
//����������������������������������������������
XMFLOAT2 RectangleBoundingBox::GetSize()const
{
	return m_size;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W��ݒu����
// �����P�F���̃o�E���f�B���O�{�b�N�X�����I�u�W�F�N�g�̐V�������W
//����������������������������������������������
void RectangleBoundingBox::SetPos(XMFLOAT2 _pos)
{
	m_pos.x = _pos.x + m_relativePos.x;
	m_pos.y = _pos.y + m_relativePos.y;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̃T�C�Y��ς���
// �����P�F�V�������W
//����������������������������������������������
void RectangleBoundingBox::ChangeSize(XMFLOAT2 _newSize)
{
	m_size = _newSize;
}

//����������������������������������������������
// �o�E���f�B���O�{�b�N�X�̍��W�Ƃ�������I�u�W�F�N�g�̍��W�̍���ς���
// �����P�F�V���������i���j
//����������������������������������������������
void RectangleBoundingBox::SetRelativePos(XMFLOAT2 _newRelativePos)
{
	m_relativePos = _newRelativePos;
}

//����������������������������������������������
// ���o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
//����������������������������������������������
bool RectangleBoundingBox::Collision(const BoundingBox* _target, XMFLOAT2* _pDirectionVector)const
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
bool RectangleBoundingBox::Collision(CPicture* _target, XMFLOAT2* _pDirectionVector)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->getSize();
	XMFLOAT4 targetPos = _target->getPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	if (_pDirectionVector)
	{
		// �ڐG�ʂ��v�Z����
		XMFLOAT2 contactSurface;

		contactSurface.x = ((m_size.x + targetSize.x) - Abs((m_pos.x - m_size.x / 2.f) - (targetPos.x - targetSize.x / 2.f)) - Abs((m_pos.x + m_size.x / 2.f) - (targetPos.x + targetSize.x / 2.f))) / 2.f;
		contactSurface.y = ((m_size.y + targetSize.y) - Abs((m_pos.y - m_size.y / 2.f) - (targetPos.y - targetSize.y / 2.f)) - Abs((m_pos.y + m_size.y / 2.f) - (targetPos.y + targetSize.y / 2.f))) / 2.f;
	
		if (contactSurface.x > contactSurface.y)
		{
			_pDirectionVector->y = -_pDirectionVector->y;
		}
		else
		{
			_pDirectionVector->x = -_pDirectionVector->x;
		}
	}

	return true;
}

bool RectangleBoundingBox::CollisionWithCircle(const CircleBoundingBox* _target)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	float targetRadius = _target->GetRadius();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + m_size.x / 2.f + targetRadius)return false;
	if (m_pos.x < targetPos.x - m_size.x / 2.f - targetRadius)return false;
	if (m_pos.y > targetPos.y + m_size.y / 2.f + targetRadius)return false;
	if (m_pos.y < targetPos.y - m_size.y / 2.f - targetRadius)return false;

	// �^�[�Q�b�g�������̎΂߂̕�������Ȃ��ꍇ
	if (Abs(targetPos.x - m_pos.x) < m_size.x / 2.f)
	{
		if (Abs(targetPos.y - m_pos.y) < (m_size.y / 2.f + targetRadius))
		{
			throw 1;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (Abs(targetPos.y - m_pos.y) < m_size.y / 2.f)
	{
		if (Abs(targetPos.x - m_pos.x) < (m_size.x / 2.f + targetRadius))
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
			vertex = { m_pos.x + m_size.x / 2.f, m_pos.y + m_size.y / 2.f };
		}
		// �^�[�Q�b�g����
		else
		{
			vertex = { m_pos.x + m_size.x / 2.f, m_pos.y - m_size.y / 2.f };
		}
	}
	// �^�[�Q�b�g����
	else
	{
		// �^�[�Q�b�g����
		if (m_pos.y < targetPos.y)
		{
			vertex = { m_pos.x - m_size.x / 2.f, m_pos.y + m_size.y / 2.f };
		}
		// �^�[�Q�b�g����
		else
		{
			vertex = { m_pos.x - m_size.x / 2.f, m_pos.y - m_size.y / 2.f };
		}
	}

	// ���_�ƃ^�[�Q�b�g�̍��W�̋������v�Z����
	XMFLOAT2 coordinateDifference = { targetPos.x - vertex.x, targetPos.y - vertex.y };
	float distance = FindDistanceByCoordinateDifference(coordinateDifference);

	// �������^�[�Q�b�g�̔��a���傫���ꍇ
	if (distance > targetRadius)
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
// �ۂ��o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̊ۂ��o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool RectangleBoundingBox::Collision(const CircleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	try
	{
		// �������ĂȂ�������false��Ԃ�
		if (!CollisionWithCircle(_target))return false;

		// �ړ��������Ȃ��ꍇ�͂��̂܂�true��Ԃ�
		if (!_pDirectionVector)return true;
	}

	// �������Ă��銎�ړ������̃|�C���^�[��NULL�ł͂Ȃ��ꍇ��
	// ����������̈ړ��������v�Z����
	catch (int num)
	{
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

				bool up = targetRelativePos.y > 0.f;
				bool right = targetRelativePos.x > 0.f;

				targetRelativePos.x = Abs(targetRelativePos.x);
				targetRelativePos.y = Abs(targetRelativePos.y);

				float r = _target->GetRadius();

				XMFLOAT2 line = { m_size.x / 2.f, m_size.y / 2.f };

				float x;
				float y;

				{
					float x1 = r * r - line.y * line.y - 2.f * line.y * targetRelativePos.y + targetRelativePos.y * targetRelativePos.y;
					x1 = Abs(x1);
					x = -sqrtf(x1) + targetRelativePos.x;
				}
				{
					float y1 = r * r - line.x * line.x - 2.f * line.x * targetRelativePos.x + targetRelativePos.x * targetRelativePos.x;
					y1 = Abs(y1);
					y = -sqrtf(y1) + targetRelativePos.y;
				}

				XMFLOAT2 point[2] = {{ x, line.y }, { line.x, y}};
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
// �l�p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̎l�p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool RectangleBoundingBox::Collision(const RectangleBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	// �Ώۂ̍��W�ƃT�C�Y���擾���Ă���
	XMFLOAT2 targetSize = _target->GetSize();
	XMFLOAT2 targetPos = _target->GetPos();

	// ������Ȃ��ꏊ�ɂ�����A����false��return����
	if (m_pos.x > targetPos.x + (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.x < targetPos.x - (targetSize.x + m_size.x) / 2.f)return false;
	if (m_pos.y > targetPos.y + (targetSize.y + m_size.y) / 2.f)return false;
	if (m_pos.y < targetPos.y - (targetSize.y + m_size.y) / 2.f)return false;

	if (_pDirectionVector)
	{
		// �ڐG�ʂ��v�Z����
		XMFLOAT2 contactSurface;

		contactSurface.x = ((m_size.x + targetSize.x) - Abs((m_pos.x - m_size.x / 2.f) - (targetPos.x - targetSize.x / 2.f)) - Abs((m_pos.x + m_size.x / 2.f) - (targetPos.x + targetSize.x / 2.f))) / 2.f;
		contactSurface.y = ((m_size.y + targetSize.y) - Abs((m_pos.y - m_size.y / 2.f) - (targetPos.y - targetSize.y / 2.f)) - Abs((m_pos.y + m_size.y / 2.f) - (targetPos.y + targetSize.y / 2.f))) / 2.f;

		if (contactSurface.x > contactSurface.y)
		{
			if ((_pDirectionVector->y > 0.f && targetPos.y > m_pos.y) ||
				(_pDirectionVector->y < 0.f && targetPos.y < m_pos.y))
			{
				_pDirectionVector->y = -_pDirectionVector->y;
			}
			else if((_pDirectionVector->x > 0.f && targetPos.x > m_pos.x) ||
				(_pDirectionVector->x < 0.f && targetPos.x < m_pos.x))
			{
				_pDirectionVector->x = -_pDirectionVector->x;
			}
		}
		else
		{
			if ((_pDirectionVector->x > 0.f && targetPos.x > m_pos.x) ||
				(_pDirectionVector->x < 0.f && targetPos.x < m_pos.x))
			{
				_pDirectionVector->x = -_pDirectionVector->x;
			}
			else if((_pDirectionVector->y > 0.f && targetPos.y > m_pos.y) ||
				(_pDirectionVector->y < 0.f && targetPos.y < m_pos.y))
			{
				_pDirectionVector->y = -_pDirectionVector->y;
			}
		}
	}

	return true;
}

//����������������������������������������������
// ���p�`�o�E���f�B���O�{�b�N�X�Ƃ̓����蔻��
// �����P�F�Ώۂ̑��p�`�o�E���f�B���O�{�b�N�X
//����������������������������������������������
bool RectangleBoundingBox::Collision(const PolygonBoundingBox* _target, XMFLOAT2* _pDirectionVector)const
{
	RectangleBoundingBox ob(m_pos, m_size, m_relativePos);

	return _target->Collision(&ob);
}