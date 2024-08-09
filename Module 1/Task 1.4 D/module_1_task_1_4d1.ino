#include <avr/io.h>
#include <avr/interrupt.h>

// Defining the pins for LED and the temperature sensor
const int ledPin = 13;
const int tempPin = A0; 

// Setting a threshold value for the temperature in degrees Celsius
const float tempThreshold = 25.0; 

// Setting the initial state of the LED as off
volatile bool ledState = false;

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Set the temperature sensor pin as an input
  pinMode(tempPin, INPUT);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Enable Pin Change Interrupt Control Register for PCINT2 (which includes pins 2 and 3)
  PCICR |= (1 << PCIE2); 
  
  // Enable Pin Change Interrupt Mask Register for pins 2 (PCINT18) and 3 (PCINT19)
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19); 

  // Timer setup for 1-second intervals
  noInterrupts();            // Disable interrupts during setup
  TCCR1A = 0;                // Clear Timer/Counter Control Registers
  TCCR1B = 0;               
  TCNT1  = 0;                // Initialize the counter to 0
  
  // Set Compare Match Register to trigger every second
  OCR1A = 15624;             // For 1 Hz (1-second) interval at 16 MHz clock with 1024 prescaler
  TCCR1B |= (1 << WGM12);    // Configure timer 1 for CTC (Clear Timer on Compare Match) mode
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Set up a 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);   // Enable timer compare interrupt

  interrupts();              // Enable interrupts after setup
}

// ISR (Interrupt Service Routine) for Pin Change Interrupt on pins 2 and 3
ISR(PCINT2_vect) { 
  // Turn the LED ON if any motion is detected on pins 2 or 3
  digitalWrite(ledPin, HIGH);
  Serial.println("Motion detected, LED ON!");
}

// Timer1 Compare Match ISR, triggers every second
ISR(TIMER1_COMPA_vect) {
  // Call function to read and process temperature values
  readTemperature();
}

void loop() {
  // No recurring events in the main loop
}

// Function to read and process temperature sensor values
void readTemperature() {
  int sensorValue = analogRead(tempPin);        // Read the analog value from the temperature sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading to voltage
  float temperatureC = (voltage - 0.5) * 100.0; // Convert voltage to temperature in Celsius
  
  // Print the temperature value to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  // Check if the temperature exceeds the threshold
  if (temperatureC > tempThreshold) {
    digitalWrite(ledPin, HIGH);  // Turn the LED ON if the temperature is above the threshold
    Serial.println("Temperature exceeds threshold, LED On!");
  } else {
    digitalWrite(ledPin, LOW);   // Turn the LED OFF if the temperature is below the threshold
    Serial.println("Temperature below threshold, LED Off!");
  }
}
