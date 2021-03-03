#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <BlynkSimpleEsp8266.h>


const char ssid[] = "Samsungs10";
const char pass[] = "nepal123";
const char auth[] = "lxNZPbVB6pkJU4zwU6wPmdL79AhvPGF7";
WiFiClient client;
BlynkTimer timer;
Servo myservo;
#define SS_PIN 4
#define RST_PIN 5
#define pin D8
#define second D4
MFRC522 mfrc522(SS_PIN, RST_PIN);   



void setup() {
 
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  SPI.begin();      
  mfrc522.PCD_Init(); 
  pinMode(pin,OUTPUT);
  pinMode(second,OUTPUT);
 timer.setInterval(1000L,rfidSearch);
  //myservo.attach(8);
  
}



void loop() {
  // put your main code here, to run repeatedly:
   
   rfidSearch();
}

void lighting()
{
  
  for(int i=0; i<10; i++)
  {
    digitalWrite(pin,HIGH);
    digitalWrite(second,LOW);
  delay(500);
   digitalWrite(pin,LOW);
   digitalWrite(second,HIGH);
   delay(500);
   digitalWrite(second,LOW);
  }
    
 
}

void rfidSearch()
{
 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "99 B4 9E 98") //change here the UID of the card/cards that you want to give access
  {
    
    Serial.println("Authorized access");
      Blynk.notify("Your child has reached to school.");

    lighting();
  
    Serial.println();
    delay(3000);
  }
   else if (content.substring(1) == "49 9F 85 98") 
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}

//void internetConnection()
//{
//      Serial.println("Wifi connecting....");
//       WiFi.begin(ssid, pass); 
//       while (WiFi.status() != WL_CONNECTED) 
//          {
//            delay(500);
//            Serial.print(".");
//          }
//      Serial.println("");
//      Serial.println("WiFi connected"); 
//}
