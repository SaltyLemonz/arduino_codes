#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
//#include<string>

//DISPLAY
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int flag;
int pos = 0;
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
String UID[3] = { "20115312290", "249224147101", "105199145101" };
String name[3] = { "Krrish", "Diptayan", "Ayan" };
String data;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  //SD CARD
  Serial.println("Initializing SD card");
  if (!SD.begin(cs)) {
    Serial.println("initialization failed");
    while (1)
      ;
  }
  Serial.println("initialization DONE");
  if (SD.exists("attendance.csv")) {
    Serial.println("FILE EXISTS");
    }
  else {
    Serial.println("FILE DOESN'T EXISTS"); 
    }
  myfile = SD.open("attendance.csv", FILE_WRITE);
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
    for (int i = 0; i < 3; i++) {
      if (tag == UID[i]) {
        flag = 1;
        pos = i;
        break;
      } else {
        flag = 0;
      }
    }
    if (flag == 1) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Welcome");
      lcd.setCursor(1, 1);
      Serial.println(name[pos]);
      lcd.println(name[pos]);
      delay(2000);
      data = name[pos] + "," + UID[pos]; //one whole row of string together
      myfile.println(data); 
      Serial.println("WROTE IN FILE SUCCESSFUL");
      myfile.close();
    } else {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Who Tf is You ?");
      myfile.println("Unknown Entry");
      lcd.setCursor(1, 1);
      lcd.print(tag);
      Serial.println(tag);
      delay(2000);
    }
    myfile.close();
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}