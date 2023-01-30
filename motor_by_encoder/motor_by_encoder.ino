 
 #define inA 4
 #define inB 5
 //motor
 #define min1 6
 #define min2 7
 #define pw 8
 int counter = 0; 
 int aState;
 int aLastState; 
  void forward(){
   digitalWrite(min1,HIGH);
   digitalWrite(min2,LOW);
 }
 void backward(){
  digitalWrite(min1,LOW);
  digitalWrite(min2,HIGH);
 }
 void stop(){
  digitalWrite(min1,LOW);
  digitalWrite(min2,LOW);
 }

 void setup() { 
   pinMode (inA,INPUT);
   pinMode (inB,INPUT);
   
   Serial.begin (9600);
   aLastState = digitalRead(inA);   
 } 

 void loop() {
  String dir="";
  int flag=0;
  int flagf=0;
  int n1=0;
  int n2=0;
  digitalWrite(pw, 42);
   aState = digitalRead(inA);
   if (aState != aLastState){     
     if (digitalRead(inB) != aState) { 
       counter ++;
       n1=counter;
       Serial.println(dir);
     }
     else {
       counter --;
       n2=counter;
       Serial.println(dir);
     }
     Serial.print("Position: ");
     Serial.println(counter);

     
     if(counter>=0&&counter<70){
      forward();
      Serial.println("forward");
     }
     
     if(counter>=70){
      backward();
     Serial.println("backward");
     }
     
//     if(flagf==1){
//      forward();
//      Serial.printf("forward");
//     }
//     if(flag==1 && dir=="acw"){
//      delay(200);
//     backward();
//     Serial.println("backward");
//     }

    if (counter<=-1){
       stop();
       Serial.println("stop");
    }
    
   }
   aLastState = aState;
 }
