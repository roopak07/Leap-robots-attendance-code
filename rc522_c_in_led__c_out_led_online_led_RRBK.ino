
/* Typical pin layout used:
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
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<String.h>

char auth[] = "e9d0c7f4f2f44ac0889c201e7aee194f";
char ssid[] = "Leap Robots LLP";
char pass[] = "leaprobot$";
BlynkTimer timer;

#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 4
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);
int check[20];
int result;
void sendSensor()
{
  bool result = Blynk.connected();
  Serial.println("Online Status: "+String(result));
  if(result==1)  // indication for online
   digitalWrite(15,HIGH); 
  else
    digitalWrite(15,LOW);
if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
   return;
  String strID = "";  
  for (byte i = 0; i < 4; i++) 
  {
    strID +=String(rfid.uid.uidByte[i], DEC);
  }
  Serial.print("Tap card key: ");
  Serial.println(strID);
/* Roopak, check[0] */
  if(strID=="83704143")
  {
    Serial.println("Roopak");
    if(check[0]==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "Roopak check-in");
      check[0]=1;
      digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
    }
    else if(check[0]==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "Roopak check-out");
      check[0]=0;
      digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
  }

 /* Ravi - check[1] */ 
  else if(strID=="36129182137")
   {
    Serial.println("Ravi");
    if(check[1]==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "Ravi check-in");
      check[1]=1;
      digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
    }
    else if(check[1]==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "Ravi check-out");
      check[1]=0;
      digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
   }
 /* Deeksha - check[2] ' */ 
else if(strID=="11240181137")
 {
  Serial.println("Deeksha");
  if(check[2]==0)
  {
    Serial.println("check in");
    Blynk.virtualWrite(V1, "Deeksha check-in");
    check[2]=1;
    digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
  }
  else if(check[2]==1)
  { 
    Serial.println("check out");
    Blynk.virtualWrite(V1,"Deeksha check-out");
    check[2]=0;
    digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
  }
 }

 /* Kalyani - check[3] */ 
  else if(strID=="501684338")
   {
    Serial.println("Kalyani");
    if(check[3]==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "Kalyani check-in");
      check[3]=1;
      digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
    }
    else if(check[3]==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "Kalyani check-out");
      check[3]=0;
       digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
   }

    /* Lavanya - check[4] */ 
  else if(strID=="5717122941")
   {
    Serial.println("Lavanya");
    if(check[4]==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "Lavanya check-in");
      check[4]=1;
      digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
    }
    else if(check[4]==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "Lavanya check-out");
      check[4]=0;
       digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
   }
 /* Ishwarya - check[5] */ 
  else if(strID=="52125183137")
   {
    Serial.println("Ishwarya");
    if(check[5]==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "Ishwarya check-in");
      check[5]=1;
      digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
    }
    else if(check[5]==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "Ishwarya check-out");
      check[5]=0;
       digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
   }

  /* person6 - check[6] */ 
  else if(strID=="501684338")
   {
    Serial.println("person6");
    if(check[6]==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "person6 check-in");
      check[6]=1;
      digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
    }
    else if(check[6]==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "person6 check-out");
      check[5]=0;
       digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
   }
   
 else
 {
  Blynk.virtualWrite(V1, strID); // printing card value in excel sheet
 }
  rfid.PICC_HaltA(); // 
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(0,OUTPUT); //D3 , for check-in indication
  pinMode(2,OUTPUT); //D4 , for check-out indication
  pinMode(15,OUTPUT); //D8 , for online indication
  SPI.begin();
  rfid.PCD_Init();
  for(int i=0;i<20;i++)
  {
   check[i]=0;
  }
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
