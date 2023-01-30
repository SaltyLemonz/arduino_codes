#include<SPI.h>
#include<SD.h>

File myfile; //create a file named attendance

void setup(){
  Serial.begin(9600);
  while(!Serial){
    ;
  }

  Serial.println("Initializing SD card");

  if(!SD.begin(4)){
    Serial.println("initialization failed");
    while(1);
  }
  Serial.println("initialization DONE");

  if(SD.exists("attendance.txt")) //checks whether the file is available or not
  Serial.println("FILE EXISTS");
  else
  Serial.println("FILE DOESN'T EXISTS");

//writing into file "attendance.txt"
  myfile=SD.open("attendance.txt", FILE_WRITE);
  myfile.write("WRITING :) :)");
  Serial.println("WROTE IN FILE SUCCESSFUL");
  myfile.close();

// //reading a file
//   myfile=SD.open("attendance.txt", FILE_READ);
//   myfile.write("READING :) :)");
//   while(myfile.available()){
//     Serail.write(myfile.read());
//   }
//   myfile.close();
}
void loop(){
  
}