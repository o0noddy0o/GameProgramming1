/**
 * @file CActionGameApp.cpp
 * @brief アプリケーションのエントリ ポイントを定義します。
 * @author 織戸　喜隆
 * @date 日付（2017.02.14）
 */

#include "stdafx.h"
#include "CActionGameApp.h"
#include "kadai0/CText.h"
#include "kadai0/InOutputFile.h"
#include "kadai0/GameResource.h"

CActionGameApp::CActionGameApp()
{
	gameInfo.pDevice = &m_pDevice;
	gameInfo.pDeviceContext = &m_pDeviceContext;
	gameInfo.pViewPort = &m_viewPort[0];
	gameInfo.pCamera = &m_pCamera;
	gameInfo.pDirectInput = &m_pDirectInput;

	pText = new CText(getGameInfo(), Tex_Text, kTexelText, XMFLOAT2(28.f, 28.f), XMFLOAT2(0.f, 0.f), XMFLOAT2(5.f, 14.f));
}


CActionGameApp::~CActionGameApp()
{
	delete pText;
	delete pInOutFile;
}

/**
 * @fn void CActionGameApp::initCameraInfo()
 * @brief カメラの設定
 * @param	無し
 * @return	無し
 */
void CActionGameApp::initCameraInfo()
{
	float z = -(float)(min(WINDOW_HEIGHT,WINDOW_WIDTH) / 2) / tanf(XM_PI / 8.0f);
	m_vEyePt	= XMFLOAT3{ 0.0f, 0.0f,		z };	//!< カメラ（視点）位置
	m_vLookatPt	= XMFLOAT3{ 0.0f, 0.0f,     0.0f };	//!< 注視位置
	m_vUpVec	= XMFLOAT3{ 0.0f, 1.0f,     0.0f };	//!< 上方位置
	m_angle		= (FLOAT)XM_PI / 4;					//!< 視野角
	m_aspect	= ASPECT;							//!< アスペクト比
	m_near		= 0.1f;								//!< 前方クリップ
	m_far		= abs(z) + 100.0f;					//!< 後方クリップ
}


CPicture* CActionGameApp::createSprite (LPCWSTR path_, float width_, float height_)
{
	vector <QuadrangleTexel>  singleTexels = {
	QuadrangleTexel{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }	//!< テクセルの配列が一つの配列
	};
	XMFLOAT2 spriteSize = { width_, height_};
	CPicture* object = NULL;

	object = CPicture::create (m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
		{ 0.0f, 0.0f, 0.0f, 0.0f },	//!< スプライトの位置
		spriteSize,					//!< スプライトのサイズ
		singleTexels);				//!< テクセルの配列
	
	return object;
}

void CActionGameApp::renderSprite( CPicture* object)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if( object != NULL)
	{
#if 1
		XMFLOAT4 col;
		col.x = 1.0f;
		col.y = 1.0f;
		col.z = 1.0f;
		col.w = 1.0f;

		object->render(matView, matProj, 0Ui64, col);
#else
		object->render(matView, matProj);
#endif
	}
}
void CActionGameApp::renderSprite(CPicture* object, XMFLOAT3 color)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		XMFLOAT4 col;
		col.x = color.x;
		col.y = color.y;
		col.z = color.z;

		object->render(matView, matProj, 0Ui64, col);
	}
}
void CActionGameApp::renderSprite(CPicture* object, float r, float g, float b)
{
	renderSprite( object, XMFLOAT3(r, g, b));
}
void CActionGameApp::renderSprite(CPicture* object, XMFLOAT4 color)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		XMFLOAT4 col;
		col.x = color.x;
		col.y = color.y;
		col.z = color.z;
		col.w = color.w;

		object->render(matView, matProj, 0Ui64, col);
	}
}

void CActionGameApp::disposeSprite( CPicture* object)
{
	if( object != NULL)
	{
		object->release();
		delete object;
	}
}

CFont* CActionGameApp::createFont(LPCWSTR path_, int digits_, float width_, float height_)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CFont* objects = NULL;

	return objects;
}
void CActionGameApp::renderFont(CFont* object, int num_)
{
	XMFLOAT4X4	matView = m_pCamera->getViewMatrix();		 //!< ビュートランスフォーム（視点座標変換）
	XMFLOAT4X4	matProj = m_pCamera->getProjectionMatrix();	 //!< プロジェクショントランスフォーム（射影変換）
	if (object != NULL)
	{
		object->render(matView, matProj, num_);
	}
}
void CActionGameApp::disposeFont(CFont* object)
{
	if (object != NULL)
	{
		object->release();
	}
}

/**
 * @fn bool CActionGameApp::createSpaceship(void)
 * @brief スプライトの生成
 * @param	無し
 * @return	成功・失敗
 */
bool CActionGameApp::createSpaceship(void)
{
	/*
    if (m_pPlayer == NULL)
    {
        m_pPlayer = CPlayer::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL,
            { 0.0f, -200.0f, 0.0f, 0.0f },	//!< スプライトの位置
            kCharSpriteSize,				//!< スプライトのサイズ
            kTexelPlayerBulletIndex);		//!< テクセルの配列のインデックス（アニメーションのため）
    }
    m_pPlayer->setHP(kMaxHP);                           // <!
    m_pPlayer->setDamage(FALSE);                        // <!
    m_pPlayer->setActive(TRUE);                         // <!
    m_pPlayer->setPos({ 0.0f, -200.0f, 0.0f, 0.0f });   // <!
	m_pPlayer->setState(eMoving);
	m_pPlayer->setScale(1.0f);
    m_pPlayer->resetExplosion();                        // <!
    m_pPlayer->resetAllBullets();                       // <!
    m_pPlayer->setAngleZ(0.0f);                         // <!

	XMFLOAT4 ePos[] = {
		{-120.0f +  0 + 48 * 0, 200.0f, 0.0f, 0.0f},
		{-120.0f +  0 + 48 * 1, 200.0f, 0.0f, 0.0f},
		{-120.0f +  0 + 48 * 2, 200.0f, 0.0f, 0.0f},
		{-120.0f +  0 + 48 * 3, 200.0f, 0.0f, 0.0f},
		{-120.0f +  0 + 48 * 4, 200.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 0, 160.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 1, 160.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 2, 160.0f, 0.0f, 0.0f},
		{-120.0f + 24 + 48 * 3, 160.0f, 0.0f, 0.0f}
	};
	for (size_t i = 0; i < _countof(m_pEnemies); i++)
	{
        if (m_pEnemies[i] == NULL)
        {
            m_pEnemies[i] = CEnemy::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_PlaneHLSL,
                ePos[i],                    //!< スプライトの位置
                kCharSpriteSize,			//!< スプライトのサイズ
                kTexelEnemyBulletIndex);	//!< テクセルの配列のインデックス（アニメーションのため）
        }
        m_pEnemies[i]->setHP(kMaxHP);       // !<
        m_pEnemies[i]->setDamage(FALSE);    // <!
        m_pEnemies[i]->setActive(TRUE);     // !<
        m_pEnemies[i]->setPos(ePos[i]);     // !<
		m_pEnemies[i]->setState(eMoving);
		m_pEnemies[i]->setScale(1.0f);
        m_pEnemies[i]->resetExplosion();     //!< 
        m_pEnemies[i]->resetAllBullets();    //!< 
	}
	m_pPlayerTex    = CTexture::create(m_pDevice, Tex_Spaceship);	//!< テクセル
	m_pEnemyTex     = CTexture::create(m_pDevice, Tex_Spaceship);	//!< テクセル
	*/

	return true;
}

/**
 * @fn void CActionGameApp::doOpenning()
 * @brief オープニング
 * @param	無し
 * @return	無し
 */
void CActionGameApp::doOpenning ()
{
	procTitle();
}

/**
 * @fn void CActionGameApp::doPlaying()
 * @brief プレー中
 * @param	無し
 * @return	無し
 */
void CActionGameApp::doPlaying ()
{
#if 0
	// 【ステップ4】
	/**
	* プレイヤーのアニメーション
	*/
	m_frameCounter++;
	m_frameCounter = m_frameCounter > 99 ? 0 : m_frameCounter;

	m_pPlayer->stepAnimation(m_frameCounter % kTexelIntervalFrames == 0);

    m_pBack->scroll(-1.0f);
	m_pMiddle->scroll(-2.0f);
	m_pFront->scroll(-3.0f);
	/**
	* プレーヤーの制御
	*/
	if (m_pDirectInput->isKeyPressed(DIK_LEFT))		m_pPlayer->offsetPosInNormalRange({ -2.0f,  0.0f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_RIGHT))	m_pPlayer->offsetPosInNormalRange({  2.0f,  0.0f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_UP))		m_pPlayer->offsetPosInNormalRange({  0.0f,  2.0f, 0.0f, 0.0f });
	if (m_pDirectInput->isKeyPressed(DIK_DOWN))		m_pPlayer->offsetPosInNormalRange({  0.0f, -2.0f, 0.0f, 0.0f });

	if (m_pDirectInput->isKeyPressed(DIK_V))		m_pPlayer->addAngleZ(-0.5);
	if (m_pDirectInput->isKeyPressed(DIK_N))		m_pPlayer->addAngleZ( 0.5);
	if (m_pDirectInput->isPressedOnce(DIK_B))		m_pPlayer->shot();

	if (m_pDirectInput->isLeftButtonClicked())	    m_pPlayer->shot();

	/**
	* 【ステップ5】敵の操作
	*/
    auto    callback = [&](std::shared_ptr<CEnemy> enemy_, size_t index_) -> BOOL {
        if (enemy_->getActive() == TRUE)
        {
            prepareFrame(enemy_, index_);
        }
        return TRUE; //!< 列挙を続行
    };
	if (isActiveEnemies() == FALSE)
	{
		m_gameStatus = eGameClear;
	}
	
	/**
	* プレーヤーの爆発が完了したらゲームオーバー.
	*/
	if (m_pPlayer->isExplosionCompleted())
	{
		m_gameStatus = eGameOver;
	}
#else
	procGame ();

#endif
}


/**
 * @fn void CActionGameApp::doGameClear()
 * @brief ゲームクリア
 * @param	無し
 * @return	無し
 */
void CActionGameApp::doGameClear()
{
	procClear ();
}

/**
 * @fn void CActionGameApp::doGameOver()
 * @brief ゲームオーバー
 * @param	無し
 * @return	無し
 */
void CActionGameApp::doGameOver()
{
	procGameOver ();
}

/**
 * @fn void CActionGameApp::doEnding()
 * @brief エンディング
 * @param	無し
 * @return	無し
 */
void CActionGameApp::doEnding()
{
}

/**
 * @fn void CActionGameApp::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
 * @brief レンダー
 * @param	matView_	ビュー行列
 * @param	matProj_	プロジェクション行列
 * @return				無し
 */
void CActionGameApp::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	/*
    auto setUpEnemyTex = [&](ID3D11DeviceContext* pDeviceContext_) -> void {
        m_pEnemyTex->setup(pDeviceContext_);
    };
    auto callback = [&](CEnemy* enemy_, size_t index_) -> BOOL {
		enemy_->render(matView_, matProj_, setUpEnemyTex);
		return TRUE; //!< 列挙を続行	
    };
    auto setUpPlayerTex = [&](ID3D11DeviceContext* pDeviceContext_) -> void {
        m_pPlayerTex->setup(pDeviceContext_);
    };

	switch (m_gameStatus)
	{
	case eOpening:
		m_pTitle->render(matView_, matProj_);
		break;
	case ePlaying:
		// 引数描画する順番と結果を確認すること
		m_pPlayer->render(matView_, matProj_, setUpPlayerTex);

		m_pFront->render(matView_, matProj_);
		m_pMiddle->render(matView_, matProj_);
		m_pBack->render(matView_, matProj_);
		break;
	case eGameOver:
		m_pGameOver->render(matView_, matProj_);
		break;
	default:
		break;
	}
	*/
}


/**
* @fn void CActionGameApp::release()
* @brief 解放
* @param	無し
* @return	無し
*/
void CActionGameApp::release()
{
	super::release();
//	m_pTitle->release();
//	m_pGameOver->release();
}

GameInfo* CActionGameApp::getGameInfo()
{
	return &gameInfo;
}