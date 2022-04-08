#include <TM1637Display.h>
TM1637Display display = TM1637Display(6, 7);
int push;
int DELAY;
int Delay[11]={0,0,0,0,0,0,0,0,0,0};
int counter=-1;
void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
pinMode(10,INPUT_PULLUP);
display.clear();
randomSeed(analogRead(0));
push=1;

}

void loop() {
  // put your main code here, to run repeatedly:
DELAY=0;
 display.setBrightness(5);
 for(int i=5;i>0;i--){
 display.showNumberDec(i);
 delay(1000);
 }
 display.clear();
 int randInt=random(1,50);
 for(int i=0;i<50;i++){
  delay(100);
  if(i==randInt){
    digitalWrite(5,1);
    for(int j=0;j<3000;j++){
      delay(1);
    push=digitalRead(10);
    if(push==0){
      counter++;
      digitalWrite(5,0);
      DELAY=j;
      break;
    }
    }
    digitalWrite(5,0);
  }
  Delay[counter]=DELAY;
  if(counter<10){
   display.showNumberDec(DELAY);
   delay(1000);
  }
  if(counter==10){
    for(int i=0;i<10;i++){
      Delay[10]+=Delay[i];
      Delay[10]=Delay[10]/10;
    }
    
  }
 }
 
}
