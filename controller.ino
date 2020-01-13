#include  <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
String str;
String string;
String string0;
int number;
int motor[4][2] = {{0,0},{0,0},{0,0},{0,0}};
int LL = 6;
int LR = A5;
int LF = 7;
int LB = A4;
int RR = A3;
int RB = A0;
int RL = A2;
int RF = A1;
void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(RF,INPUT);
  pinMode(RR,INPUT);
  pinMode(RB,INPUT);
  pinMode(RL,INPUT);
  pinMode(LB,INPUT);
  pinMode(LL,INPUT);
  pinMode(LF,INPUT);
  pinMode(LR,INPUT);
}

void loop() {
  if (Serial.available()) {
    BTSerial.println("AT+ROLE1");
    while(!BTSerial.find("OK"));
    str = Serial.readStringUntil('\n');
    BTSerial.println(str);
    while(!BTSerial.find("OK"));
    Serial.println("OK");
  }
  while (digitalRead(RF) == 0 || digitalRead(RB) == 0 || digitalRead(RR) == 0 || digitalRead(RL) == 0
    || digitalRead(LF) == 0 || digitalRead(LB) == 0 || digitalRead(LR) == 0 || digitalRead(LL) == 0){
      control();

      /// Serial.println(string);
      ///Serial.println(number);
      BTSerial.write(byte(number));
      string0 = string;
      while (string0 == string){
        control();
        if (string0 != string)break;
      }
      if (number == 0){
        ///Serial.println(string);
        ///Serial.println(number);
        BTSerial.write(byte(number));
      }
  }
}

void control(){
  if(digitalRead(RF) == 0){
    motor[3][0] = 1;
  }
  else{
    motor[3][0] = 0;
  }
  if(digitalRead(RB) == 0){
    motor[3][1] = 1;
  }
  else{
    motor[3][1] = 0;
  }
  if(digitalRead(RL) == 0){
    motor[2][0] = 1;
  }
  else{
    motor[2][0] = 0;
  }
  if(digitalRead(RR) == 0){
    motor[2][1] = 1;
  }
  else{
    motor[2][1] = 0;
  }
  if(digitalRead(LF) == 0){
    motor[0][0] = 1;
  }
  else{
    motor[0][0] = 0;
  }
  if(digitalRead(LB) == 0){
    motor[0][1] = 1;
  }
  else{
    motor[0][1] = 0;
  }
  if(digitalRead(LL) == 0){
    motor[1][0] = 1;
  }
  else{
    motor[1][0] = 0;
  }
  if(digitalRead(LR) == 0){
    motor[1][1] = 1;
  }
  else{
    motor[1][1] = 0;
  }
  string = String(motor[0][0])+String(motor[0][1])+String(motor[1][0])+String(motor[1][1])+
    String(motor[2][0])+String(motor[2][1])+String(motor[3][0])+String(motor[3][1]);
  number = ldexp(int(motor[0][0]),7)+ldexp(int(motor[0][1]),6)+ldexp(int(motor[1][0]),5)+ldexp(int(motor[1][1]),4)
  +ldexp(int(motor[2][0]),3)+ldexp(int(motor[2][1]),2)+ldexp(int(motor[3][0]),1)+ldexp(int(motor[3][1]),0);

}
