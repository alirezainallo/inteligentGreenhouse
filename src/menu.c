#include "menu.h"

SetUpDataBaseStep_t SetUpDataBaseStep = SetUpDataBase_MIN;
setUp_t tmpSetUpDataBase;
dataBaseSec_t setUpDataBase_stat = SEC_HUMIDITY;

// char display_LCD[17];
static uint32_t pageInitTick = 0;
menuStat_t menuStat = menu_mainPage;

void menu_init(void){
    // LCD_Clear();
    set_menu(menu_starting);
}
menuStat_t get_menuStat(void){
    return menuStat;
}
void set_menu(menuStat_t menu){
    menuStat = menu;
    menu_initPage(menu);
}
const char S_min[] = "Enter %s min:";
const char S_max[] = "Enter %s max:";
const char S_time[] = "Enter %s time:";
const char S_HR[] = "HR";
const char S_CO2[] = "CO2";
const char S_Temp[] = "T";
const char S_LIGHT[] = "L";
const char S_Watering[] = "W";
const char S_Fertilizing[] = "F";
void menu_initPage(menuStat_t stat){
    LCD_Clear();

    switch(stat){
        case menu_starting:
            adc_init(200);
            ldr_init(300);
            mq5_init(400);
            dht11_init(450);
            
            keypad_init(FALLING_EDGE);
            
            LCD_Init();

            heart_beat_init(500);


            // RTC_Init();
            
            LCD_String_xy(0, 0, "Starting...");
            pageInitTick = get_currentTick();
            
            GSM_init();
            // GSM_sendSMS("09035683914", strlen("09035683914"), "Starting...", strlen("Starting..."));
            break;
        case menu_getSetUpForFirst:
            switch (setUpDataBase_stat)
            {
                case SEC_HUMIDITY:
                    switch (SetUpDataBaseStep)
                    {
                        case SetUpDataBase_MIN:
                            sprintf(display_LCD, S_min, S_HR);
                            LCD_String_xy(0, 0, display_LCD);
                            break;
                        case SetUpDataBase_MAX:
                            sprintf(display_LCD, S_max, S_HR);
                            LCD_String_xy(0, 0, display_LCD);
                            break;
                        case SetUpDataBase_TIME:
                            sprintf(display_LCD, S_time, S_HR);
                            LCD_String_xy(0, 0, display_LCD);
                            sprintf(display_LCD, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
                            LCD_String_xy(1, 0, display_LCD);
                            break;
                        default:
                            break;
                    }
                    break;
                case SEC_TEMP:
                    switch (SetUpDataBaseStep)
                    {
                        case SetUpDataBase_MIN:
                            sprintf(display_LCD, S_min, S_Temp);
                            LCD_String_xy(0, 0, display_LCD);
                            break;
                        case SetUpDataBase_MAX:
                            sprintf(display_LCD, S_max, S_Temp);
                            LCD_String_xy(0, 0, display_LCD);
                            break;
                        case SetUpDataBase_TIME:
                            sprintf(display_LCD, S_time, S_Temp);
                            LCD_String_xy(0, 0, display_LCD);
                            sprintf(display_LCD, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
                            LCD_String_xy(1, 0, display_LCD);
                            break;
                        default:
                            break;
                    }
                    break;
                case SEC_CO2:
                    switch (SetUpDataBaseStep)
                    {
                        case SetUpDataBase_MIN:
                            break;
                        case SetUpDataBase_MAX:
                            sprintf(display_LCD, S_max, S_CO2);
                            LCD_String_xy(0, 0, display_LCD);
                            break;
                        case SetUpDataBase_TIME:
                            sprintf(display_LCD, S_time, S_CO2);
                            LCD_String_xy(0, 0, display_LCD);
                            sprintf(display_LCD, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
                            LCD_String_xy(1, 0, display_LCD);
                            break;
                        default:
                            break;
                    }
                    break;
                case SEC_LIGHT:
                    switch (SetUpDataBaseStep)
                    {
                        case SetUpDataBase_MIN:
                            sprintf(display_LCD, S_min, S_LIGHT);
                            LCD_String_xy(0, 0, display_LCD);
                            break;
                        case SetUpDataBase_MAX:                
                            break;
                        case SetUpDataBase_TIME:
                            sprintf(display_LCD, S_time, S_LIGHT);
                            LCD_String_xy(0, 0, display_LCD);
                            sprintf(display_LCD, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
                            LCD_String_xy(1, 0, display_LCD);
                            break;
                        default:
                            break;
                    }
                    break;
                case SEC_WATERING:
                    switch (SetUpDataBaseStep)
                    {
                        case SetUpDataBase_MIN:
                            break;
                        case SetUpDataBase_MAX:
                            break;
                        case SetUpDataBase_TIME:
                            sprintf(display_LCD, S_time, S_Watering);
                            LCD_String_xy(0, 0, display_LCD);
                            sprintf(display_LCD, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
                            LCD_String_xy(1, 0, display_LCD);
                            break;
                        default:
                            break;
                    }
                    break;
                case SEC_FERTILIZING:
                    switch (SetUpDataBaseStep)
                    {
                        case SetUpDataBase_MIN:
                            break;
                        case SetUpDataBase_MAX:
                            break;
                        case SetUpDataBase_TIME:
                            sprintf(display_LCD, S_time, S_Fertilizing);
                            LCD_String_xy(0, 0, display_LCD);
                            sprintf(display_LCD, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
                            LCD_String_xy(1, 0, display_LCD);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case menu_mainPage:
            sprintf(display_LCD, "1.Stat   2.Timer");
            LCD_String_xy(0, 0, display_LCD);
            sprintf(display_LCD, "3.SetUp");
            LCD_String_xy(1, 0, display_LCD);
            break;
        case menu_mainPage_Stat:
            sprintf(display_LCD, "T:  %c   RH:  %c  ", 223, 37);
            LCD_String_xy(0, 0, display_LCD);
            sprintf(display_LCD, "CO2:      L:  %c  ", 37);
            LCD_String_xy(1, 0, display_LCD);
            break;
        case menu_mainPage_Timer:
            sprintf(display_LCD, "Watering time:");
            LCD_String_xy(0, 0, display_LCD);
            sprintf(display_LCD, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
            LCD_String_xy(1, 0, display_LCD);
            break;
        case menu_mainPage_SetUp:
            sprintf(display_LCD, "1.Time");
            LCD_String_xy(0, 0, display_LCD);
            sprintf(display_LCD, "2.SensorSense");
            LCD_String_xy(1, 0, display_LCD);
            break;
        case menu_processGsm:
            LCD_String_xy(0, 0, "AtCmdRes:");
            // GSM_sendSMS("09035683914",
            // strlen("09035683914"),
            // "HIGH error",
            // strlen("HIGH error"));
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_debugKeypad_displaySensor:
            break;
        default:
            break;
    }
}
void menu_loop(void){
    uint32_t currTick = 0;
    currTick = get_currentTick();

    menuStat_t stat = get_menuStat();
    switch(stat){
        case menu_starting:
            if(pageInitTick + 2000 < currTick){
                pageInitTick = 2000 + currTick;
                if(dataBase_wasFirstTime()){
                    set_menu(menu_getSetUpForFirst);    
                }
                else{
                    set_menu(menu_mainPage);
                }
            }
            break;
        case menu_getSetUpForFirst:
            break;
        case menu_mainPage:
            break;
        case menu_mainPage_Stat:
            // dht11_loop();
            // mq5_loop();
            break;
        case menu_mainPage_Timer:
            break;
        case menu_mainPage_SetUp:
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_debugKeypad_displaySensor:
            break;
        default:
            break;
    }
}
