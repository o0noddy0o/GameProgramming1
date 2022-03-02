

//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Board.cpp
// 概要　　　　　：掲示板管理クラス
// 作成者　　　　：20CU0332 ズン
// 更新内容　　　：2022/02/20 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "Board.h"
#include "Define.h"
#include "GameResource.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// コンストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Board::Board(GameInfo* _pGameInfo, int _BoardNum, XMFLOAT2 _pos)
    : Super(_pGameInfo)
{
    //画像を作成
    switch (_BoardNum)
    {
    case 1:
        m_pImg = CreateSprite(Tex_Board, 300.f, 300.f);
        m_pImg->setPos(_pos);
        m_pText = CreateSprite(Tex_Text_1, 300.f, 300.f);
        m_pText->setPos(_pos);
        break;
    case 2:
        m_pImg = CreateSprite(Tex_Board, 300.f, 300.f);
        m_pImg->setPos(_pos);
        m_pText = CreateSprite(Tex_Text_2, 300.f, 300.f);
        m_pText->setPos(_pos);
        break;
    }
}

//━━━━━━━━━━━━━━━━━━━━━━━
// デストラクタ
//━━━━━━━━━━━━━━━━━━━━━━━
Board::~Board()
{
    DisposeSprite(m_pImg);
    DisposeSprite(m_pText);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 每フレームにやる処理
//━━━━━━━━━━━━━━━━━━━━━━━
void Board::Tick(float _deltaTime)
{

}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像を描画
//━━━━━━━━━━━━━━━━━━━━━━━
void Board::RenderBoard()
{
    RenderSprite(m_pImg);
    RenderSprite(m_pText);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 画像の座標更新
//━━━━━━━━━━━━━━━━━━━━━━━
void Board::SetPos(XMFLOAT2 _newPos)
{

}