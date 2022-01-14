//����������������������������������������������
// �t�@�C�����@�@�FBullet.cpp
// �T�v�@�@�@�@�@�F�v���C���[�̒e�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/11/20 �쐬
//����������������������������������������������
#include "Bullet.h"
#include "Define.h"
#include "GameResource.h"
#include "CircleBoundingBox.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�e�̏������W
// �����R�F�e�̏����ړ������i�p�x�j
//����������������������������������������������
Bullet::Bullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Super(_pGameInfo)
	, m_pBoundingBox(NULL)
{
	if (!m_pImg)
	{
		m_pImg = CreateSprite(Tex_Bullet, BULLET_SIZE_X, BULLET_SIZE_Y);
		m_pImg->setPos(_pos);
	}
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));

	if(!m_pBoundingBox)m_pBoundingBox = new CircleBoundingBox(_pos, BULLET_BOUNDING_BOX_RADIUS);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
Bullet::~Bullet()
{
	DisposeSprite(m_pImg);
	delete m_pBoundingBox;
}

//����������������������������������������������
// �e�̉摜���擾
//����������������������������������������������
CPicture* Bullet::GetImg()const
{
	return m_pImg;
}

BoundingBox* Bullet::GetBoundingBox()const
{
	return m_pBoundingBox;
}

//����������������������������������������������
// �e�̉摜��`��
//����������������������������������������������
void Bullet::renderSprite()
{
	if (m_pImg->getActive())
	{
		RenderSprite(m_pImg);
	}
}

//����������������������������������������������
// �e�̉摜�̈ʒu���Z�b�g����
//����������������������������������������������
void Bullet::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos);
}

//����������������������������������������������
// �e�̉摜�摜���\���\��
//����������������������������������������������
bool Bullet::GetActive()const
{
	return m_pImg->getActive();
}

//����������������������������������������������
// �e�̉摜��\���\�i�s�j�ɂ���
//����������������������������������������������
void Bullet::SetActive(bool _b)
{
	return m_pImg->setActive(_b);
}

//����������������������������������������������
// �e�̈ړ��������Z�b�g����
// �����P�F�V�����ړ������i�p�x�j
//����������������������������������������������
void Bullet::SetMoveDirection(float _angle)
{
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));
}

//����������������������������������������������
// �ړ��̏���
//����������������������������������������������
void Bullet::MoveProcess(float _deltaTime)
{
	if (m_pImg->getActive())
	{
		m_pImg->offsetPos(XMFLOAT4(m_moveDirection.x * BULLET_MOVE_SPEED * _deltaTime, m_moveDirection.y * BULLET_MOVE_SPEED * _deltaTime, 0.f, 0.f));
		XMFLOAT2 newPos = { m_pImg->getPos().x, m_pImg->getPos().y };
		m_pBoundingBox->SetPos(newPos);
		XMFLOAT3 cameraPos = m_pGameInfo->pCamera->get()->getPos();
		
		if (newPos.x > cameraPos.x + 1000.f ||
			newPos.x < cameraPos.x - 1000.f ||
			newPos.y > cameraPos.y + 600.f ||
			newPos.y < cameraPos.y - 600.f)
		{
			m_pImg->setActive(false);
		}
	}
}

//����������������������������������������������
// �e�̓����蔻��i�G�Ƃ́j
// �����P�F�G�̔z��̃A�h���X
//����������������������������������������������
bool Bullet::Collision(vector<shared_ptr<Enemy>>* _target)
{
	return false;
}

//����������������������������������������������
// �e�̓����蔻��i��Q���Ƃ́j
// �����P�F��Q���̔z��̃A�h���X
//����������������������������������������������
bool Bullet::Collision(vector<shared_ptr<SceneryObject>>* _target)
{
	return false;
}