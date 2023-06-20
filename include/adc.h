#ifndef _ADC_H
#define _ADC_H

#include "main.h"
#include "timTick.h"

typedef enum{
  adc_ch_Idle = 0x00, 
  adc_ch4 = 0x04,
  adc_ch5 = 0x05,
}adc_channels_t;

void adc_init(uint32_t ms);
void adc_start(adc_channels_t ch);
uint16_t get_adc_value(adc_channels_t ch);
void adc_loop(void);

#endif //_ADC_H
