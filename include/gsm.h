#ifndef _GSM_H
#define _GSM_H

#include "main.h"
#include "uart.h"
#include "LCD.h"
#include "e2prom.h"
#include "timerChecker.h"

extern char testGsm[];
extern char setUpNotifFormat[];
//write data after receive '>' ch and send 26(0x1A, ctl + z)
extern char sendSmsTextMode[];
//just need use "+cmt: " for find sms command
extern char receivedSmsFormat[];
//"AT+CNMI=1,2,0,0,0/r/n"
//"AT+CMGS="09035683914"/r/n"
//Res//"+cmt: "+989217791093","","23/06/16,17:29:29+14""

void GSM_init(void);
void GSM_loop(void);
void GSM_sendAtCommand(char *cmd, size_t len);
void GSM_sendSMS(char*phone, size_t phLen, char*message, size_t messageLen);
#endif //_GSM_H
