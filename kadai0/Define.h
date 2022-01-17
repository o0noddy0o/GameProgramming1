#pragma once

//━━━━━━━━━━━━━━━━━━━━━━━
// 潜水艦
//━━━━━━━━━━━━━━━━━━━━━━━
#define SUBMARINE_MAX_HP			(200.f)
#define SUBMARINE_MOVE_SPEED		(400.f)
#define SUBMARINE_SIZE_X			(384.f)
#define SUBMARINE_SIZE_Y			(384.f)
#define NUM_OF_OPERATION_DEVICE		(5)
#define NUM_OF_COMPONENT			(6)


#define SCREEN_MULTIPLE_X			(3.f)
#define SCREEN_MULTIPLE_Y			(4.f)

#define GRAVITATION					(5.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// プレイヤー
//━━━━━━━━━━━━━━━━━━━━━━━
#define PLAYER_SIZE_X				(40.f)
#define PLAYER_SIZE_Y				(52.f)
#define PLAYER_MOVE_SPEED			(200.f)
#define PLAYER_JUMP_POWER			(15.f)
#define PLAYER_JUMP_SPEED			(20.f)
#define PLAYER_FALLING_SPEED_LIMIT	(20.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// 敵
//━━━━━━━━━━━━━━━━━━━━━━━
#define ENEMY_1_SIZE_X				(90.f)
#define ENEMY_1_SIZE_Y				(32.8f)
#define ENEMY_1_MOVE_SPEED			(100.f)

#define ENEMY_2_SIZE_X				(80.f)
#define ENEMY_2_SIZE_Y				(40.f)
#define ENEMY_2_MOVE_SPEED			(250.f)

#define ELECTRICEEL_SIZE_X			(311.f)
#define ELECTRICEEL_SIZE_Y			(162.f)
#define ELECTRICEEL_SIZE			(XMFLOAT2(ELECTRICEEL_SIZE_X, ELECTRICEEL_SIZE_Y))
#define ELECTRICEEL_MOVE_SPEED		(120.f)
#define ELECTRICEEL_TURRET_COOL_DOWN (30)

#define MISSILELAUNCHER_HEAD_SIZE_X				(50.f)
#define MISSILELAUNCHER_HEAD_SIZE_Y				(50.f)
#define MISSILELAUNCHER_PEDESTAL_SIZE_X			(50.f)
#define MISSILELAUNCHER_PEDESTAL_SIZE_Y			(30.f)
#define MISSILELAUNCHER_HEAD_PEDESTAL_INTERVAL	(40.f)
#define MISSILELAUNCHER_MAX_ROTATE_SPEED		(3.f)
#define MISSILELAUNCHER_MIN_ATTACK_INTERVAL		(30)

//━━━━━━━━━━━━━━━━━━━━━━━
// タレット
//━━━━━━━━━━━━━━━━━━━━━━━
#define TURRET_DISTANCE				(250.f)
#define TURRET_SIZE_X				(40.f)
#define TURRET_SIZE_Y				(30.f)
#define TURRET_ROTATION_SPEED		(200.f)
#define TURRET_ROTATION_RANGE		(180.f)
#define TURRET_COOL_DOWN			(0.1f)

//━━━━━━━━━━━━━━━━━━━━━━━
// 床
//━━━━━━━━━━━━━━━━━━━━━━━
#define YUKA_POSITION				(-30.f)

//━━━━━━━━━━━━━━━━━━━━━━━
// 壁
//━━━━━━━━━━━━━━━━━━━━━━━
#define WALL_1_SIZE_X				(128.f)
#define WALL_1_SIZE_Y				(142.f)
#define WALL_1_X					(110.f)
#define WALL_1_Y					(110.f)

#define WALL_2_SIZE_X				(128.f)
#define WALL_2_SIZE_Y				(142.f)
#define WALL_2_X					(-110.f)
#define WALL_2_Y					(110.f)

#define WALL_3_SIZE_X				(128.f)
#define WALL_3_SIZE_Y				(142.f)
#define WALL_3_X					(-110.f)
#define WALL_3_Y					(-110.f)

#define WALL_4_SIZE_X				(128.f)
#define WALL_4_SIZE_Y				(142.f)
#define WALL_4_X					(110.f)
#define WALL_4_Y					(-110.f)

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
#define ENEMY_BULLET_SIZE		(XMFLOAT2(ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y))
#define ENEMY_BULLET_MOVE_SPEED	(600.f)
#define ENEMY_BULLET_BOUNDING_BOX_RADIUS	(10.f)

#define ELECTRICEEL_BULLET_SIZE_X				(10.f)
#define ELECTRICEEL_BULLET_SIZE_Y				(20.f)
#define ELECTRICEEL_BULLET_MOVE_SPEED			(1500.f)
#define ELECTRICEEL_BULLET_BOUNDING_BOX_RADIUS	(10.f)

#define MISSILE_SIZE_X				(50.f)
#define MISSILE_SIZE_Y				(20.f)
#define MISSILE_MOVE_SPEED			(1500.f)
#define MISSILE_MAX_ROTATE_SPEED	(30.f)

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
#define Block_X_SIZE			(3200.f)
#define Block_Y_SIZE			(1500.f)

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
#define MAX_ENEMY_NUM			(20)

//━━━━━━━━━━━━━━━━━━━━━━━
// ダメージ
//━━━━━━━━━━━━━━━━━━━━━━━
#define DAMAGE_WHEN_ENEMY_HIT_SUBMARINE			(0.1f)
#define DAMAGE_WHEN_ENEMY_BULLET_HIT_SUBMARINE	(0.1f)
#define DAMAGE_WHEN_SUBMARINE_HIT_SCENERYOBJECT	(0.1f)

//━━━━━━━━━━━━━━━━━━━━━━━
// カメラ
//━━━━━━━━━━━━━━━━━━━━━━━
#define PERCENNTAGE_OF_CAMERA_MOVE_TO_SUBMARINNE	(0.30f)			

//━━━━━━━━━━━━━━━━━━━━━━━
// 描画用の色
//━━━━━━━━━━━━━━━━━━━━━━━
#define COLOR_RED		(XMFLOAT4(1.f, 0.f, 0.f, 1.f))
#define COLOR_YELLOW	(XMFLOAT4(1.f, (241.f / 255.f), 0.f, 1.f))
#define COLOR_GREEN		(XMFLOAT4(0.f, 1.f, 0.f, 1.f))

//━━━━━━━━━━━━━━━━━━━━━━━
// ゲームパッド入力用（学校のゲームパッド）
//━━━━━━━━━━━━━━━━━━━━━━━
#define GAMEPAD_A		(0)
#define GAMEPAD_B		(1)
#define GAMEPAD_X		(2)
#define GAMEPAD_Y		(3)
#define GAMEPAD_LB		(4)
#define GAMEPAD_RB		(5)
#define GAMEPAD_BACK	(6)
#define GAMEPAD_START	(7)
#define GAMEPAD_L3		(8)	// 左スティックを押し込む
#define GAMEPAD_R3		(9)	// 右スティックを押し込む

#define GAMEPAD_KEY_Action					(GAMEPAD_A)
#define GAMEPAD_KEY_UseOperationDevice		(GAMEPAD_B)

//━━━━━━━━━━━━━━━━━━━━━━━
// 計算用
//━━━━━━━━━━━━━━━━━━━━━━━
// π
#define PI															((float)(3.1415926535))
// 絶対値
#define Abs(x)														(((x) >= 0)?(x):(-x))
// ラジアン角を角度にする
#define RadianToDegree(x)											((x) * 180.f / PI)
// 角度をラジアン角にする
#define DegreeToRadian(x)											((x) * PI / 180.f)
// 角度で単位ベクトルを求める
#define AngleToDirectionVector(_angle)								{ cosf(DegreeToRadian(_angle)) , sinf(DegreeToRadian(_angle)) }
// 角度をプラス且つ360以内にする 
#define Degree(_angle)												((float)((_angle >= 0.f)?((int)(_angle) % 360):((360 + ((int)(_angle) % 360)))))
// ベクトルの大きさを求める
#define FindDistanceByCoordinateDifference(_coordinateDifference)	(sqrtf((_coordinateDifference).x * (_coordinateDifference).x + (_coordinateDifference).y * (_coordinateDifference).y))
// ベクトルを正規化する
#define NormalizeVector(_vector)									{ float mag = FindDistanceByCoordinateDifference(_vector); _vector.x /= mag; _vector.y /= mag; }		
// 内積
#define CrossProduct(_vector1, _vector2)							((_vector1.x) * (_vector2.y) - (_vector1.y) * (_vector2.x))
// 座標二つでベクトルを求める
#define FindVectorByTwoPos(_pos1, _pos2)							{ _pos2.x - _pos1.x, _pos2.y - _pos1.y }
// ベクトルを回転する
#define VectorRotation(_vector, _angle)								{ XMFLOAT2 result = {(_vector.x * cosf(DegreeToRadian(_angle)) - _vector.y * sinf(DegreeToRadian(_angle))), _vector.x * sinf(DegreeToRadian(_angle)) + _vector.y * cosf(DegreeToRadian(_angle))}; _vector = result; }

//━━━━━━━━━━━━━━━━━━━━━━━
// デバッグ・確認用
//━━━━━━━━━━━━━━━━━━━━━━━
#define DEBUG					(true)
#define HaveEnemy				(true)
#define ShowGamePadInput		(false)

#define DebugMessage			(false)
#if DebugMessage
#define MsgBox(message)							MessageBox(NULL, message, NULL, MB_OK)
#define MsgBox_T(message, title)				MessageBox(NULL, message, title, MB_OK)
#else
#define MsgBox(message)
#define MsgBox_T(message, title)
#endif

#define ShowDeltaTimeAndFPS			(false)
#if ShowDeltaTimeAndFPS
#define DeltaTimeText_Pos_X	(-940.f)
#define DeltaTimeText_Pos_Y	(460.f)
#define DeltaTimeText_Pos	(XMFLOAT2(DeltaTimeText_Pos_X, DeltaTimeText_Pos_Y))
#endif