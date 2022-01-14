//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：SceneryObject.h
// 概要　　　　　：ステージに出る他の物のクラス
// 作成者　　　　：20CU0340 林星
// 更新内容　　　：2021/11/26 作成
// 　　　　　　　：2021/01/12 コンストラクタを編集
// 　　　　　　　　           GetBoundingBoxメソッド追加
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "CObjectBase.h"
#include "Define.h"
#include "BoundingBox.h"

class SceneryObject : public CObjectBase
{
public:
	SceneryObject(GameInfo* _pGameInfo);
	virtual ~SceneryObject();

	// 画像を取得する（当たり判定用）
	CPicture* GetImg() const;

	// 当たり判定
	virtual BoundingBox* GetBoundingBox()const;

	// 画像を描画する
	virtual void renderSprite();


protected:
	// 画像
	CPicture* m_pImg;
	BoundingBox* m_pBoundingBox;
};

