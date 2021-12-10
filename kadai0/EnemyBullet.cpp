//����������������������������������������������
// �t�@�C�����@�@�FEnemyBullet.cpp
// �T�v�@�@�@�@�@�F�v���C���[�̒e�̃N���X
// �쐬�ҁ@�@�@�@�F20CU0340 �ѐ�
// �X�V���e�@�@�@�F2021/11/07 �쐬
//����������������������������������������������
#include "EnemyBullet.h"
#include "Define.h"
#include "GameResource.h"
#include "CircleBoundingBox.h"

//����������������������������������������������
// �R���X�g���N�^
// �����P�F�Q�[���̏��
// �����Q�F�e�̏������W
// �����R�F�e�̏����ړ������i�p�x�j
//����������������������������������������������
EnemyBullet::EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle)
	: Super(_pGameInfo)
	, m_pBoundingBox(NULL)
{
	m_pImg = CreateSprite(Tex_EnemyBullet, ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y);
	m_pImg->setPos(_pos);
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));

	m_pBoundingBox = new CircleBoundingBox(_pos, ENEMY_BULLET_BOUNDING_BOX_RADIUS);
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
EnemyBullet::~EnemyBullet()
{
	DisposeSprite(m_pImg);
	delete m_pBoundingBox;
}


//����������������������������������������������
// �G�̒e�̉摜��`��
//����������������������������������������������
void EnemyBullet::renderSprite()
{
	if (m_pImg->getActive())
	{
		RenderSprite(m_pImg);
	}
}

//����������������������������������������������
// �G�̒e�̉摜�̈ʒu���Z�b�g����
//����������������������������������������������
void EnemyBullet::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos);
}

//����������������������������������������������
// �G�̒e�̉摜�摜���\���\��
//����������������������������������������������
bool EnemyBullet::GetActive()const
{
	return m_pImg->getActive();
}

//����������������������������������������������
// �G�̒e�̉摜��\���\�i�s�j�ɂ���
//����������������������������������������������
void EnemyBullet::SetActive(bool _b)
{
	return m_pImg->setActive(_b);
}

//����������������������������������������������
// �G�̒e�̈ړ��������Z�b�g����
// �����P�F�V�����ړ������i�p�x�j
//����������������������������������������������
void EnemyBullet::SetMoveDirection(float _angle)
{
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));
}

//����������������������������������������������
// �ړ��̏���
//����������������������������������������������
void EnemyBullet::MoveProcess(float _deltaTime)
{
	if (m_pImg->getActive())
	{
		m_pImg->offsetPos(XMFLOAT4(m_moveDirection.x * ENEMY_BULLET_MOVE_SPEED * _deltaTime, m_moveDirection.y * ENEMY_BULLET_MOVE_SPEED * _deltaTime, 0.f, 0.f));
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
// �����蔻��
//����������������������������������������������
BoundingBox* EnemyBullet::GetBoundingBox() const
{
	return m_pBoundingBox;
}

