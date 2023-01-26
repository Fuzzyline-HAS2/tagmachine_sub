#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\tagmachine_sub.h"
#ifndef _DONE_ITEMBOX_CODE_
#define _DONE_ITEMBOX_CODE_

#include "Library_and_pin.h"
const int rfid_num = 3; // 설치된 pn532의 개수

HardwareSerial fromSubSerial(1);
//****************************************SimpleTimer SETUP****************************************************************
SimpleTimer GameTimer;
void TimerInit();
void GameTimerFunc();
int gameTimerId;

//****************************************Pointer System****************************************************************
void (*ptrCurrentMode)();   //현재모드 저장용 포인터 함수

//****************************************RFID SETUP****************************************************************
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS1);
void RfidInit(void);
void RfidLoopMain(void);
bool rfid_init_complete = false;
#endif


