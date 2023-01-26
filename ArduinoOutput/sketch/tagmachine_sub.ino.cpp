#include <Arduino.h>
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\tagmachine_sub.ino"
 ;/**
 * @file Done_ItemBox_code.ino
 * @author 김병준 (you@domain.com)
 * @brief
 * @version 1.0
 * @date 2022-11-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "tagmachine_sub.h"

#line 14 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\tagmachine_sub.ino"
void setup();
#line 41 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\tagmachine_sub.ino"
void loop();
#line 2 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\rfid.ino"
void RfidInit();
#line 19 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\rfid.ino"
void RfidLoopMain(void);
#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\timer.ino"
void TimerInit();
#line 6 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\timer.ino"
void GameTimerFunc();
#line 14 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\tagmachine_sub.ino"
void setup() {
    Serial.begin(115200);
    fromSubSerial.begin(9600, SERIAL_8N1, HWSERIAL_RX, HWSERIAL_TX);
    String dataSetUp = "";
    delay(2000);
    Serial.println("INIT");
    while(1){
        fromSubSerial.println("W");
        Serial.println("W");
        if(fromSubSerial.available() > 0){
            String dataSetUp = fromSubSerial.readStringUntil('\n'); //추가 시리얼의 값을 수신하여 String으로 저장
            // Serial.println("received:" + String(dataSetUp[0])); //기본 시리얼에 추가 시리얼 내용을 출력
            if(dataSetUp[0] == 'W'){
                while(rfid_init_complete == false){
                    Serial.println("Beetle RFID Initializing...");
                    RfidInit();
                    delay(3000);
                }
                break;
            }
        }
        delay(1000);
    }
    Serial.println("INIT FINISH");
    TimerInit();
}
    
void loop() {
    if(fromSubSerial.available() > 0){
        String dataSetUp = fromSubSerial.readStringUntil('\n'); //추가 시리얼의 값을 수신하여 String으로 저장
        // Serial.println("received:" + String(dataSetUp[0])); //기본 시리얼에 추가 시리얼 내용을 출력
        if(dataSetUp[0] == 'R'){ 
            while(rfid_init_complete == false){
                Serial.println("Beetle RFID Initializing...");
                RfidInit(); 
                delay(3000);
            }
        }
    }
    RfidLoopMain(); 
}

#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\Game_system.ino"

#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\rfid.ino"

void RfidInit()
{
    RestartPn532:
    nfc.begin();
    if (!(nfc.getFirmwareVersion()))
    {
        Serial.print("PN532 연결실패");
        rfid_init_complete = false;
        goto RestartPn532;
    }
    else
    {
        nfc.SAMConfig();
        Serial.print("PN532 연결성공");
        rfid_init_complete = true;
    }
}
void RfidLoopMain(void)
{
    uint8_t uid[3][7] = {{0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0}}; // Buffer to store the returned UID
    uint8_t uidLength[] = {0};                   // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    uint8_t data[32];
    byte pn532_packetbuffer11[64];
    pn532_packetbuffer11[0] = 0x00;
    if (nfc.sendCommandCheckAck(pn532_packetbuffer11, 1)){ // rfid 통신 가능한 상태인지 확인
        if (nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A)){                                       // rfid에 tag 찍혔는지 확인용 //데이터 들어오면 uid정보 가져오기
            if (nfc.ntag2xx_ReadPage(7, data)){ // ntag 데이터에 접근해서 불러와서 data행열에 저장
                String tagData = "";
                for(int i = 0; i < 4; i++)
                    tagData += (char)data[i];
                Serial.println(tagData);
                fromSubSerial.println(tagData);
            }
        }
        else{
        }
    }
}

#line 1 "c:\\Users\\HAS1\\Desktop\\BBangJun\\Final_Code\\tagmachine_sub\\timer.ino"
void TimerInit(){
    gameTimerId = GameTimer.setInterval(1500,GameTimerFunc);
    // GameTimer.disable(gameTimerId);
}

void GameTimerFunc(){
    // Serial.println("T1:"+tag1+"_T2:"+tag2+"_T3:"+tag3);
    // fromSubSerial.println("T1:"+tag1+"_T2:"+tag2+"_T3:"+tag3);
}
