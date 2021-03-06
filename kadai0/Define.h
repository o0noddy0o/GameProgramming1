#pragma once

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦
//━━━━━━━━━━━━━━━━━━━━━━━
#define SUBMARINE_MAX_HP			(200.f)
#define SUBMARINE_MOVE_SPEED		(600.f)
#define SUBMARINE_SIZE_X			(384.f)
#define SUBMARINE_SIZE_Y			(384.f)
#define NUM_OF_OPERATION_DEVICE		(5)
#define NUM_OF_COMPONENT			(6)

#define GRAVITATION					(5.f)
 
//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤー１
//━━━━━━━━━━━━━━━━━━━━━━━
#define PLAYER_1_SIZE_X				(40.f)
#define PLAYER_1_SIZE_Y				(52.f)
#define PLAYER_1_MOVE_SPEED			(200.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤー２
//━━━━━━━━━━━━━━━━━━━━━━━
#define PLAYER_2_SIZE_X				(40.f)
#define PLAYER_2_SIZE_Y				(52.f)
#define PLAYER_2_MOVE_SPEED			(200.f)

#define YUKA_POSITION				(30.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵
//━━━━━━━━━━━━━━━━━━━━━━━
#define ENEMY_1_SIZE_X				(90.f)
#define ENEMY_1_SIZE_Y				(32.8f)
#define ENEMY_1_MOVE_SPEED			(200.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// タレット
//━━━━━━━━━━━━━━━━━━━━━━━
#define TURRET_DISTANCE				(300.f)
#define TURRET_SIZE_X				(40.f)
#define TURRET_SIZE_Y				(30.f)
#define TURRET_ROTATION_SPEED		(200.f)
#define TURRET_ROTATION_RANGE		(180.f)
#define TURRET_COOL_DOWN			(0)

//━━━━━━━━━━━━━━━━━━━━━━━
// 床
//━━━━━━━━━━━━━━━━━━━━━━━
#define YUKA_POSITION				(30.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// 壁
//━━━━━━━━━━━━━━━━━━━━━━━
#define WALL_1_SIZE_X				(128.f)
#define WALL_1_SIZE_Y				(142.f)
#define WALL_1_X					(110.f)
#define WALL_1_Y					(110.f)

#define WALL_2_SIZE_X				(128.f)
#define WALL_2_SIZE_Y				(142.f)
#define WALL_2_X					(110.f)
#define WALL_2_Y					(110.f)

#define WALL_3_SIZE_X				(128.f)
#define WALL_3_SIZE_Y				(142.f)
#define WALL_3_X					(110.f)
#define WALL_3_Y					(110.f)

#define WALL_4_SIZE_X				(128.f)
#define WALL_4_SIZE_Y				(142.f)
#define WALL_4_X					(110.f)
#define WALL_4_Y					(110.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// 弾
//━━━━━━━━━━━━━━━━━━━━━━━
#define BULLET_SIZE_X		(15.f)
#define BULLET_SIZE_Y		(15.f)
#define BULLET_MOVE_SPEED	(1000.f)
#define BULLET_BOUNDING_BOX_RADIUS	(10.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵の弾
//━━━━━━━━━━━━━━━━━━━━━━━
#define ENEMY_BULLET_SIZE_X		(15.f)
#define ENEMY_BULLET_SIZE_Y		(15.f)
#define ENEMY_BULLET_MOVE_SPEED	(600.f)
#define ENEMY_BULLET_BOUNDING_BOX_RADIUS	(10.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// ジェットエンジン
//━━━━━━━━━━━━━━━━━━━━━━━
#define JET_ENGINE_SIZE_X			(600.f)
#define JET_ENGINE_SIZE_Y			(384.f)
#define JET_ENGINE_ROTATION_SPEED	(300.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// バリア
//━━━━━━━━━━━━━━━━━━━━━━━
#define BARRIER_SIZE_X			(6.f)
#define BARRIER_SIZE_Y			(6.f)
#define BARRIER_RANGE			(90.f)
#define BARRIER_ROTATION_SPEED	(300.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// マップサイズ
//━━━━━━━━━━━━━━━━━━━━━━━
#define Map_X_SIZE				(19)
#define Map_Y_SIZE				(24)
#define Block_X_SIZE			(60.f)
#define Block_Y_SIZE			(60.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// UI
//━━━━━━━━━━━━━━━━━━━━━━━
#define HP_BAR_RELATIVE_POS_X	(-750.f)
#define HP_BAR_RELATIVE_POS_Y	( 500.f)
#define HP_BAR_RELATIVE_POS		(XMFLOAT2(HP_BAR_RELATIVE_POS_X, HP_BAR_RELATIVE_POS_Y))
#define HP_BAR_SIZE_X			(400.f)
#define HP_BAR_SIZE_Y			(40.f)
#define HP_BAR_FREAM_SIZE_X		(HP_BAR_SIZE_X + 4.f)
#define HP_BAR_FREAM_SIZE_Y		(HP_BAR_SIZE_Y + 4.f)
#define MAP_RELATIVE_POS_X		(0.f)
#define MAP_RELATIVE_POS_Y		(0.f)
#define MAP_RELATIVE_POS		(XMFLOAT2(MAP_RELATIVE_POS_X, MAP_RELATIVE_POS_Y))
#define ENEMY_NUM_POS_X			(-66.f)
#define ENEMY_NUM_POS_Y			(500.f)
#define ENEMY_NUM_POS			(XMFLOAT2(ENEMY_NUM_POS_X, ENEMY_NUM_POS_Y))
#define MAX_ENEMY_NUM			(50)

//━━━━━━━━━━━━━━━━━━━━━━━
// ダメージ
//━━━━━━━━━━━━━━━━━━━━━━━
#define DAMAGE_WHEN_ENEMY_HIT_SUBMARINE			(0.1f)
#define DAMAGE_WHEN_ENEMY_BULLET_HIT_SUBMARINE	(0.1f)

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
#define DEBUG					(true)
#define HaveEnemy				(true)

#define DebugMessage			(true)
#if DebugMessage
#define MsgBox(message)							MessageBox(NULL, message, NULL, MB_OK)
#define MsgBox_T(message, title)				MessageBox(NULL, message, title, MB_OK)
#else
#define MsgBox(message)
#define MsgBox_T(message, title)
#endif

#define ShowDeltaTimeAndFPS			(true)
#if ShowDeltaTimeAndFPS
#define DeltaTimeText_Pos_X	(-940.f)
#define DeltaTimeText_Pos_Y	(460.f)
#define DeltaTimeText_Pos	(XMFLOAT2(DeltaTimeText_Pos_X, DeltaTimeText_Pos_Y))
#endif