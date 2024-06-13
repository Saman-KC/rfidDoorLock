#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>


 
#include <SPI.h>
#include <MFRC522.h>

#define RELAY_PIN 8
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
 
void setup() 
{
  pinMode(7,1);
  pinMode(6,1);
  Serial.begin(9600);  
  SPI.begin();   
  mfrc522.PCD_Init(); 
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  digitalWrite(RELAY_PIN, LOW);

}
void loop() 
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
  if (content.substring(1) == "-- -- -- --") //place here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();


    digitalWrite(RELAY_PIN, HIGH);
    
  }
  else 
  {
    Serial.println("Access denied");
    Serial.println();

  }
 
 
} 