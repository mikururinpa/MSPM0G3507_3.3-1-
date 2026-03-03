#ifndef __KEY_H
#define __KEY_H
#include <stdint.h>
#include "ti_msp_dl_config.h"

// 宏定义读取四个按键引脚的状态 (高电平返回1，低电平返回0)
#define KEY0  (DL_GPIO_readPins(KEY_PORT_PORT, KEY_PORT_K0_PIN) ? 1 : 0)
#define KEY1  (DL_GPIO_readPins(KEY_PORT_PORT, KEY_PORT_K1_PIN) ? 1 : 0)
#define KEY2  (DL_GPIO_readPins(KEY_PORT_PORT, KEY_PORT_K2_PIN) ? 1 : 0)
#define KEY3  (DL_GPIO_readPins(KEY_PORT_PORT, KEY_PORT_K3_PIN) ? 1 : 0)

void key_init(void);
#endif
