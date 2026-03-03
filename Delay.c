#include "Delay.h"
#include "ti_msp_dl_config.h"

void Delay_Init(void) {
    // 留空即可
}

// 假设 MSPM0G3507 运行在默认的 32MHz 主频1微秒对应 32 个 CPU 时钟周期
void Delay_us(uint32_t us) {
    delay_cycles(32 * us);
}

// 1毫秒对应 32000 个 CPU 时钟周期
void Delay_ms(uint32_t ms) {
    delay_cycles(32000 * ms);
}