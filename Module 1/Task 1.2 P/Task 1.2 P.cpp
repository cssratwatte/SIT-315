// Define the pins
const int ledPin = 13; // LED connected to digital pin 13
const int sensorPin = 2; // Motion sensor connected to digital pin 2

// Flag to indicate motion detected
volatile bool motionDetectedFlag = false;

void setup() {
  // Set pin modes
  pinMode(sensorPin, INPUT); // Set sensor pin as input
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  
  // Initialize serial communication
  Serial.begin(9600);

  // Attach interrupt to the motion sensor pin
  // Calls motionDetectedISR() function on state change
  attachInterrupt(digitalPinToInterrupt(sensorPin), motionDetectedISR, CHANGE);
}

void loop() {
  // Check if the motion detected flag is set
  if (motionDetectedFlag) {
    // Clear the motion detected flag
    motionDetectedFlag = false;

    // Read the motion sensor state
    int motionSensorState = digitalRead(sensorPin);
    
    // Print the motion sensor state to the Serial Monitor
    Serial.println("Motion Sensor State:");
    Serial.println(motionSensorState);

    // Turn the LED on or off based on the motion sensor state
    if (motionSensorState == HIGH) {
      digitalWrite(ledPin, HIGH); // Turn LED on
    } else {
      digitalWrite(ledPin, LOW); // Turn LED off
    }

    // Print the state of the LED to the Serial Monitor
    Serial.println("LED state: ");
    Serial.println(digitalRead(ledPin));
  }
}

// Interrupt Service Routine (ISR) for motion detection
void motionDetectedISR() {
  // Set the motion detected flag
  motionDetectedFlag = true;
}
