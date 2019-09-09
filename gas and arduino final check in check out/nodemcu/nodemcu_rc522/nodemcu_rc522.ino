/*
PINOUT:
 * https://circuits4you.com
 * 
 * RC522 Interfacing with NodeMCU
 * 
 * Typical pin layout used:
 * ----------------------------------
 *             MFRC522      Node     
 *             Reader/PCD   MCU      
 * Signal      Pin          Pin      
 * ----------------------------------
 * RST/Reset   RST          D1 (GPIO5)        
 * SPI SS      SDA(SS)      D2 (GPIO4)       
 * SPI MOSI    MOSI         D7 (GPIO13)
 * SPI MISO    MISO         D6 (GPIO12)
 * SPI SCK     SCK          D5 (GPIO14)
 * 3.3V        3.3V         3.3V
 * GND         GND          GND
 */
#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 4
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
 if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) // it will check for newcard and it will check weather card reader is avilable or not  
   return; //it will print continious 0's if we remove this line ,since if we get 0's it will retrun back to loop()
  String strID = ""; // intilizing or declaring strID as a string  
  for (byte i = 0; i < 4; i++) 
  {
    strID +=String(rfid.uid.uidByte[i], DEC);
  }
  Serial.print("Tap card key: ");
  Serial.println(strID);
  rfid.PICC_HaltA(); // it will print card value only time if you kep card on reader ,if we remove this line it will print values continously 
}
