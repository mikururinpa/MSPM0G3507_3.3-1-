#include "ti_msp_dl_config.h" // 必须放在第一行
#include "Delay.h"
#include "Motor.h"
#include "PWM.h"
#include "sensor.h"
#include "Encoder.h"
#include "Key.h"
#include "oled_hardware_i2c.h" // 刚才替换的新 OLED 头文件
#include "line.h"
#include "menu.h"

// 全局 10ms 计时变量 (跑图逻辑和测速全靠它)
volatile uint32_t time = 0; 

// ==========================================
// 10ms 定时器中断服务函数
// ==========================================
void TIMG0_IRQHandler(void) {
    switch (DL_TimerG_getPendingInterrupt(TIMER_10MS_INST)) {
        case DL_TIMER_IIDX_ZERO:
            time++;  // 每10ms进入一次时间加1
            break;
        default:
            break;
    }
}

// ==========================================
// 主函数
// ==========================================
int main(void) {
    // 1. 初始化底层硬件 (SysConfig 自动生成，代替了原来一万行的 GPIO/TIM Init)
    SYSCFG_DL_init();

    // 2. 开启中断响应 (极度重要！)
    NVIC_EnableIRQ(TIMER_10MS_INST_INT_IRQN);  // 开启 10ms 定时器中断
    NVIC_EnableIRQ(GPIO_ENCODER_R_INT_IRQN);   // 开启右轮编码器(GPIO)中断

    // 3. 应用层模块初始化
    Delay_Init();
    Motor_Init();
    OLED_Init();  // 调用硬件 IIC 库的初始化函数
    Menu_Init();  // 初始化菜单光标状态

    // 4. 进入死循环
    while (1) {
        // 第一步：运行菜单界面，等待用户设置速度、圈数并按下启动键
        Menu_Run(); 
        
        // 第二步：用户在菜单里按了确认，退出菜单，开始跑图！
        if (Map_Selection == 1) {
            Run_Square_Map(Loop_Target); // 跑正方形地图
        } 
        else if (Map_Selection == 2) {
            Run_Normal_Map(Loop_Target); // 跑普通赛道
        }
        
        // 第三步：小车跑完目标圈数并停下后，重置菜单状态，准备下一次发车
        Menu_Init();
    }
}