//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：OperationDevice.cpp
// 概要　　　　　：操作装置のクラス
// 作成者　　　　：20CU0332 フアンスアンズン
// 更新内容　　　：2021/11/29 作成（ズン）
//				  2021/12/01 描画メソッドを定義（ズン）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "OperationDevice.h"
#include "GameResource.h"
#include "Player.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
OperationDevice::OperationDevice(GameInfo* _pGameInfo, XMFLOAT2 _pos, XMFLOAT2 _relativePos, int _index)
	: Super(_pGameInfo)
	, m_relativePos(_pos)
	, m_bPlayer1IsUsing(false)
	, m_bPlayer2IsUsing(false)
{
	switch (_index)
	{
	case 0:
		m_pImg = CreateSprite(Tex_Operation_Device_1, 64.f, 64.f);
		m_pImg->setPos(1500.f, 1500.f);
		break;
	case 1:
		m_pImg = CreateSprite(Tex_Operation_Device_2, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 2:
		m_pImg = CreateSprite(Tex_Operation_Device_3, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 3:
		m_pImg = CreateSprite(Tex_Operation_Device_4, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 4:
		m_pImg = CreateSprite(Tex_Operation_Device_5, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	/*case 5:
		m_pImg = CreateSprite(Tex_Operation_Device_4, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;*/
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
OperationDevice::~OperationDevice()
{
	DisposeSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 毎フレームにやる処理
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::Tick(float _deltaTime)
{
	
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::RenderDevice()
{
	RenderSprite(m_pImg);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤーとの当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::collisionWithPlayer(Player* _player, float _deltaTime)
{
	switch (_player->getPlayerIdx())
	{
	case 1:
		if (m_bPlayer2IsUsing)return;
		if ((bool)m_pImg->collision(_player->GetImg()) == true)
		{
			if (GetInput()->isPressedOnce(DIK_NUMPAD3))
			{
				m_bPlayer1IsUsing = !m_bPlayer1IsUsing;
				_player->SetMoveAble(!m_bPlayer1IsUsing);
			}
			if (m_bPlayer1IsUsing)
			{
				m_pComponent->InputProcess(1, _deltaTime);
			}
		}
		break;

	case 2:
		if (m_bPlayer1IsUsing)return;
		if ((bool)m_pImg->collision(_player->GetImg()) == true)
		{
			if (GetInput()->isPressedOnce(DIK_M))
			{
				m_bPlayer2IsUsing = !m_bPlayer2IsUsing;
				_player->SetMoveAble(!m_bPlayer2IsUsing);
			}
			if (m_bPlayer2IsUsing)
			{
				m_pComponent->InputProcess(2, _deltaTime);
			}
		}
		break;
	}	
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 対応する部品のアドレス（潜水艦クラス用）
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::SetComponent(shared_ptr<Component> _component)
{
	m_pComponent = _component.get();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像の位置を設置
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::SetPos(XMFLOAT2 _newPos)
{
	m_pImg->setPos(_newPos.x + m_relativePos.x, _newPos.y + m_relativePos.y);
}