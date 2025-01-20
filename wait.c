#include "ev3api.h"
#include "app.h"
#include "wait.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

void start_wait() {
    if(ev3_button_is_pressed(ENTER_BUTTON)){
        // 通知音を鳴らす
        ev3_speaker_play_tone(NOTE_C4, 500);
        // 画面をクリア
        ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
        tslp_tsk(5);
        status = START;
    }
}

void loop_wait() {
    if(ev3_button_is_pressed(LEFT_BUTTON)){ // 左ボタンが押されたら
        ev3_speaker_play_tone(NOTE_C4, 500);
        ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
        tslp_tsk(5);
        status = GO_STORE;
    }else if(ev3_button_is_pressed(RIGHT_BUTTON)){  // 右ボタンが押されたら
        ev3_speaker_play_tone(NOTE_C4, 500);
        tslp_tsk(1000);
        ev3_speaker_play_tone(NOTE_C4, 500);
        ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
        tslp_tsk(5);
        status = PARKING;

    }else{
        //30秒経過後自動で戻る
        /*ev3_speaker_play_tone(NOTE_C4, 500);
        tslp_tsk(5);
        ev3_speaker_play_tone(NOTE_C4, 500);
        ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
        tslp_tsk(5);
        state = PARKING;*/

    };
}

void parking() {

	if(last_color == 3){
		//最後の荷物がGREENなら右回転して下がる
        ev3_motor_steer(L_motor, R_motor, 10, 0);// 少し前進
        
        tslp_tsk(200);// 0.2秒待機

        ev3_motor_stop(R_motor, true);
	    ev3_motor_stop(L_motor, true);
		ev3_motor_rotate(L_motor, 150, 30, true);
		ev3_motor_rotate(R_motor, -150, 30, true);
		tslp_tsk(250);
		
	}else if(last_color == 5){
		//最後の荷物がREDなら左回転して下がる
		ev3_motor_rotate(L_motor, -150, 30, true);
		ev3_motor_rotate(R_motor, 150, 30, true);
		tslp_tsk(200);
	}else {
        //最後の荷物がGREENなら右回転して下がる
        ev3_motor_steer(L_motor, R_motor, 10, 0);// 少し前進
        
        tslp_tsk(200);// 0.2秒待機

        ev3_motor_stop(R_motor, true);
	    ev3_motor_stop(L_motor, true);

		ev3_motor_rotate(L_motor, 150, 30, true);
		ev3_motor_rotate(R_motor, -150, 30, true);
		tslp_tsk(250);
    }
	
	ev3_motor_stop(R_motor, true);
	ev3_motor_stop(L_motor, true);

	tslp_tsk(200);

	ev3_speaker_play_tone(NOTE_C4, 500);
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);

	ev3_motor_steer(L_motor,R_motor,-20,0); //バック

	tslp_tsk(1200);

	ev3_motor_stop(R_motor, true);
	ev3_motor_stop(L_motor, true);
	tslp_tsk(5);

	status = START_WAIT;
		
}

void start() {
	int power = 20; 
	int now_val = 0;
	int now_color = 0;
	
	const int threshold = 42;
	
	ev3_motor_reset_counts(L_motor);
	ev3_motor_reset_counts(R_motor);

    now_val = line_ref;
    now_color = line_cor;

    if (now_val < threshold && now_color == 2) { // 黒を検出
        stop_count_start++;
    } else {
        stop_count_start = 0; // リセット
    }


    if (stop_count_start == 3) { // 停止条件
        ev3_motor_stop(L_motor, true);
        ev3_motor_stop(R_motor, true);

        ev3_motor_rotate(R_motor, 150, 30, true);
        stop_count_start = 0;

        ev3_motor_steer(L_motor, R_motor, 10, 0);
        tslp_tsk(200);
        ev3_motor_stop(L_motor, true);
        ev3_motor_stop(R_motor, true);

        status = GO_STORE;
        return;
        
    } else {
        ev3_motor_steer(L_motor, R_motor, power, 0 );
    }
		
		
	
}

void error() {
    ev3_motor_stop(L_motor, true);
    ev3_motor_stop(R_motor, true);
    ev3_motor_stop(M_motor, true);
    ev3_speaker_set_volume(20);
    ev3_speaker_play_tone(NOTE_C4, 500);

    // UP / DOWN _BUTTONが押されるとグリッパーを動作させる
    if (ev3_button_is_pressed(UP_BUTTON)) {
        ev3_motor_rotate(M_motor, 20, 100, 0);  // グリッパーを閉じる
    }
    if (ev3_button_is_pressed(DOWN_BUTTON)) {
        ev3_motor_rotate(M_motor, -20, 100, 0);  // グリッパーを開く
    }

    if (ev3_button_is_pressed(BACK_BUTTON)) {
        status = GO_HOME;
    } else if (ev3_button_is_pressed(ENTER_BUTTON)) {
        status = last_status;
    }
}

void gripper_control() {
    if (ev3_button_is_pressed(UP_BUTTON)) {
        ev3_motor_rotate(M_motor, 20, 100, 0);  // グリッパーを閉じる
    }
    if (ev3_button_is_pressed(DOWN_BUTTON)) {
        ev3_motor_rotate(M_motor, -20, 100, 0);  // グリッパーを開く
    }
    if (ev3_button_is_pressed(BACK_BUTTON)) {   // リセット
        ev3_motor_reset_counts(M_motor);
    }
}

