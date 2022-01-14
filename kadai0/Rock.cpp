//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Rock.cpp
// 概要　　　　　：岩のクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/01/13 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Rock.h"
#include "GameResource.h"
#include "PolygonBoundingBox.h"

Rock::Rock(GameInfo* _pGameInfo, int _rockType, XMFLOAT2 _pos, float _angle)
	: Super(_pGameInfo)
{
	vector<XMFLOAT2> vector;
	switch (_rockType)
	{
	case 1:
		{
			m_pImg = CreateSprite(Tex_Rock1, 959.f, 1374.f);
			m_pImg->setPos(_pos);
			vector =
			{
				{ -480.f, 684.f },
				{ 480.f, 652.f },
				{ 480.f, -684.f },
				{ -184.f, -268.f },
			};
			
		}
		break;
	case 2:
		{
			m_pImg = CreateSprite(Tex_Rock2, 848.f, 2207.f);
			m_pImg->setPos(_pos);
			vector =
			{
				{ 424.f, 1120.f },
				{ 424.f, -1096.f },
				{ -152.f, -680.f },
				{ -432.f, 280.f },
			};
		}
		break;
	case 3:
		{
			m_pImg = CreateSprite(Tex_Rock3, 1739.f, 633.f);
			m_pImg->setPos(_pos);
			vector =
			{
				{ 630.f, 318.f },
				{ 868.f, -10.f },
				{ 206.f, -314.f },
				{ -710.f, -214.f },
				{ -870.f, 192.f },
			};
		}
		break;
	case 4:
		{
			m_pImg = CreateSprite(Tex_Rock4, 1445.f, 624.f);
			m_pImg->setPos(_pos);
			vector =
			{
				{ 126.f, 312.f },
				{ 720.f, -6.f },
				{ -300.f, -310.f },
				{ -722.f, -166.f },
				{ -428.f, 268.f },
			};
		}
		break;
	case 5:
		{
			m_pImg = CreateSprite(Tex_Rock5, 708.f, 857.f);
			m_pImg->setPos(_pos);
			vector =
			{
				{ -134.f, 428.f },
				{ 270.f, 206.f },
				{ 354.f, -158.f },
				{ 140.f, -400.f },
				{ -94.f, -428.f },
				{ -354.f, -74.f },
				{ -294.f, 274.f },
			};
		}
		break;
	}
	m_pBoundingBox = new PolygonBoundingBox(_pos, vector);
	if (_angle != 0.f)
	{
		m_pImg->setAngleZ(_angle);
		((PolygonBoundingBox*)m_pBoundingBox)->RotateVertex(_angle);
	}
}

Rock::~Rock()
{
}