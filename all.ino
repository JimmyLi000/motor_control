
#include <SoftwareSerial.h> 
#include <Wire.h>
SoftwareSerial BT(8, 9); 
const int AOUTpin=0;
const int ledPin=12;
int value;
byte serialA;
const int stepPin = 3; 
const int dirPin = 4; 
int  relay =5;  //電磁閥
int  relay2 =6; //馬達通電
 
char APPDATA = 0 ;  

void setup() { 

  // put your setup code here, to run once: 
pinMode(3,OUTPUT); 
pinMode(4,OUTPUT); 
pinMode(ledPin, OUTPUT);
pinMode(relay,OUTPUT);
pinMode(relay2,OUTPUT);
Serial.begin(9600); 
Serial.println("Enter AT commands:"); 
BT.begin(9600); 
} 

void loop() { 
   value= analogRead(AOUTpin);
   Serial.print("Gas value: ");
   Serial.println(value);

   delay(100);
   if (value >= 320){
   digitalWrite(ledPin, HIGH);
   }
   else{
   digitalWrite(ledPin, LOW);
   }
   if (BT.available()>0) //只在有收到資料的時候送值 
  { 
    APPDATA = BT.read();// 讀取收到的值 
    if(APPDATA == 'c') //大左轉 
        { 
          push(); 
          pick();
        } 
    else if(APPDATA == 'g') //大右轉
        { 
          pull(); 
        } 
    else if(APPDATA == 'f') //小右轉
        { 
          right(); 
        } 
    else if(APPDATA == 'h') //小左轉
        { 
          left(); 
        } 
    else if(APPDATA == 'd') //電磁開
        { 
          on(); 
        } 
    else if(APPDATA == 'e') //電磁關
        { 
          off(); 
        } 
    else if(APPDATA == 'i') //馬達電源開
        { 
          on2(); 
        } 

    else if(APPDATA == 'j') //馬達電源關
        { 
         delay(200); 
         off2(); 
        } 
  } 
   
  } 
void on()
    {
    digitalWrite(relay,HIGH);  //電磁閥通電
    delay(2000);  
}
void off()
    {
    digitalWrite(relay,LOW);  //電磁閥關電
    delay(2000);  
}
void on2()
    {
    digitalWrite(relay2,HIGH);  //馬達通電
}
void off2()
    {
    digitalWrite(relay2,LOW);  //馬達關電
    delay(2000);  
}
void pick()
    {
    digitalWrite(11,HIGH);  //馬達關電
    delay(3000);   
    digitalWrite(11,LOW);  //馬達關電
    delay(1000);  
}

void push()  //motor 大右轉
    { 
digitalWrite(dirPin,HIGH); 
for(int x = 0; x < 300; x++){ 
digitalWrite(stepPin,HIGH); 
delayMicroseconds(1000); 
digitalWrite(stepPin,LOW); 
delayMicroseconds(3000); 
}    
     
delay(1000); 
    } 

void pull()  //motor 大左轉
    { 
digitalWrite(dirPin,LOW); 
for(int x = 0; x < 300; x++){ 
digitalWrite(stepPin,HIGH); 
delayMicroseconds(1000); 
digitalWrite(stepPin,LOW); 
delayMicroseconds(3000); 
}    
     
delay(1000); 
    } 
void right()  
    { 
digitalWrite(dirPin,HIGH); 
for(int x = 0; x < 150; x++){ 
digitalWrite(stepPin,HIGH); 
delayMicroseconds(1000); 
digitalWrite(stepPin,LOW); 
delayMicroseconds(3000); 
} 
     
delay(1000); 
    } 
 void left() //motor 
{ 
digitalWrite(dirPin,LOW); 
for(int x = 0; x < 150; x++){ 
digitalWrite(stepPin,HIGH); 
delayMicroseconds(1000); 
digitalWrite(stepPin,LOW); 
delayMicroseconds(3000);  
} 
 /* byte Data[3];  //蔡
    byte cmmd[20]; 
    int insize; 
    char str[256]; 
    int i=analogRead(A0);//read sensor value 
    serialA=BT.read(); 
    Data[0]='a'; 
    Data[1]=i/256; 
    Data[2]=i%256; 
    sprintf(str,"i: %d 0: %d 1: %d 2: %d",i,Data[0],Data[1],Data[2]); 
     Serial.println(str); 
     if (serialA == 49){ 
         for(int j=0;j<3;j++) 
         BT.write(Data[j]); 
          
         serialA=0;  //蔡
     }
delay(1000); */
}
