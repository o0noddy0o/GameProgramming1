/**
 * ここでそれぞれの画像のUV座標を指定する
 */
#pragma once

#include "stdafx.h"
#include "Common3DType.h"

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// サンプル
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// const std::vector <QuadrangleTexel>   kTexelSamples = {
// 	//	左下					左上					右下					右上
// 	{ { 0.0f / 4.0f, 1.0f }, { 0.0f / 4.0f, 0.0f }, { 1.0f / 4.0f, 1.0f }, { 1.0f / 4.0f, 0.0f } },
// };
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

const std::vector <QuadrangleTexel>  singleTexels =
{
	{ { 0.f, 1.f },{ 0.f, 0.f },{ 1.f, 1.f },{ 1.f, 0.f } }	//!< 指定するUV座標の配列が一つの配列
};

const std::vector <QuadrangleTexel>  kTexelText =
{
	// 数字
	{ { 0.0f       , 5.0f / 6.0f },{ 0.0f       , 4.0f / 6.0f },{ 1.0f / 7.0f, 5.0f / 6.0f },{ 1.0f / 7.0f, 4.0f / 6.0f } },	//!< 　０ー＞０
	{ { 1.0f / 7.0f, 5.0f / 6.0f },{ 1.0f / 7.0f, 4.0f / 6.0f },{ 2.0f / 7.0f, 5.0f / 6.0f },{ 2.0f / 7.0f, 4.0f / 6.0f } },	//!< 　１ー＞１
	{ { 2.0f / 7.0f, 5.0f / 6.0f },{ 2.0f / 7.0f, 4.0f / 6.0f },{ 3.0f / 7.0f, 5.0f / 6.0f },{ 3.0f / 7.0f, 4.0f / 6.0f } },	//!< 　２ー＞２
	{ { 3.0f / 7.0f, 5.0f / 6.0f },{ 3.0f / 7.0f, 4.0f / 6.0f },{ 4.0f / 7.0f, 5.0f / 6.0f },{ 4.0f / 7.0f, 4.0f / 6.0f } },	//!< 　３ー＞３
	{ { 4.0f / 7.0f, 5.0f / 6.0f },{ 4.0f / 7.0f, 4.0f / 6.0f },{ 5.0f / 7.0f, 5.0f / 6.0f },{ 5.0f / 7.0f, 4.0f / 6.0f } },	//!< 　４−＞４

	{ { 0.0f       , 1.0f        },{ 0.0f       , 5.0f / 6.0f },{ 1.0f / 7.0f, 1.0f        },{ 1.0f / 7.0f, 5.0f / 6.0f } },	//!< 　５ー＞５
	{ { 1.0f / 7.0f, 1.0f        },{ 1.0f / 7.0f, 5.0f / 6.0f },{ 2.0f / 7.0f, 1.0f        },{ 2.0f / 7.0f, 5.0f / 6.0f } },	//!< 　６ー＞６
	{ { 2.0f / 7.0f, 1.0f        },{ 2.0f / 7.0f, 5.0f / 6.0f },{ 3.0f / 7.0f, 1.0f        },{ 3.0f / 7.0f, 5.0f / 6.0f } },	//!< 　７ー＞７
	{ { 3.0f / 7.0f, 1.0f        },{ 3.0f / 7.0f, 5.0f / 6.0f },{ 4.0f / 7.0f, 1.0f        },{ 4.0f / 7.0f, 5.0f / 6.0f } },	//!< 　８ー＞８
	{ { 4.0f / 7.0f, 1.0f        },{ 4.0f / 7.0f, 5.0f / 6.0f },{ 5.0f / 7.0f, 1.0f        },{ 5.0f / 7.0f, 5.0f / 6.0f } },	//!< 　９−＞９

	// アルファベット
	{ { 0.0f       , 1.0f / 6.0f },{ 0.0f       , 0.0f },{ 1.0f / 7.0f, 1.0f / 6.0f },{ 1.0f / 7.0f, 0.0f } },					//!< １０ー＞A
	{ { 1.0f / 7.0f, 1.0f / 6.0f },{ 1.0f / 7.0f, 0.0f },{ 2.0f / 7.0f, 1.0f / 6.0f },{ 2.0f / 7.0f, 0.0f } },					//!< １１ー＞B
	{ { 2.0f / 7.0f, 1.0f / 6.0f },{ 2.0f / 7.0f, 0.0f },{ 3.0f / 7.0f, 1.0f / 6.0f },{ 3.0f / 7.0f, 0.0f } },					//!< １２ー＞C
	{ { 3.0f / 7.0f, 1.0f / 6.0f },{ 3.0f / 7.0f, 0.0f },{ 4.0f / 7.0f, 1.0f / 6.0f },{ 4.0f / 7.0f, 0.0f } },					//!< １３ー＞D
	{ { 4.0f / 7.0f, 1.0f / 6.0f },{ 4.0f / 7.0f, 0.0f },{ 5.0f / 7.0f, 1.0f / 6.0f },{ 5.0f / 7.0f, 0.0f } },					//!< １４−＞E
	{ { 5.0f / 7.0f, 1.0f / 6.0f },{ 5.0f / 7.0f, 0.0f },{ 6.0f / 7.0f, 1.0f / 6.0f },{ 6.0f / 7.0f, 0.0f } },					//!< １５−＞F
	{ { 6.0f / 7.0f, 1.0f / 6.0f },{ 6.0f / 7.0f, 0.0f },{ 1.0f       , 1.0f / 6.0f },{ 1.0f       , 0.0f } },					//!< １６−＞G
							
	{ { 0.0f       , 2.0f / 6.0f },{ 0.0f       , 1.0f / 6.0f },{ 1.0f / 7.0f, 2.0f / 6.0f },{ 1.0f / 7.0f, 1.0f / 6.0f } },	//!< １７ー＞H
	{ { 1.0f / 7.0f, 2.0f / 6.0f },{ 1.0f / 7.0f, 1.0f / 6.0f },{ 2.0f / 7.0f, 2.0f / 6.0f },{ 2.0f / 7.0f, 1.0f / 6.0f } },	//!< １８ー＞I
	{ { 2.0f / 7.0f, 2.0f / 6.0f },{ 2.0f / 7.0f, 1.0f / 6.0f },{ 3.0f / 7.0f, 2.0f / 6.0f },{ 3.0f / 7.0f, 1.0f / 6.0f } },	//!< １９ー＞J
	{ { 3.0f / 7.0f, 2.0f / 6.0f },{ 3.0f / 7.0f, 1.0f / 6.0f },{ 4.0f / 7.0f, 2.0f / 6.0f },{ 4.0f / 7.0f, 1.0f / 6.0f } },	//!< ２０ー＞K
	{ { 4.0f / 7.0f, 2.0f / 6.0f },{ 4.0f / 7.0f, 1.0f / 6.0f },{ 5.0f / 7.0f, 2.0f / 6.0f },{ 5.0f / 7.0f, 1.0f / 6.0f } },	//!< ２１−＞L
	{ { 5.0f / 7.0f, 2.0f / 6.0f },{ 5.0f / 7.0f, 1.0f / 6.0f },{ 6.0f / 7.0f, 2.0f / 6.0f },{ 6.0f / 7.0f, 1.0f / 6.0f } },	//!< ２２−＞M
	{ { 6.0f / 7.0f, 2.0f / 6.0f },{ 6.0f / 7.0f, 1.0f / 6.0f },{ 1.0f       , 2.0f / 6.0f },{ 1.0f       , 1.0f / 6.0f } },	//!< ２３−＞N
														 							  
	{ { 0.0f       , 3.0f / 6.0f },{ 0.0f       , 2.0f / 6.0f },{ 1.0f / 7.0f, 3.0f / 6.0f },{ 1.0f / 7.0f, 2.0f / 6.0f } },	//!< ２４ー＞O
	{ { 1.0f / 7.0f, 3.0f / 6.0f },{ 1.0f / 7.0f, 2.0f / 6.0f },{ 2.0f / 7.0f, 3.0f / 6.0f },{ 2.0f / 7.0f, 2.0f / 6.0f } },	//!< ２５ー＞P
	{ { 2.0f / 7.0f, 3.0f / 6.0f },{ 2.0f / 7.0f, 2.0f / 6.0f },{ 3.0f / 7.0f, 3.0f / 6.0f },{ 3.0f / 7.0f, 2.0f / 6.0f } },	//!< ２６ー＞Q
	{ { 3.0f / 7.0f, 3.0f / 6.0f },{ 3.0f / 7.0f, 2.0f / 6.0f },{ 4.0f / 7.0f, 3.0f / 6.0f },{ 4.0f / 7.0f, 2.0f / 6.0f } },	//!< ２７ー＞R
	{ { 4.0f / 7.0f, 3.0f / 6.0f },{ 4.0f / 7.0f, 2.0f / 6.0f },{ 5.0f / 7.0f, 3.0f / 6.0f },{ 5.0f / 7.0f, 2.0f / 6.0f } },	//!< ２８−＞S
	{ { 5.0f / 7.0f, 3.0f / 6.0f },{ 5.0f / 7.0f, 2.0f / 6.0f },{ 6.0f / 7.0f, 3.0f / 6.0f },{ 6.0f / 7.0f, 2.0f / 6.0f } },	//!< ２９−＞T
	{ { 6.0f / 7.0f, 3.0f / 6.0f },{ 6.0f / 7.0f, 2.0f / 6.0f },{ 1.0f       , 3.0f / 6.0f },{ 1.0f       , 2.0f / 6.0f } },	//!< ３０−＞U
														 							  
	{ { 0.0f       , 4.0f / 6.0f },{ 0.0f       , 3.0f / 6.0f },{ 1.0f / 7.0f, 4.0f / 6.0f },{ 1.0f / 7.0f, 3.0f / 6.0f } },	//!< ３１ー＞V
	{ { 1.0f / 7.0f, 4.0f / 6.0f },{ 1.0f / 7.0f, 3.0f / 6.0f },{ 2.0f / 7.0f, 4.0f / 6.0f },{ 2.0f / 7.0f, 3.0f / 6.0f } },	//!< ３２ー＞W
	{ { 2.0f / 7.0f, 4.0f / 6.0f },{ 2.0f / 7.0f, 3.0f / 6.0f },{ 3.0f / 7.0f, 4.0f / 6.0f },{ 3.0f / 7.0f, 3.0f / 6.0f } },	//!< ３３ー＞X
	{ { 3.0f / 7.0f, 4.0f / 6.0f },{ 3.0f / 7.0f, 3.0f / 6.0f },{ 4.0f / 7.0f, 4.0f / 6.0f },{ 4.0f / 7.0f, 3.0f / 6.0f } },	//!< ３４ー＞Y
	{ { 4.0f / 7.0f, 4.0f / 6.0f },{ 4.0f / 7.0f, 3.0f / 6.0f },{ 5.0f / 7.0f, 4.0f / 6.0f },{ 5.0f / 7.0f, 3.0f / 6.0f } },	//!< ３５−＞Z

	// 符号
	{ { 5.0f / 7.0f, 4.0f / 6.0f },{ 5.0f / 7.0f, 3.0f / 6.0f },{ 6.0f / 7.0f, 4.0f / 6.0f },{ 6.0f / 7.0f, 3.0f / 6.0f } },	//!< ３６ー＞"
	{ { 6.0f / 7.0f, 4.0f / 6.0f },{ 6.0f / 7.0f, 3.0f / 6.0f },{ 1.0f       , 4.0f / 6.0f },{ 1.0f       , 3.0f / 6.0f } },	//!< ３７ー＞,
	{ { 5.0f / 7.0f, 5.0f / 6.0f },{ 5.0f / 7.0f, 4.0f / 6.0f },{ 6.0f / 7.0f, 5.0f / 6.0f },{ 6.0f / 7.0f, 4.0f / 6.0f } },	//!< ３８ー＞.
	{ { 6.0f / 7.0f, 5.0f / 6.0f },{ 6.0f / 7.0f, 4.0f / 6.0f },{ 1.0f       , 5.0f / 6.0f },{ 1.0f       , 4.0f / 6.0f } },	//!< ３９ー＞謎のC
	{ { 5.0f / 7.0f, 1.0f        },{ 5.0f / 7.0f, 5.0f / 6.0f },{ 6.0f / 7.0f, 1.0f        },{ 6.0f / 7.0f, 5.0f / 6.0f } },	//!< ４０ー＞ー（ハイフン）
	{ { 6.0f / 7.0f, 1.0f        },{ 6.0f / 7.0f, 5.0f / 6.0f },{ 1.0f       , 1.0f        },{ 1.0f       , 5.0f / 6.0f } },	//!< ４１ー＞！
};

const std::vector <QuadrangleTexel>  kTexelNumber =
{
	{ { 0.0f       , 1.0f / 2.0f },{ 0.0f       , 0.0f },{ 1.0f / 5.0f, 1.0f / 2.0f },{ 1.0f / 5.0f, 0.0f } },		//!< 　０
	{ { 1.0f / 5.0f, 1.0f / 2.0f },{ 1.0f / 5.0f, 0.0f },{ 2.0f / 5.0f, 1.0f / 2.0f },{ 2.0f / 5.0f, 0.0f } },		//!< 　１
	{ { 2.0f / 5.0f, 1.0f / 2.0f },{ 2.0f / 5.0f, 0.0f },{ 3.0f / 5.0f, 1.0f / 2.0f },{ 3.0f / 5.0f, 0.0f } },		//!< 　２
	{ { 3.0f / 5.0f, 1.0f / 2.0f },{ 3.0f / 5.0f, 0.0f },{ 4.0f / 5.0f, 1.0f / 2.0f },{ 4.0f / 5.0f, 0.0f } },		//!< 　３
	{ { 4.0f / 5.0f, 1.0f / 2.0f },{ 4.0f / 5.0f, 0.0f },{ 5.0f / 5.0f, 1.0f / 2.0f },{ 5.0f / 5.0f, 0.0f } },		//!< 　４

	{ { 0.0f       , 1.0f },{ 0.0f       , 1.0f / 2.0f },{ 1.0f / 5.0f, 1.0f },{ 1.0f / 5.0f, 1.0f / 2.0f } },		//!< 　５
	{ { 1.0f / 5.0f, 1.0f },{ 1.0f / 5.0f, 1.0f / 2.0f },{ 2.0f / 5.0f, 1.0f },{ 2.0f / 5.0f, 1.0f / 2.0f } },		//!< 　６
	{ { 2.0f / 5.0f, 1.0f },{ 2.0f / 5.0f, 1.0f / 2.0f },{ 3.0f / 5.0f, 1.0f },{ 3.0f / 5.0f, 1.0f / 2.0f } },		//!< 　７
	{ { 3.0f / 5.0f, 1.0f },{ 3.0f / 5.0f, 1.0f / 2.0f },{ 4.0f / 5.0f, 1.0f },{ 4.0f / 5.0f, 1.0f / 2.0f } },		//!< 　８
	{ { 4.0f / 5.0f, 1.0f },{ 4.0f / 5.0f, 1.0f / 2.0f },{ 5.0f / 5.0f, 1.0f },{ 5.0f / 5.0f, 1.0f / 2.0f } },		//!< 　９
};
