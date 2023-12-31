#include "gsm.h"



char testGsm[]           = "AT\r\n";
char setUpNotifFormat[]  = "AT+CNMI=1,2,0,0,0\r\n";
//write data after receive '>' ch and send 26(0x1A, ctl + z)
char sendSmsTextMode[]   = "AT+CMGS=\"%s\"\r\n";
//just need use "+cmt: " for find sms command
char receivedSmsFormat[] = "+CMT: \"+989035683914\",\"\",\"23/06/19,02:06:03+14\"\r\n";
//"AT+CNMI=1,2,0,0,0/r/n"
//"AT+CMGS="09035683914"/r/n"
//Res//"+cmt: "+989217791093","","23/06/16,17:29:29+14""
char setUpClearSim[] = "AT+CMGDA=\"DEL ALL\"\r\n";

// char display[256];



//Watering Alarm
char CMD_WA[] = "WA,  :  :  ,";
//Fertilizing Timer
char CMD_FT[] = "FT,  :  :  ,";

extern menuStat_t get_menuStat(void);
void smsReceived(char *num, char *message, char *time){
    //process messages
    timer_t tim;

    if(memcmp(CMD_WA, message, 2) == 0){
        sscanf(&message[3], "%2hhd", &tim.hour);
        sscanf(&message[6], "%2hhd", &tim.min);
        sscanf(&message[9], "%2hhd", &tim.sec);
        if(get_menuStat() == menu_processGsm){
            LCD_String_xy(1,0,(char*)freeLine);
            sprintf(display_LCD, "%d:%d:%d", tim.hour, tim.min, tim.sec);
            LCD_String_xy(1,0, display_LCD);
        }
        timerChecker_addTimer(SEC_AlarmForTimerChecker, tim, setAlarmForStartWatering);
        // turnOn(RELAY_WATERING);
        // timerChecker_addTimer(SEC_AlarmForTimerChecker, tim, setAlarmForStartWatering);
    }
    else if(memcmp(CMD_FT, message, 2) == 0){
        sscanf(&message[3], "%2hhd", &tim.hour);
        sscanf(&message[6], "%2hhd", &tim.min);
        sscanf(&message[9], "%2hhd", &tim.sec);
        if(get_menuStat() == menu_processGsm){
            LCD_String_xy(1,0,(char*)freeLine);
            sprintf(display_LCD, "%d:%d:%d", tim.hour, tim.min, tim.sec);
            LCD_String_xy(1,0, display_LCD);
        }
        timerChecker_addTimer(SEC_AlarmForTimerChecker2, tim, setAlarmForStartFertilizing);
        // turnOn(RELAY_FERTILIZING);
        // timerChecker_addTimerAfterNow(SEC_FERTILIZING, tim, AlarmToTernOffFertilizing);
    }

    if(get_menuStat() == menu_processGsm){
        // txSendDataLen(num,     strlen(num));
        // txSendDataLen(message, strlen(message));
        // txSendDataLen(time,    strlen(time));

        // LCD_String_xy(0, 0, num);
        // LCD_String_xy(1, 0, time);
        // LCD_String_xy(1, 0, (char*)freeLine);
        // LCD_String_xy(1, 0, message);
    }
}
static char rxSmsNumber[15]  = {0};
static char rxSmsMessage[50] = {0};
static char rxSmsTime[15]    = {0};
// bool forceNeedCrLf = false;
// bool smsWaitTitleOrMessage = true;//title true, message false
char GSM_SmsBuff[RX_BUFFER_SIZE];
size_t GSM_SmsBuffLen = 0;
extern bool SMS_lineReady;
void GSM_lineProcess(char *line, size_t len){
    // txSendDataLen(line, len);
    // if(get_menuStat() == menu_processGsm){
    //     LCD_String_xy(1,0,(char*)freeLine);
    //     LCD_String_xy(1,0, line);
    // }
            
    //Res//"+CMT: "+989217791093","","23/06/16,17:29:29+14""
    
    if(SMS_lineReady){
        SMS_lineReady = false;
        memcpy(GSM_SmsBuff, line, len);
        GSM_SmsBuffLen = len;

        rxSmsNumber[0] = 0;
        char * startNumber = (char*)memchr(GSM_SmsBuff, '"', GSM_SmsBuffLen);
        char * stopNumber  = (char*)memchr(&startNumber[1], '"', GSM_SmsBuffLen);
        size_t numLen = (size_t)(stopNumber - startNumber) - 2;
        memcpy(rxSmsNumber, &startNumber[2], numLen);
        rxSmsNumber[numLen] = 0; //Number ready

        rxSmsTime[0] = 0;
        char * startTime = (char*)memchr(&stopNumber[1], '"', GSM_SmsBuffLen);
        char * stopTime  = (char*)memchr(&startTime[1], '"', GSM_SmsBuffLen);
        startTime = (char*)memchr(&stopTime[1], '"', GSM_SmsBuffLen);
        stopTime  = (char*)memchr(&startTime[1], '"', GSM_SmsBuffLen);
        size_t timeLen = (size_t)(stopTime - startTime) - 1;
        memcpy(rxSmsTime, &startTime[1], timeLen);
        rxSmsTime[timeLen] = 0; //Time ready

        rxSmsMessage[0] = 0;
        char * startMessage = (char*)memchr(&stopNumber[1], '\n', GSM_SmsBuffLen);
        char * stopMessage  = (char*)memchr(&startMessage[1], '\n', GSM_SmsBuffLen);
        size_t messageLen = (size_t)(stopMessage - startMessage) - 2;
        memcpy(rxSmsMessage, &startMessage[1], messageLen);
        rxSmsMessage[messageLen] = 0; //Time ready

        smsReceived(rxSmsNumber, rxSmsMessage, rxSmsTime);
    }
}
// void tgl(void){
//     static bool pre = false;
//     if(pre){
//         PORTA &= ~(1 << PA2);
//     }
//     else{
//         PORTA |= (1 << PA2);
//     }
//     pre = !pre;
// }
void GSM_init(void){
    // DDRA  |= (1 << PA2);
    // PORTA |= (1 << PA2);
    // PORTA &= ~(1 << PA2);
    uart_init();
    GSM_sendAtCommand(setUpNotifFormat, strlen(setUpNotifFormat));
    _delay_ms(500);
    GSM_sendAtCommand(setUpClearSim, strlen(setUpClearSim));
    _delay_ms(500);
}
void GSM_sendAtCommand(char *cmd, size_t len){
    txSendDataLen(cmd, len);
}
void GSM_loop(void){
    uart_loop();
}
bool smsSignReceived = false;
void GSM_sendSMS(char*phone, size_t phLen, char*message, size_t messageLen){
    char cmd[50];
    phone[phLen] = 0;
    sprintf(cmd, sendSmsTextMode, phone);
    smsSignReceived = false;
    GSM_sendAtCommand(cmd, strlen(cmd));
    while(!smsSignReceived){
        _delay_ms(1);
    }
    // smsSignReceived = false;
    message[messageLen] = 0;
    sprintf(cmd, "%s%c", message, 26);
    GSM_sendAtCommand(cmd, strlen(cmd));
}
