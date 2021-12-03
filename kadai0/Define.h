#pragma once

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦
//━━━━━━━━━━━━━━━━━━━━━━━
#define SUBMARINE_MOVE_SPEED		(30.f)
#define NUM_OF_OPERATION_DEVICE		(5)
#define NUM_OF_COMPONENT			(6)

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤー１
//━━━━━━━━━━━━━━━━━━━━━━━
#define PLAYER_1_SIZE_X				(128.f)
#define PLAYER_1_SIZE_Y				(128.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤー２
//━━━━━━━━━━━━━━━━━━━━━━━
#define PLAYER_2_SIZE_X				(128.f)
#define PLAYER_2_SIZE_Y				(128.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// タレット
//━━━━━━━━━━━━━━━━━━━━━━━
#define TURRET_DISTANCE				(300.f)
#define TURRET_SIZE_X				(40.f)
#define TURRET_SIZE_Y				(30.f)
#define TURRET_ROTATION_SPEED		(10.f)
#define TURRET_ROTATION_RANGE		(180.f)
#define TURRET_COOL_DOWN			(0)

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾
//━━━━━━━━━━━━━━━━━━━━━━━
#define BULLET_SIZE_X		(20.f)
#define BULLET_SIZE_Y		(20.f)
#define BULLET_MOVE_SPEED	(30.f)
#define BULLET_BOUNDING_BOX_RADIUS	(10.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// ジェットエンジン
//━━━━━━━━━━━━━━━━━━━━━━━
#define JET_ENGINE_SIZE_X			(600.f)
#define JET_ENGINE_SIZE_Y			(600.f)
#define JET_ENGINE_ROTATION_SPEED	(15.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// バリア
//━━━━━━━━━━━━━━━━━━━━━━━
#define BARRIER_SIZE_X			(600.f)
#define BARRIER_SIZE_Y			(600.f)
#define BARRIER_RANGE			(90.f)
#define BARRIER_ROTATION_SPEED	(15.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// マップサイズ
//━━━━━━━━━━━━━━━━━━━━━━━
#define Map_X_SIZE				(19)
#define Map_Y_SIZE				(24)
#define Block_X_SIZE			(60.f)
#define Block_Y_SIZE			(60.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// エネミーのサイズ
//━━━━━━━━━━━━━━━━━━━━━━━
#define Enemy_X_SIZE			(60.f)
#define Enemy_Y_SIZE			(60.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラ
//━━━━━━━━━━━━━━━━━━━━━━━
#define PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE	(0.30f)			

//━━━━━━━━━━━━━━━━━━━━━━━
// 描画用の色
//━━━━━━━━━━━━━━━━━━━━━━━
#define COLOR_RED		(XMFLOAT4(1.f, 0.f, 0.f, 1.f))
#define COLOR_YELLOW	(XMFLOAT4(1.f, (241.f / 255.f), 0.f, 1.f))

//━━━━━━━━━━━━━━━━━━━━━━━
// 計算用
//━━━━━━━━━━━━━━━━━━━━━━━
#define PI										((float)(3.1415926535))
#define Abs(x)									((x >= 0)?(x):(-x))
#define RadianToDegree(x)						((x) * 180.f / PI)
#define DegreeToRadian(x)						((x) * PI / 180.f)
#define AngleToDirectionVector(_angle)			{ cosf(DegreeToRadian(_angle)) , sinf(DegreeToRadian(_angle)) }
#define Degree(_angle)							((float)((_angle >= 0.f)?((int)(_angle) % 360):((360 + ((int)(_angle) % 360)))))

//━━━━━━━━━━━━━━━━━━━━━━━
// デバッグ・確認用
//━━━━━━━━━━━━━━━━━━━━━━━
#define DEBUG					(false)
#define DebugMessage			(true)
#define HaveEnemy				(true)

#if DebugMessage
#define MsgBox(message)							MessageBox(NULL, message, NULL, MB_OK)
#define MsgBox_T(message, title)				MessageBox(NULL, message, title, MB_OK)
#else
#define MsgBox(message)
#define MsgBox_T(message, title)
#endif


