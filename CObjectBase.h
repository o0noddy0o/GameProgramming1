//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CObjectBase.h
// 概要　　　　　：すべて画面に出すオブジェクトの親クラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include "GameConst.h"
#include "CActionGameApp.h"
#include "kadai0/UV.h"

class CPicture;

class CObjectBase
{
protected:
	// コンストラクタ
	CObjectBase(GameInfo* _pGameInfo);

	// デストラクタ
	~CObjectBase();

	// 画像を作成するメソッド
	CPicture* CreateSprite(LPCWSTR path_, float width_ = WINDOW_WIDTH, float height_ = WINDOW_HEIGHT, std::vector <QuadrangleTexel> _texelsUV = singleTexels);
	
	// 画像を破棄するメソッド
	void DisposeSprite(CPicture* object);
	
	// 画像を描画するメソッド
	void RenderSprite(CPicture* object, XMFLOAT4 _col = XMFLOAT4(1.f, 1.f, 1.f, 1.f));

	CFont* createFont(LPCWSTR path_, int digits_, float width_, float height_, std::vector <QuadrangleTexel> _texelsUV = kTexelNumber);
	void renderFont(CFont* object, int num_, XMFLOAT4 _col = XMFLOAT4(1.f, 1.f, 1.f, 1.f));
	void disposeFont(CFont* object);

	void SetTexels(CPicture* _object, std::vector<QuadrangleTexel> _texels, XMFLOAT2 _size = { 0.f, 0.f });

	// 入力を取得するメソッド
	std::shared_ptr<CDirectInput> GetInput();

protected:
	// ゲームの情報
	GameInfo* m_pGameInfo;
};