#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 128
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
BlynkTimer timer;
#define EspSerial Serial
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8
MFRC522 rfid(SS_PIN, RST_PIN);

char auth[] = "09754f5944c94ede9f2714b3802430ef";
char ssid[] = "Realme 2 Pro"; 
char pass[] = "roopak07"; 
int a=12345,b=12345;

void sendSensor()
{
   digitalWrite(4,HIGH); // indication for online
if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
   return;
  String strID = "";  
  for (byte i = 0; i < 4; i++) 
  {
    strID +=String(rfid.uid.uidByte[i], DEC);
  }
  Serial.print("Tap card key: ");
  Serial.println(strID);
  digitalWrite(3,HIGH);
  delay(200);
  digitalWrite(3,LOW);
  delay(200);
/* Master Card */
  if(strID=="83704143")
  {
    Serial.println("master card");
    a=0;
    b=0;
    Blynk.virtualWrite(V1, "master card"); //printing name in excel sheet
  }

 /* Manisha */ 
  else if(strID=="16024222841")
   {
    Serial.println("Mahesh");
    if(a==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "Mahesh check-in");
      a=1;
    }
    else if(a==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "Mahesh check-out");
      a=0;
    }
    else if(a==12345)
    {
      Serial.println("Mahesh");
      Blynk.virtualWrite(V1, "Mahesh"); //printing name in excel sheet
    }
   }
 /* roopak '  */ 
else if(strID=="160206175137")
 {
  Serial.println("Roopak");
  if(b==0)
  {
    Serial.println("check in");
    Blynk.virtualWrite(V1, "Roopak check-in");
    b=1;
  }
  else if(b==1)
  { 
    Serial.println("check out");
    Blynk.virtualWrite(V1,"Roopak check-out");
    b=0;
  }
  else if(b==12345)
    {
      Serial.println("Roopak");
      Blynk.virtualWrite(V1, "Roopak"); //printing name in excel sheet
    }
 }
 else
 {
  Blynk.virtualWrite(V1, strID); // printing card value in excel sheet
 }
  rfid.PICC_HaltA(); // 
}

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth,wifi, ssid, pass);
  SPI.begin();
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  rfid.PCD_Init();
  timer.setInterval(2000L, sendSensor); 
}

void loop(){
  Blynk.run();
  timer.run();
}

