#ifndef __ENCODER_H
#define __ENCODER_H

#include <stdint.h>

void Encoder_Init_Tim2(void);
void Encoder_Init_Tim4(void);
int Read_Encoder(uint8_t TIMX);

#endif