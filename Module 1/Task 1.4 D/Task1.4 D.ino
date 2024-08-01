#include <PinChangeInt.h>
#include <TimerOne.h>

// Define the pins for the PIR sensors and LEDs
const int pirPin1 = 13;
const int pirPin2 = 12;
const int pirPin3 = 11;

const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int ledPin4 = 5;
const int ledPin5 = 6;
const int ledPin6 = 7;
const int ledPin7 = 8;
const int ledPin8 = 9;
const int ledPin9 = 10;

// Variables to track PIR states and LED state
volatile int pir1 = 0;
volatile int pir2 = 0;
volatile int pir3 = 0;
volatile bool ledState = false;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Set PIR sensor pins as input
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(pirPin3, INPUT);

  // Set LED pins as output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin9, OUTPUT);

  // Attach pin change interrupts to the PIR sensor pins using the PCINT library
  PCintPort::attachInterrupt(pirPin1, pirISR, CHANGE);
  PCintPort::attachInterrupt(pirPin2, pirISR, CHANGE);
  PCintPort::attachInterrupt(pirPin3, pirISR, CHANGE);

  // Set up the timer interrupt
  Timer1.initialize(1000000); // Set interval to 1 second (1000000 microseconds)
  Timer1.attachInterrupt(timerISR); // Attach the timer interrupt
}

// ISR for PIR sensors using the PCINT library
void pirISR() {
  // Read PIR sensor states
  pir1 = digitalRead(pirPin1);
  pir2 = digitalRead(pirPin2);
  pir3 = digitalRead(pirPin3);

  Serial.println("Pin Change Interrupt Detected");

  // Handle the PIR sensor input
  if (pir1 == HIGH) {
    signal_1();
    delay(5000);
    clear();
  }
  if (pir2 == HIGH) {
    signal_2();
    delay(5000);
    clear();
  }
  if (pir3 == HIGH) {
    signal_3();
    delay(5000);
    clear();
  }
  if (pir1 == HIGH && pir2 == HIGH && pir3 == HIGH) {
    signal_1();
    delay(5000);
    clear();
    signal_2();
    delay(5000);
    clear();
    signal_3();
    delay(5000);
    clear();
  }
}

// ISR for the timer interrupt
void timerISR() {
  Serial.println("Timer Interrupt Fired");
  
  // Simulate sensor data reading
  int sensor1Data = analogRead(A0);
  int sensor2Data = analogRead(A1);
  Serial.print("Reading Sensor Data: Sensor1: ");
  Serial.print(sensor1Data);
  Serial.print(", Sensor2: ");
  Serial.println(sensor2Data);
}

// Function to handle signal 1
void signal_1() {
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin8, HIGH);
  delay(1000);
  digitalWrite(ledPin8, LOW);
  digitalWrite(ledPin7, HIGH);
}

// Function to handle signal 2
void signal_2() {
  digitalWrite(ledPin9, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin5, HIGH);
  delay(1000);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin4, HIGH);
}

// Function to handle signal 3
void signal_3() {
  digitalWrite(ledPin6, HIGH);
  digitalWrite(ledPin9, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(1000);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, HIGH);
}

// Function to clear all signals
void clear() {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin6, LOW);
  digitalWrite(ledPin7, LOW);
  digitalWrite(ledPin8, LOW);
  digitalWrite(ledPin9, LOW);
}

void loop() {
  // Main loop does nothing, everything is handled by ISRs
}
