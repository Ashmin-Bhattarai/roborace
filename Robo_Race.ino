#include <ibus.h>
#include <Servo.h>


//defining the required ports
#define enableLeft 6
#define enableRight 11
#define leftfor 7
#define leftbac 8
#define rightfor 9
#define rightbac 10
#define ser 3

Servo my_Servo;
int16_t channel[10];
int16_t up,side,ang;

void setup() {
  Serial.begin(115200);
  IBus.begin(Serial);
  my_Servo.attach(ser);
  //Define pinMode
  pinMode (enableLeft, OUTPUT);
  pinMode (enableRight, OUTPUT);
  pinMode (leftfor, OUTPUT);
  pinMode (leftbac,OUTPUT);
  pinMode (rightfor, OUTPUT);
  pinMode (rightbac,OUTPUT);
  my_Servo.write(0);
}

void loop() {
  readData();
  up = map(channel[2],1000,2000,-255,255);
  side = map(channel[3],1000,2000,-255,255);
  ang = map (channel[5],1000,2000,-180,180);

  if (up > 40 && up <= 255){
    analogWrite (enableLeft, abs(up));
    analogWrite (enableRight,abs(up));
    forwards();
  }
  else if (up < -40 && up >= -255){
    analogWrite( enableLeft, abs(up));
    analogWrite( enableRight, abs(up));
    backwards();
  }
  else if (side > 40 && side <= 255 && up < 40 && up > -40){
    analogWrite( enableLeft, abs(side));
    analogWrite( enableRight, abs(side));
    left();
  }
  else if (side < -40 && side >= -255 && up < 40 && up > -40){
    
    analogWrite( enableLeft, abs(side));
    analogWrite( enableRight, abs(side));
    right();
  }
  else{
    stopped();
  }
  
  my_Servo.write(ang);
}

void readData(){
  IBus.loop();
  for(int i=0; i<10 ; i++){
    channel[i] = IBus.readChannel(i);
  }
}

void forwards(){
  digitalWrite(leftfor,HIGH);
  digitalWrite(rightfor,HIGH);
  digitalWrite(leftbac,LOW);
  digitalWrite(rightbac,LOW);
}
void backwards(){
  digitalWrite(leftbac,HIGH);
  digitalWrite (rightbac, HIGH);
  digitalWrite (leftfor,LOW);
  digitalWrite (rightfor,LOW);
}
void left(){
  digitalWrite (leftbac,HIGH);
  digitalWrite (rightfor,HIGH);
  digitalWrite (leftfor,LOW);
  digitalWrite (rightbac,LOW);
}
void right(){
  digitalWrite (rightbac,HIGH);
  digitalWrite (leftfor,HIGH);
  digitalWrite (rightfor,LOW);
  digitalWrite (leftbac,LOW);
}
void stopped(){
  digitalWrite (rightbac,LOW);
  digitalWrite (leftbac, LOW);
  digitalWrite (rightfor, LOW);
  digitalWrite (leftfor, LOW);
}
