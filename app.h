#include "target_test.h"

/*
 *  ターゲットに依存する可能性のある定数の定義
 */

#ifndef STACK_SIZE
#define	STACK_SIZE		4096		/* タスクのスタックサイズ */
#endif /* STACK_SIZE */


/*
 *  関数のプロトタイプ宣言
 */
#ifndef TOPPERS_MACRO_ONLY
extern void	main_task(intptr_t exinf);
extern void	run_task(intptr_t exinf);
extern void sensor_task(intptr_t exinf);
#endif /* TOPPERS_MACRO_ONLY */

#ifndef APP_H
#define APP_H

/*
 *  STATUS enumeration definition
 */
typedef enum {
    START_WAIT,
    START,
    GO_STORE,
    PICK_UP,
    GO_YARD,
    DROP_DOWN,
    GO_HOME,
    LOOP_WAIT,
    PARKING,
    ERROR,
    END
} STATUS;

// モーターのポートを設定
#define L_motor		EV3_PORT_B  // 左モーターのポートを設定
#define R_motor		EV3_PORT_C  // 右モーターのポートを設定
#define M_motor		EV3_PORT_A  // 中モーターのポートを設定

// センサーのポートを設定
#define line_sensor		EV3_PORT_4  // ラインセンサーのポートを設定
#define color_sensor	EV3_PORT_3  // カラーセンサーのポートを設定

// グローバル変数
extern int line_cor;  // ラインセンサーの色を格納
extern int color_flag;  // カラーセンサーの色を格納
extern int marker_flag;  // マーカーの状態を格納
extern bool_t gripper_flag;  // グリッパーの状態を格納 0: 開いている 1: 閉じている
extern int line_ref;  // ラインセンサーの反射率を格納
extern int angle;  // M_motorの回転角度を格納
extern STATUS status;  // 状態変数
extern STATUS last_status;  // 最後の状態変数
extern int last_color;  // 最後の荷物の色を格納
extern int stop_count; // 誤検知防止用
extern int stop_count_start;    // 誤検知防止用
extern int last_line_cor;  // 最後のラインセンサーの色を格納
extern int cyc_cnt;  // カウンター
extern int speaker_timer; // スピーカーのタイマー

#endif /* APP_H */
