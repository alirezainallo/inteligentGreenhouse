#include "gsm.h"

void tgl(void);

char testGsm[]           = "AT\r\n";
char setUpNotifFormat[]  = "AT+CNMI=1,2,0,0,0\r\n";
//write data after receive '>' ch and send 26(0x1A, ctl + z)
char sendSmsTextMode[]   = "AT+CMGS=\"%s\"\r\n";
//just need use "+cmt: " for find sms command
char receivedSmsFormat[] = "+cmt: \"+989217791093\",\"\",\"23/06/16,17:29:29+14\"\r\n";
//"AT+CNMI=1,2,0,0,0/r/n"
//"AT+CMGS="09035683914"/r/n"
//Res//"+cmt: "+989217791093","","23/06/16,17:29:29+14""
char setUpClearSim[] = "AT+CMGDA=\"DEL ALL\"\r\n";

char display[17];

extern menuStat_t get_menuStat(void);
void smsReceived(char *num, char *message, char *time){
    // LCD_String(",P");
    //process messages
    if(get_menuStat() == menu_processGsm){
        LCD_String_xy(1,0,(char*)freeLine);
        sprintf(display, "%s,%d,%d,%d,%d", message, message[0], message[1], message[2], message[3]);
        LCD_String_xy(1,0, display);
    }
}
char rxSmsNumber[15]  = {0};
char rxSmsMessage[50] = {0};
char rxSmsTime[15]    = {0};
bool forceNeedCrLf = false;
bool smsWaitTitleOrMessage = true;//title true, message false
void GSM_lineProcess(char *line, size_t len){
    tgl();
    if(get_menuStat() == menu_processGsm){
        LCD_String_xy(1,0,(char*)freeLine);
        LCD_String_xy(1,0, line);
    }
    if(memcmp(line, "+cmt:", 3) == 0){

        if(smsWaitTitleOrMessage){
            smsWaitTitleOrMessage = false;
            forceNeedCrLf = true;
            //Res//"+cmt: "+989217791093","","23/06/16,17:29:29+14""
            char * start = (char*)memchr(line, '"', len);
            char * stop  = (char*)memchr(&start[1], '"', len);
            size_t numLen = (size_t)(stop - start);
            memcpy(rxSmsNumber, &start[1], numLen);
            rxSmsNumber[numLen] = 0; //Number ready
            
            start = (char*)memchr(&stop[1], '"', len);
            stop  = (char*)memchr(&start[1], '"', len);
            start = (char*)memchr(&stop[1], '"', len);
            stop  = (char*)memchr(&start[1], '"', len);
            size_t timeLen = (size_t)(stop - start);
            memcpy(rxSmsTime, &start[1], timeLen);
            rxSmsTime[timeLen] = 0; //Time ready
        }
    }
    else if(!smsWaitTitleOrMessage){
        LCD_String(",c");
        strncat(rxSmsMessage, line, len);
        if(!forceNeedCrLf){
            smsWaitTitleOrMessage = true;
            smsReceived(rxSmsNumber, rxSmsMessage, rxSmsTime);
        }
    }
    
}
void tgl(void){
    static bool pre = false;
    if(pre){
        PORTA &= ~(1 << PA2);
    }
    else{
        PORTA |= (1 << PA2);
    }
    pre = !pre;
}
void GSM_init(void){
    DDRA  |= (1 << PA2);
    PORTA |= (1 << PA2);
    PORTA &= ~(1 << PA2);
    uart_init();
    GSM_sendAtCommand(setUpNotifFormat, strlen(setUpNotifFormat));
    _delay_ms(200);
    GSM_sendAtCommand(setUpClearSim, strlen(setUpClearSim));
    _delay_ms(200);
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
