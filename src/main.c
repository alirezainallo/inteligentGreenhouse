#include "main.h"
#include "adc.h"
#include "mq5.h"
#include "gsm.h"
#include "key.h"
#include "RTC.h"
#include "menu.h"
#include "uart.h"
#include "DHT11.h"
#include "relay.h"
#include "e2prom.h"
#include "timTick.h"
#include "time_out.h"
#include "heart_beat.h"
#include "keypad_4x4.h"
#include "timerChecker.h"

char display_LCD[17];
const char freeLine[17] = "                ";



int main(void){

  // tim0_init();

  sei(); //enable global interrupt
  
  tim1_init();

  dataBase_init();

  menu_init();

  // uart_init();

  while(1){

    // heart_beat();
    menu_loop();
    keys_loop();
    keypad_process();
    
    adc_loop();
    dht11_loop();
    mq5_loop();
    ldr_loop();
    
    GSM_loop();
    
    RTC_loop();
    timerChecker_loop();
  }
}




