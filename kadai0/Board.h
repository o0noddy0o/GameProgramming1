//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：Board.h
// 概要　　　　　：掲示板管理クラス
// 作成者　　　　：20CU0332 ズン
// 更新内容　　　：2022/02/20 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once

#include "CObjectBase.h"

class CObjectBase;

class Board : public CObjectBase
{
    typedef CObjectBase Super;
public:
    Board(GameInfo* _pGameInfo, int _BoardNum, XMFLOAT2 _pos = { 0.f, 0.f });
    ~Board();

    //每フレームにやる処理
    void Tick(float _deltaTime);

    //画像を描画
    void RenderBoard();

    //画像の座標更新
    void SetPos(XMFLOAT2 _newPos);

private:
    CPicture* m_pImg;         //掲示板の画像
    CPicture* m_pText;        //掲示板に書かれている文字の画像
};