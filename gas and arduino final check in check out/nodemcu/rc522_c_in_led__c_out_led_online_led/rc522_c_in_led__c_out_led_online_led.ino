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
//#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "e9d0c7f4f2f44ac0889c201e7aee194f";
char ssid[] = "Realme 2 Pro";
char pass[] = "roopak07";
BlynkTimer timer;

#include "MFRC522.h"
#define SS_PIN 4
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);
int check[20];
void sendSensor()
{
   digitalWrite(15,HIGH); // indication for online
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

 /* Rahul - check[1] */ 
  else if(strID=="16024222841")
   {
    Serial.println("Rahul");
    if(check[1]==0)
    {
      Serial.println("check in");
      Blynk.virtualWrite(V1, "Rahul check-in");
      check[1]=1;
      digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
    }
    else if(check[1]==1)
    {
      Serial.println("check out");
      Blynk.virtualWrite(V1, "Rahul check-out");
      check[1]=0;
      digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
   }
 /* Bansi - check[2] '  */ 
else if(strID=="160206175137")
 {
  Serial.println("Bansi");
  if(check[2]==0)
  {
    Serial.println("check in");
    Blynk.virtualWrite(V1, "Bansi check-in");
    check[2]=1;
    digitalWrite(0,HIGH);
      delay(200);
      digitalWrite(0,LOW);
      delay(200);
  }
  else if(check[2]==1)
  { 
    Serial.println("check out");
    Blynk.virtualWrite(V1,"Bansi check-out");
    check[2]=0;
    digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
  }
 }

 /* Kalyani - check[3] */ 
  else if(strID=="24419422941")
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
