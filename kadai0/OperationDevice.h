//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：OperationDevice.h
// 概要　　　　　：操作装置のクラス
// 作成者　　　　：20CU0332 フアンスアンズン
// 更新内容　　　：2021/11/29 作成（ズン）
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "Define.h"
#include "Component.h"
#include "CObjectBase.h"
#include "Player.h"


class OperationDevice : public CObjectBase
{
	typedef CObjectBase Super;
public:
	OperationDevice(GameInfo* _pGameInfo, XMFLOAT2 _pos, int _index);
	~OperationDevice();

	//プレイヤーとの当たり判定
	void collisionWithPlayer(Player _player);

	//対応する部品のアドレス（潜水艦クラス用）
	void SetComponent(shared_ptr<Component> _component);

	//画像の位置を設置
	void SetPos(XMFLOAT2 _newPos);

private:
	//操作装置の画像
	CPicture* m_pImg;

	//操作装置の座標と潜水艦の座標の差
	XMFLOAT2 m_relativePos;

	//対応する部品のアドレス
	Component* m_pComponent;
};