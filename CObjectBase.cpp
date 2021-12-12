//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：CObjectBase.cpp
// 概要　　　　　：すべて画面に出すオブジェクトの親クラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "CObjectBase.h"
#include "CPicture.h"
#include "MediaResource.h"
#include "CCamera.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
// 引数１：ゲームの情報
//━━━━━━━━━━━━━━━━━━━━━━━
CObjectBase::CObjectBase(GameInfo* _pGameInfo) 
	: m_pGameInfo(_pGameInfo)
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
CObjectBase::~CObjectBase()
{
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を作成するメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
CPicture* CObjectBase::CreateSprite(LPCWSTR path_, float width_, float height_, std::vector <QuadrangleTexel> _texelsUV)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CPicture* object = NULL;

	// 基本的な作成
	object = CPicture::create(*(m_pGameInfo->pDevice), *(m_pGameInfo->pDeviceContext), (m_pGameInfo->pViewPort), HLSL_AlphaHLSL, path_,
		{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
		spriteSize,					//!< スプライトのサイズ
		_texelsUV);				//!< 指定するUV座標の配列
	return object;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を破棄するメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CObjectBase::DisposeSprite(CPicture* object)
{
	if (object != NULL)
	{
		object->release();
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画するメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
void CObjectBase::RenderSprite(CPicture* object, XMFLOAT4 _col)
{
	XMFLOAT4X4	matView = (*m_pGameInfo->pCamera)->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = (*m_pGameInfo->pCamera)->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		object->render(matView, matProj, 0Ui64, _col);
	}
}

CFont* CObjectBase::createFont(LPCWSTR path_, int digits_, float width_, float height_, std::vector <QuadrangleTexel> _texelsUV)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CFont* objects = NULL;

	objects = CFont::create(*(m_pGameInfo->pDevice), *(m_pGameInfo->pDeviceContext), (m_pGameInfo->pViewPort), HLSL_PlaneHLSL, path_,
		{ 0.0f, 0.0f, 0.0f, 0.0f },	// スプライトの位置
		spriteSize,					// スプライトのサイズ
		_texelsUV,					// 指定するUV座標の配列
		digits_);					// 桁数

	return objects;
}

void CObjectBase::renderFont(CFont* object, int num_, XMFLOAT4 _col)
{
	XMFLOAT4X4	matView = (*m_pGameInfo->pCamera)->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = (*m_pGameInfo->pCamera)->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		object->render(matView, matProj, num_, 0Ui64, _col);
	}
}

void CObjectBase::disposeFont(CFont* object)
{
	if (object != NULL)
	{
		object->release();
	}
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 入力を取得するメソッド
//━━━━━━━━━━━━━━━━━━━━━━━
std::shared_ptr<CDirectInput> CObjectBase::GetInput()
{
	return *(m_pGameInfo->pDirectInput);
}