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
EnemyBullet::EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, float _angle, TypeOfEnemyBullet _bulletType)
	: Super(_pGameInfo)
	, m_pBoundingBox(NULL)
	, m_bulletType(_bulletType)
	, m_pImg(NULL)
	, m_pEff(NULL)
	, m_effCnt(0)
{
	if (_bulletType == normal)
	{
		m_pImg = CreateSprite(Tex_EnemyBullet, ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y);
		m_pImg->setPos(_pos);
	}
	m_moveDirection = XMFLOAT2(AngleToDirectionVector(_angle));

	if(m_bulletType == normal || m_bulletType == thunderBullet)m_pBoundingBox = new CircleBoundingBox(_pos, ENEMY_BULLET_BOUNDING_BOX_RADIUS);
}
EnemyBullet::EnemyBullet(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _moveDirection, TypeOfEnemyBullet _bulletType)
	: Super(_pGameInfo)
	, m_pBoundingBox(NULL)
	, m_bulletType(_bulletType)
	, m_moveDirection(_moveDirection)
	, m_pImg(NULL)
	, m_pEff(NULL)
	, m_effCnt(0)
{
	if (_bulletType == normal)
	{
		m_pImg = CreateSprite(Tex_EnemyBullet, ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y);
		m_pImg->setPos(_pos);
	}

	if (m_bulletType == normal || m_bulletType == thunderBullet)m_pBoundingBox = new CircleBoundingBox(_pos, ENEMY_BULLET_BOUNDING_BOX_RADIUS);
}
EnemyBullet::EnemyBullet(GameInfo* _pGameInfo, TypeOfEnemyBullet _bulletType)
	: Super(_pGameInfo)
	, m_bulletType(_bulletType)
	, m_pImg(NULL)
	, m_pEff(NULL)
	, m_effCnt(0)
{
}

//����������������������������������������������
// �f�X�g���N�^
//����������������������������������������������
EnemyBullet::~EnemyBullet()
{
	if (m_pImg)DisposeSprite(m_pImg);
	if (m_pEff)DisposeSprite(m_pEff);
	delete m_pBoundingBox;
}

int EnemyBullet::GetBulletType()const
{
	return m_bulletType;
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
	if (m_pEff)
	{
		if (m_effCnt++ >= ENEMY_BULLET_EFFECT_SWITCH_CNT)
		{
			m_pEff->stepAnimation();
			m_effCnt = 0;
			++m_effAnimIndex;
			if (m_effAnimIndex > 5)
			{
				m_pEff->setActive(false);
			}
		}
		RenderSprite(m_pEff);
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
	return (m_pImg->getActive() || ((m_pEff) ? (m_pEff->getActive()) : (false)));
}

//����������������������������������������������
// �G�̒e�̉摜��\���\�i�s�j�ɂ���
//����������������������������������������������
void EnemyBullet::SetActive(bool _b)
{
	m_pImg->setActive(_b);
	if (!_b)
	{
		if (m_pEff)DisposeSprite(m_pEff);
		m_pEff = NULL;
	}
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
// �G�̒e�̈ړ��������Z�b�g����
// �����P�F�V�����ړ������i�x�N�g���j
//����������������������������������������������
void EnemyBullet::SetMoveDirection(XMFLOAT2 _moveDirection)
{
	m_moveDirection = _moveDirection;
}

//����������������������������������������������
// �ړ��̏���
//����������������������������������������������
void EnemyBullet::MoveProcess(float _deltaTime, XMFLOAT2 _SubmarinePos)
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
// �o�E���f�B���O�{�b�N�X���擾
//����������������������������������������������
BoundingBox* EnemyBullet::GetBoundingBox() const
{
	return m_pBoundingBox;
}

//����������������������������������������������
// �e������������������̏���
//����������������������������������������������
void EnemyBullet::Hit()
{
	if (!m_pImg->getActive())return;
	m_pImg->setActive(false);

	if (!ExplosionEffectOn)return;

	if (!m_pEff)m_pEff = CreateSprite(Tex_Bong, 45.f, 45.f, kTexelExplosionEff);
	else
	{
		m_pEff->setActive(true);
		m_pEff->setAnimation(0);
	}
	m_pEff->setPos(m_pImg->getPos());
	m_effCnt = 0;
	m_effAnimIndex = 0;
}

bool EnemyBullet::ImgActive()const
{
	return m_pImg->getActive();
}