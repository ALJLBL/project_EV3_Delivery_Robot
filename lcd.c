#include "ev3api.h"
#include "app.h"
#include "lcd.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

// LCDに表示する関数
void display_on_lcd() {
	// LCDのフォントサイズを設定
	ev3_lcd_set_font(EV3_FONT_MEDIUM);  // フォントを設定

	char buffer[32];  // 十分な大きさのバッファを用意


	// ステータスを表示
	const char* status_str;
	switch(status) {
		case START_WAIT: status_str = "START_WAIT"; break;
		case START: status_str = "START"; break;
		case GO_STORE: status_str = "GO_STORE"; break;
		case PICK_UP: status_str = "PICK_UP"; break;
		case GO_YARD: status_str = "GO_YARD"; break;
		case DROP_DOWN: status_str = "DROP_DOWN"; break;
		case GO_HOME: status_str = "GO_HOME"; break;
		case LOOP_WAIT: status_str = "LOOP_WAIT"; break;
		case PARKING: status_str = "PARKING"; break;
		case ERROR: status_str = "ERROR"; break;
		case END: status_str = "END"; break;
		default: status_str = "UNKNOWN"; break;
	}
	snprintf(buffer, sizeof(buffer), "Sta: %s", status_str);
	ev3_lcd_draw_string(buffer, 0, 0);

	switch(status) {
		case START_WAIT:
			snprintf(buffer, sizeof(buffer), "Carrying start");
			ev3_lcd_draw_string(buffer, 0, 20);

			snprintf(buffer, sizeof(buffer), "Press center key");
			ev3_lcd_draw_string(buffer, 0, 40);

			// グリッパーの状態を表示
			snprintf(buffer, sizeof(buffer), "grip: %d", gripper_flag);
			ev3_lcd_draw_string(buffer, 0, 60);

			// M_motorの回転角度を表示
			snprintf(buffer, sizeof(buffer), "angle: %08d", angle);
			ev3_lcd_draw_string(buffer, 0, 80);
			break;

		case GO_STORE:
			// 現在のカラーセンサー値を表示
			snprintf(buffer, sizeof(buffer), "fron_col: %02d", color_flag);
			ev3_lcd_draw_string(buffer, 0, 20);

			// ラインセンサー値を表示
			snprintf(buffer, sizeof(buffer), "line_col: %02d", line_cor);
			ev3_lcd_draw_string(buffer, 0, 40);

			// ラインセンサーの反射率を表示
			snprintf(buffer, sizeof(buffer), "line_ref: %03d", line_ref);
			ev3_lcd_draw_string(buffer, 0, 60);

			// グリッパーの状態を表示
			snprintf(buffer, sizeof(buffer), "grip: %d", gripper_flag);
			ev3_lcd_draw_string(buffer, 0, 80);

			// M_motorの回転角度を表示
			snprintf(buffer, sizeof(buffer), "angle: %08d", angle);
			ev3_lcd_draw_string(buffer, 0, 100);
			break;

		case GO_YARD:
			// 現在のカラーセンサー値を表示
			snprintf(buffer, sizeof(buffer), "fron_col: %02d", color_flag);
			ev3_lcd_draw_string(buffer, 0, 20);

			// ラインセンサー値を表示
			snprintf(buffer, sizeof(buffer), "line_col: %02d", line_cor);
			ev3_lcd_draw_string(buffer, 0, 40);

			// ラインセンサーの反射率を表示
			snprintf(buffer, sizeof(buffer), "line_ref: %03d", line_ref);
			ev3_lcd_draw_string(buffer, 0, 60);

			// グリッパーの状態を表示
			snprintf(buffer, sizeof(buffer), "grip: %d", gripper_flag);
			ev3_lcd_draw_string(buffer, 0, 80);

			// M_motorの回転角度を表示
			snprintf(buffer, sizeof(buffer), "angle: %08d", angle);
			ev3_lcd_draw_string(buffer, 0, 100);
			break;

		case PICK_UP:
			// 現在のカラーセンサー値を表示
			snprintf(buffer, sizeof(buffer), "fron_col: %02d", color_flag);
			ev3_lcd_draw_string(buffer, 0, 20);

			// ラインセンサー値を表示
			snprintf(buffer, sizeof(buffer), "line_col: %02d", line_cor);
			ev3_lcd_draw_string(buffer, 0, 40);

			// ラインセンサーの反射率を表示
			snprintf(buffer, sizeof(buffer), "line_ref: %03d", line_ref);
			ev3_lcd_draw_string(buffer, 0, 60);

			// グリッパーの状態を表示
			snprintf(buffer, sizeof(buffer), "grip: %d", gripper_flag);
			ev3_lcd_draw_string(buffer, 0, 80);

			// M_motorの回転角度を表示
			snprintf(buffer, sizeof(buffer), "angle: %08d", angle);
			ev3_lcd_draw_string(buffer, 0, 100);
			break;

		case DROP_DOWN:
			// 現在のカラーセンサー値を表示
			snprintf(buffer, sizeof(buffer), "fron_col: %02d", color_flag);
			ev3_lcd_draw_string(buffer, 0, 20);

			// ラインセンサー値を表示
			snprintf(buffer, sizeof(buffer), "line_col: %02d", line_cor);
			ev3_lcd_draw_string(buffer, 0, 40);

			// ラインセンサーの反射率を表示
			snprintf(buffer, sizeof(buffer), "line_ref: %03d", line_ref);
			ev3_lcd_draw_string(buffer, 0, 60);

			// グリッパーの状態を表示
			snprintf(buffer, sizeof(buffer), "grip: %d", gripper_flag);
			ev3_lcd_draw_string(buffer, 0, 80);

			// M_motorの回転角度を表示
			snprintf(buffer, sizeof(buffer), "angle: %08d", angle);
			ev3_lcd_draw_string(buffer, 0, 100);
			break;

		case GO_HOME:
			// 現在のカラーセンサー値を表示
			snprintf(buffer, sizeof(buffer), "fron_col: %02d", color_flag);
			ev3_lcd_draw_string(buffer, 0, 20);

			// ラインセンサー値を表示
			snprintf(buffer, sizeof(buffer), "line_col: %02d", line_cor);
			ev3_lcd_draw_string(buffer, 0, 40);

			// ラインセンサーの反射率を表示
			snprintf(buffer, sizeof(buffer), "line_ref: %03d", line_ref);
			ev3_lcd_draw_string(buffer, 0, 60);

			// グリッパーの状態を表示
			snprintf(buffer, sizeof(buffer), "grip: %d", gripper_flag);
			ev3_lcd_draw_string(buffer, 0, 80);

			// M_motorの回転角度を表示
			snprintf(buffer, sizeof(buffer), "angle: %08d", angle);
			ev3_lcd_draw_string(buffer, 0, 100);
			break;

		case LOOP_WAIT:
			snprintf(buffer, sizeof(buffer), "One More Carrying?");
			ev3_lcd_draw_string(buffer, 0, 20);

			snprintf(buffer, sizeof(buffer), "Yes -> Press Left Key");
			ev3_lcd_draw_string(buffer, 0, 40);

			snprintf(buffer, sizeof(buffer), "No -> Press Right Key");
			ev3_lcd_draw_string(buffer, 0, 60);
			break;

		case PARKING:
			snprintf(buffer, sizeof(buffer), "Now Parking...");
			ev3_lcd_draw_string(buffer, 0, 20);
			break;

		case ERROR:
			snprintf(buffer, sizeof(buffer), "Error Occured!!!!");
			ev3_lcd_draw_string(buffer, 0, 20);
			break;

	}

	// // 現在のカラーセンサー値を表示
	// snprintf(buffer, sizeof(buffer), "color_sensor: %02d", color_flag);
	// ev3_lcd_draw_string(buffer, 0, 20);

	// // ラインセンサー値を表示
	// snprintf(buffer, sizeof(buffer), "line_col: %02d", line_cor);
	// ev3_lcd_draw_string(buffer, 0, 40);

	// // ラインセンサーの反射率を表示
	// snprintf(buffer, sizeof(buffer), "line_ref: %03d", line_ref);
	// ev3_lcd_draw_string(buffer, 0, 60);

	// // グリッパーの状態を表示
	// snprintf(buffer, sizeof(buffer), "grip: %d", gripper_flag);
	// ev3_lcd_draw_string(buffer, 0, 80);

	// // M_motorの回転角度を表示
	// snprintf(buffer, sizeof(buffer), "angle: %08d", angle);
	// ev3_lcd_draw_string(buffer, 0, 100);
}
