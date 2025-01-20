#include "ev3api.h"
#include "app.h"
#include "gripper.h"
#include "lcd.h"
#include "wait.h"
#include "linetrace.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

// 状態変数
STATUS status = START_WAIT;
STATUS last_status = START_WAIT;

// グローバル変数
int line_cor;  // ラインセンサーの色を格納
int line_ref;  // ラインセンサーの反射率を格納
int color_flag;  // カラーセンサーの色を格納
int marker_flag;  // マーカーの状態を格納
bool_t gripper_flag = 1;  // グリッパーの状態を格納 0: 開いている 1: 閉じている
int angle;  // M_motorの回転角度を格納
int last_color;  // 最後の荷物の色を格納
int last_line_cor;  // 最後のラインセンサーの色を格納
int stop_count = 0; // 誤検知防止用
int stop_count_start = 0;    // 誤検知防止用
int cyc_cnt = 0;  // カウンター



void run_task(intptr_t unused) {

	// 状態制御
	switch (status) {
	case START_WAIT:
		start_wait();
		gripper_control();
		break;

	case START:
		start();
		break;

	case GO_STORE:
		line_trace();
		gripper_control();
		break;
		
	case PICK_UP:
		gripper();
		gripper_control();
		break;

	case GO_YARD:
		line_trace();
		gripper_control();
		break;

	case DROP_DOWN:
		gripper();
		break;

	case GO_HOME:
		line_trace();
		gripper_control();
		break;

	case LOOP_WAIT:
		loop_wait();
		gripper_control();
		break;

	case PARKING:
		parking();
		break;

	case ERROR:
		error();
		gripper_control();
		break;
	
	case END:
		break;
	}

	// LCDに状態を表示
	display_on_lcd();
}

void sensor_task(intptr_t unused) {

	// ラインセンサーの色を取得
	line_cor = ev3_color_sensor_get_color(line_sensor);

	// ラインセンサーの反射率を取得
	line_ref = ev3_color_sensor_get_reflect(line_sensor);

	// カラーセンサーの色を取得
	color_flag = ev3_color_sensor_get_color(color_sensor);

	// M_motorの回転角度を取得
	angle = ev3_motor_get_counts(M_motor);
	if (ev3_button_is_pressed(BACK_BUTTON)) {
		ev3_motor_reset_counts(M_motor);
	}

	// グリッパーの状態を取得
	if (angle > -100 && angle < 100) {
		gripper_flag = 1; // 閉じている
	} else if (angle > -1540 && angle < -1340) {	
		gripper_flag = 0; // 開いている
	}
	
}

void main_task(intptr_t unused) {
	// モーターの設定
	ev3_motor_config( L_motor , LARGE_MOTOR );  // 左モーターを大モーターとして設定
	ev3_motor_config( R_motor , LARGE_MOTOR );  // 右モーターを大モーターとして設定
	ev3_motor_config( M_motor , MEDIUM_MOTOR ); // 中モーターを中モーターとして設定

	// センサーの設定
	ev3_sensor_config( line_sensor , COLOR_SENSOR );  // ラインセンサーを設定
	ev3_sensor_config( color_sensor , COLOR_SENSOR );  // カラーセンサーを設定

	// タスクを開始する
	ev3_sta_cyc(RUN_TASK);
	ev3_sta_cyc(SENSOR_TASK);
}
