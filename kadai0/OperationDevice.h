//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：OperationDevice.h
// 概要　　　　　：操作装置のクラス
// 作成者　　　　：20CU0332 フアンスアンズン
// 更新内容　　　：2021/11/29 作成（ズン）
//				  2021/12/01 描画メソッドを定義（ズン）
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
	OperationDevice(GameInfo* _pGameInfo, XMFLOAT2 _pos = { 0.f, 0.f }, XMFLOAT2 _relativePos = { 0.f, 0.f }, int _index = 0);
	~OperationDevice();

	//毎フレームの更新処理
	void Tick(float _deltaTime);

	//画像を描画
	void RenderDevice();

	//プレイヤーとの当たり判定
	void collisionWithPlayer(Player* _player, float _deltaTime);

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

	bool m_bPlayer1IsUsing;
	bool m_bPlayer2IsUsing;
};