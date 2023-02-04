#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
//#include<string>

//DISPLAY
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//RFID
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN = D4;
MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class
MFRC522::MIFARE_Key key;
String tag;

//SDCARD
File myfile;                //create a file named attendance
constexpr uint8_t cs = D8;  //NODE MCU

//ID CARD DETAILS
// char *UID[] = {"249224147101", "UID2"};
// char *name[] = {"Diptayan"};
//maybe
String UID[2] = { "249224147101", "20115312290" };
String name[2] = { "Diptayan", "Krrish" };

int pos;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  //SD CARD
  // Serial.println("Initializing SD card");
  // if (!SD.begin(cs)) {
  //   Serial.println("initialization failed");
  //   while (1)
  //     ;
  // }
  // Serial.println("initialization DONE");
  // if (SD.exists("attendance.txt"))
  //   Serial.println("FILE EXISTS");
  // else
  //   Serial.println("FILE DOESN'T EXISTS");
}

void loop() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("scan");
  lcd.setCursor(1, 1);
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    //Serial.println(tag);

    // if (tag == "249224147101") {
    //   lcd.clear();
    //   lcd.setCursor(2, 0);
    //   lcd.print("Welcome");
    //   lcd.setCursor(1, 1);
    //   Serial.println("Diptayan");
    //   lcd.println("Diptayan");
    //   delay(2000);
    // } else {
    //   lcd.clear();
    //   lcd.setCursor(2, 0);
    //   lcd.print("SUS!!!");
    //   lcd.setCursor(1, 1);
    //   lcd.print(tag);
    //   Serial.println(tag);
    //   delay(2000);
    // }
    for (int i = 0; i < 2; i++) {
      if (tag == UID[i]) {
        pos = i;
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Welcome");
        lcd.setCursor(1, 1);
        Serial.println(name[pos]);
        lcd.println(name[pos]);
        delay(2000);
        } else {
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("Who Tf is You ?");
          lcd.setCursor(1, 1);
          lcd.print(tag);
            Serial.println(tag);
          delay(2000);
          break;
      }
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}