// Pins
int ledPin = 13;
int sensorPin = 4;

int motionSensorState = 0;
void setup()
{
  // pins setup
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // reading data from motion sensor
  motionSensorState = digitalRead(sensorPin);
  // printing motionSensor state 
  Serial.println("Motion Sensor State:");
  Serial.println(motionSensorState);
  
  if(motionSensorState == HIGH){
    digitalWrite(ledPin,HIGH);
  }else {
    digitalWrite(ledPin, LOW);
  }
  // printing the state of LED
  Serial.println("LED state: ");
  Serial.println(digitalRead(ledPin));
  // adding 2sec delay
  delay(2000);
}