#include "ev3api.h"
#include "app.h"
#include "linetrace.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif


// ライントレース処理の実装
void line_trace() {

    int turn=0;
    // int B=45; //turn to power
    // int W=45;
    int power=18; 
    int now_val=0;      // ラインセンサーの反射率
    int now_color =0;   // ラインセンサーの色
    int front_color =0; // カラーセンサーの色
    float p = 1.4;

    const int threshold = 42;

    now_val = line_ref;
    now_color = line_cor;
    front_color= color_flag;


    if (status == GO_STORE) {

        if (now_color == 2) {   // 青を検出
            cyc_cnt++;
        }else{
            cyc_cnt = 0;
        }
        if (cyc_cnt > 6) { //stop
            tslp_tsk(10);//待機
            power=0;
            turn=0;
            cyc_cnt = 0;
            // ラインセンサーが再び青が検知された場合
            if (ev3_color_sensor_get_color(line_sensor) == 2) {
                status = PARKING;
            }// ラインセンサーが青以外を検知した場合は　==> 何もしない
        }
        

        //  カラーセンサーが緑か赤
        if ((front_color == 3 || front_color == 5)) { // カラーセンサーが緑または赤 かつ ラインセンサーが緑または赤ではない かつ グリッパーが閉じている場合
            stop_count++;
        } else {
            stop_count = 0; // リセット
        }

        if (stop_count == 1) { // 停止条件
            power = 0;
            turn = 0;
            stop_count = 0;
            last_color = front_color;
            status = PICK_UP; // i think here
        } else {
            if (now_val < threshold) {
                turn = p * (now_val - threshold); // P制御
            } else {
                turn = p * (now_val - threshold); // P制御
            }
        }

        // ラインセンサーが緑または赤を検出した場合,直進する
        if(now_color == 5 || now_color == 3){
            turn = 0;
        }
    }

    if (status == GO_YARD) {
        // カラーセンサーが緑また赤を未検出
        if (front_color != 3 && front_color != 5) {
            stop_count++;
        }else {
            stop_count = 0; // リセット
        }
        if (stop_count > 10) { // カウンターが3になり、緑または赤を未検出
            power = 0;
            turn = 0;
            stop_count = 0;
            last_status = status;   // 状態を保存
            status = ERROR;         // エラー状態に遷移
            return;
        }

        // ラインセンサーが最後の荷物の色を検出
        if (now_color == last_color) {
            cyc_cnt++;
        } else {
            cyc_cnt = 0;    // リセット
        }

        // カウンターが3になり、緑または赤を検出
        if (cyc_cnt == 3 && (front_color == 3 || front_color == 5)) {
            ev3_motor_stop(L_motor, true);
            ev3_motor_stop(R_motor, true);
            tslp_tsk(500);
            ev3_motor_steer(L_motor, R_motor, -10, 0);
            tslp_tsk(200);
            power = 0;
            turn = 0;
            cyc_cnt = 0;
            // ラインセンサーが再び青が検知された場合
            if ((ev3_color_sensor_get_color(line_sensor) == 3) || (ev3_color_sensor_get_color(line_sensor) == 5)) {
                status = DROP_DOWN;
            }// ラインセンサーが緑また赤以外を検知した場合は　==> 何もしない
        
        }else {
            if (now_val < threshold) {
                turn = p * (now_val - threshold); // P制御
            } else {
                turn = p * (now_val - threshold); // P制御
            }
        }
    }

    if (status == GO_HOME) {
        if (now_color == 2) {
            stop_count++;
        } else {
            stop_count = 0; // リセット
        }

        if (stop_count > 6) { // 停止条件
            ev3_motor_stop(L_motor, true);
            ev3_motor_stop(R_motor, true);
            tslp_tsk(500);
            ev3_motor_steer(L_motor, R_motor, -10, 0);
            tslp_tsk(200);
            power = 0;
            turn = 0;
            stop_count = 0;
            // ラインセンサーが再び青が検知された場合
            if (ev3_color_sensor_get_color(line_sensor) == 2) {
                status = LOOP_WAIT;
            }// ラインセンサーが青以外を検知した場合は　==> 何もしない
        
        } else {
            if (now_val < threshold) {
                turn = p * (now_val - threshold); // P制御
            } else {
                turn = p * (now_val - threshold); // P制御
            }
        }
    }

    ev3_motor_steer(L_motor, R_motor, power, turn);
}