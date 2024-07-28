// Define the pin for the button
const uint8_t switchPin = 3;
// Define the pin for the LED
const uint8_t led = 2;
// Define the pin for PIR
const uint8_t pir = 7;

// Variable to store the state of switch
uint8_t switch_state = LOW;
// Variable to store the current state of the LED
uint8_t led_state = LOW;
// Variable to store the state of PIR
uint8_t pir_state = LOW;

void handleLED(){
  led_state = !led_state;
  digitalWrite(led, led_state);
  
  Serial.print("LED state: ");
  Serial.println(led_state);
}

void setup()
{
  // Set the switch pin as input with an internal pull-up resistor
  pinMode(switchPin, INPUT_PULLUP);
  
  // set the PIR pin as INPUT)
  pinMode(pir, INPUT);
  
  // Set the LED pin as output
  pinMode(led, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(switchPin), handleLED, CHANGE);
  
  // Initialize serial communication at a baud rate of 9600
  Serial.begin(9600);
}

void loop()
{
  int pir_value = digitalRead(pir);
  if (pir_value == HIGH) {
    led_state = !led_state;
    pir_state = !pir_state;
    
    Serial.print("PIR State: ");
    Serial.println(pir_state);
    
    digitalWrite(led, led_state);
    
    // Debounce delay
    delay(200);
  }
}
