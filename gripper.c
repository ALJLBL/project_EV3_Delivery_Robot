#include "ev3api.h"
#include "app.h"
#include "gripper.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif


// グリッパー操作
void gripper(void){

    // グリッパーを制御
    //if ((color_flag == 3 || color_flag == 5) && (line_cor != 3 && line_cor != 5) &&(gripper_flag == 1)) { // カラーセンサーが緑または赤 かつ ラインセンサーが緑または赤ではない かつ グリッパーが開いている場合
    if (status == PICK_UP) {

        ev3_motor_rotate(M_motor, -360*4, 100, 0);  // グリッパーを開く

        // 待機
        tslp_tsk(1500);

        // 前進
        ev3_motor_steer(L_motor, R_motor, 10, 0);

        // 待機
        tslp_tsk(700);

        // 停止
        ev3_motor_stop(L_motor, true);
        ev3_motor_stop(R_motor, true);

        // グリッパーを閉じる
        ev3_motor_rotate(M_motor, 360*4, 50, 0);  

        // 待機
        tslp_tsk(1500);

        ev3_motor_steer(L_motor, R_motor, -10, 0);// バック
        
        tslp_tsk(800);// 待機

        // 状態をGO_YARDに変更
        status = GO_YARD;
    }

    //if (((line_cor == 3 && color_flag == 3) || (line_cor == 5 && color_flag == 5)) && (gripper_flag == 1)) { // ラインセンサーが緑または赤 かつ カラーセンサーが緑または赤 かつ グリッパーが閉じている場合
    if (status == DROP_DOWN) {
        ev3_motor_steer(L_motor, R_motor, -10, 0);// バック
        tslp_tsk(1900);// 待機

        ev3_motor_stop(L_motor, true);// モーター停止
        ev3_motor_stop(R_motor, true);// モーター停止

        // グリッパーを開く
        ev3_motor_rotate(M_motor, -360*4, 100, 0);
        tslp_tsk(1500);// 1500ms待機
        
        ev3_motor_steer(L_motor, R_motor, -10, 0);// バック
        tslp_tsk(700);// 待機
        
        ev3_motor_stop(L_motor, true);// モーター停止
        ev3_motor_stop(R_motor, true);// モーター停止

        // グリッパーを閉じる
        ev3_motor_rotate(M_motor, 360*4, 50, 0);

        tslp_tsk(1500);// 1500ms待機

        // 180度回転
        ev3_motor_set_power(L_motor, -20);
        ev3_motor_set_power(R_motor, 20);
        if (last_color == 3) {
            tslp_tsk(1600);
        }else {
            tslp_tsk(1200);
        }
        

        ev3_motor_stop(L_motor, true);// モーター停止
        ev3_motor_stop(R_motor, true);// モーター停止

        ev3_motor_steer(L_motor, R_motor, -10, 0);// バック
        
        tslp_tsk(400);// 0.4秒待機

        ev3_motor_stop(L_motor, true);// モーター停止
        ev3_motor_stop(R_motor, true);// モーター停止


        // 状態をGO_YARDに変更
        status = GO_HOME;
    }
}
