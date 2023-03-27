# BrainDelayTest
This code is designed for an Arduino board to play a game where a LED turns on at a random time and the user has to press a button to turn it off, while the time it took to turn it off is displayed on a 4-digit 7-segment display. The purpose of the game is to test the user's reaction time.

# Pin Configuration
The following pins are used for LED, push button, and the 4-digit 7-segment display:
```
int push = 10; // Push button pin
int LED = 5; // LED pin
TM1637Display display = TM1637Display(6, 7); // Display pins
```
# Variables
DELAY: stores the time it took to turn off the LED

Delay[11]: an array for storing the last 10 delay times

counter: a counter for indexing the Delay array

# Setup
The code sets up the LED and push button pins as output and input respectively, and initializes the push button state. The display is cleared and the random seed is set based on an analog read value:
```
void setup() {
    pinMode(LED, OUTPUT);
    pinMode(push, INPUT_PULLUP);
    display.clear();
    randomSeed(analogRead(0));
    push = 1;
}
```
# Game Loop
The game loop consists of two main parts: the countdown and the game itself.

# Countdown
A countdown from 5 is displayed on the 4-digit 7-segment display:
```
display.setBrightness(5);
for (int i = 5; i > 0; i--) {
    display.showNumberDec(i);
    delay(1000);
}
display.clear();
```
# Game
A random number between 1 and 50 is generated and the LED is turned on after that many iterations. The delay time is recorded when the push button is pressed and the LED is turned off:
```
int randInt = random(1, 50);
for (int i = 0; i < 50; i++) {
    delay(100);
    if (i == randInt) {
        digitalWrite(LED, 1); // Turn on the LED
        for (int j = 0; j < 3000; j++) { // Wait for the push button to be pressed and record the delay time
            delay(1);
            push = digitalRead(10);
            if (push == 0) {
                counter++; // Increment the counter
                digitalWrite(LED, 0); // Turn off the LED
                DELAY = j; // Record the delay time
                break; // Exit the loop
            }
        }
        digitalWrite(LED, 0); // Turn off the LED
    }
    Delay[counter] = DELAY; // Store the delay time in the Delay array
    // Show the last delay time on the 4-digit 7-segment display
    if (counter < 10) {
        display.showNumberDec(DELAY);
        delay(1000);
    }
    // Calculate and show the average delay time on the 4-digit 7-segment display
    if (counter == 10) {
        for (int i = 0; i < 10; i++) {
            Delay[10] += Delay[i]; // Add up all the delay times
            Delay[10] = Delay[10] / 10; // Divide by 10 to get the average delay time
        }
    }
}
```
The last 10 delay times are stored in an array and displayed on the 4-digit 7-segment display.
