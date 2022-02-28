//����������������������������������������������
// �t�@�C�����@�@�FArrow.cpp
// �T�v�@�@�@�@�@�F�q���g�̖��̃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2022/02/27 �쐬
//����������������������������������������������
#include "Arrow.h"
#include "Define.h"
#include "GameResource.h"
#include "CameraManager.h"

Arrow::Arrow(GameInfo* _pGameInfo, XMFLOAT2 _goalPos)
	: Super(_pGameInfo)
	, m_goalPos(_goalPos)
{
	m_pImg = CreateSprite(Tex_Arrow, ARROW_SIZE_X, ARROW_SIZE_Y);
}

Arrow::~Arrow()
{
	DisposeSprite(m_pImg);
}

void Arrow::RenderSprite()
{
	Super::RenderSprite(m_pImg);
}

void Arrow::Tick()
{
	// �J�����̍��W���擾���Ă���
	XMFLOAT3 cameraPos = CameraManager::GetCameraPos();
	
	XMFLOAT2 vector = FindVectorByTwoPos(cameraPos, m_goalPos);

	// �S�[������ʓ��̏���
	if (Abs(vector.x) < WINDOW_RIGHT &&
		Abs(vector.y) < WINDOW_TOP)
	{
		m_pImg->setActive(false);
	}
	// �S�[������ʊO�̏���
	else
	{
		m_pImg->setAngleZ(DirectionVectorToAngle(vector) - 90.f);
		
		// ���E
		if (Abs(WINDOW_TOP / vector.y * vector.x) > WINDOW_RIGHT)
		{
			vector.y *= Abs((WINDOW_RIGHT - ARROW_SIZE_Y / 2.f) / vector.x);
			vector.x = ((vector.x > 0.f) ? (WINDOW_RIGHT - ARROW_SIZE_Y / 2.f) : (-(WINDOW_RIGHT - ARROW_SIZE_Y / 2.f)));
		}
		// �㉺
		else
		{
			vector.x *= Abs((WINDOW_TOP - ARROW_SIZE_Y / 2.f) / vector.y);
			vector.y = ((vector.y > 0.f) ? (WINDOW_TOP - ARROW_SIZE_Y / 2.f) : (-(WINDOW_TOP - ARROW_SIZE_Y / 2.f)));
		}
		vector.x += cameraPos.x;
		vector.y += cameraPos.y;
		m_pImg->setActive(true);
	}
	m_pImg->setPos(vector);
}