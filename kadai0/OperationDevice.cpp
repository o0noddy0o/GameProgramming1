//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：OperationDevice.cpp
// 概要　　　　　：操作装置のクラス
// 作成者　　　　：20CU0332 フアンスアンズン
// 更新内容　　　：2021/11/29 作成（ズン）
//━━━━━━━━━━━━━━━━━━━━━━━
#include "OperationDevice.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
OperationDevice::OperationDevice(GameInfo* _pGameInfo, XMFLOAT2 _pos, int _index)
	: Super(_pGameInfo)
{
	switch (_index)
	{
	case 1:
		m_pImg = CreateSprite(Tex_Operation_Device_1, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 2:
		m_pImg = CreateSprite(Tex_Operation_Device_2, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 3:
		m_pImg = CreateSprite(Tex_Operation_Device_3, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
	case 4:
		m_pImg = CreateSprite(Tex_Operation_Device_4, 64.f, 64.f);
		m_pImg->setPos(_pos);
		break;
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
// プレイヤーとの当たり判定
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::collisionWithPlayer(Player _player)
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// 対応する部品のアドレス（潜水艦クラス用）
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::SetComponent(shared_ptr<Component> _component)
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像の位置を設置
//━━━━━━━━━━━━━━━━━━━━━━━
void OperationDevice::SetPos(XMFLOAT2 _newPos)
{

}