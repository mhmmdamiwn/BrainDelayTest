/*

Arduino code for a game where a LED turns on at a random time and the user has to press a button to turn it off,
while the time it took to turn it off is displayed on a 4-digit 7-segment display.
*/
#include <TM1637Display.h>
TM1637Display display = TM1637Display(6, 7); // Create a display object for the 4-digit 7-segment display and specify the pins

// Variables for push button, LED and delay time
int push;
int DELAY;
int Delay[11]={0,0,0,0,0,0,0,0,0,0}; // Array for storing the last 10 delay times
int counter=-1; // Counter for indexing the Delay array

void setup() {
pinMode(5,OUTPUT); // Set the LED pin as an output
pinMode(10,INPUT_PULLUP); // Set the push button pin as an input with a pull-up resistor
display.clear(); // Clear the display
randomSeed(analogRead(0)); // Set the random seed based on an analog read value
push=1; // Initialize the push button state
}

void loop() {
// Countdown from 5 on the 4-digit 7-segment display
display.setBrightness(5);
for(int i=5;i>0;i--){
display.showNumberDec(i);
delay(1000);
}
display.clear();

// Generate a random number between 1 and 50 and turn on the LED after that many iterations
int randInt=random(1,50);
for(int i=0;i<50;i++){
delay(100);
if(i==randInt){
digitalWrite(5,1); // Turn on the LED
// Wait for the push button to be pressed and record the delay time
for(int j=0;j<3000;j++){
delay(1);
push=digitalRead(10);
if(push==0){
counter++; // Increment the counter
digitalWrite(5,0); // Turn off the LED
DELAY=j; // Record the delay time
break; // Exit the loop
}
}
digitalWrite(5,0); // Turn off the LED
}
Delay[counter]=DELAY; // Store the delay time in the Delay array
// Show the last delay time on the 4-digit 7-segment display
if(counter<10){
display.showNumberDec(DELAY);
delay(1000);
}
// Calculate and show the average delay time on the 4-digit 7-segment display
if(counter==10){
for(int i=0;i<10;i++){
Delay[10]+=Delay[i]; // Add up all the delay times
Delay[10]=Delay[10]/10; // Divide by 10 to get the average delay time
}
}
}
}
