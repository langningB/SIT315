int LED = 13;
int GasSensorPin = A0;
int buttonPin = 2;
int buttonState = 0;

int DistanceSensorPin = A1;
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt( buttonState, pin_ISR, CHANGE);
}
void loop() {
  float sensorValue, GasSensorPin;
  sensorValue = analogRead(GasSensorPin); 
  
  float distanceValue, DistanceSensorPin;
  distanceValue = analogRead(DistanceSensorPin);
  
  if(sensorValue >= 100){
    digitalWrite(LED, HIGH);
    Serial.print(sensorValue);
    Serial.println(" | SMOKE DETECTED");
  } 
  else {
  	digitalWrite(LED,LOW);
    Serial.println("Sensor Value: ");
    Serial.println(sensorValue);
  } 
  
  
  if(distanceValue >= 1){
    digitalWrite(LED, HIGH);
    Serial.print(distanceValue);
    Serial.println(" | distance found");
  } 
  else {
  	digitalWrite(LED,LOW);
    Serial.println("Sensor Value: ");
    Serial.println(distanceValue);
  } 
  
  delay(5000);
}

void pin_ISR(){
  buttonState = digitalRead(buttonPin);
  digitalWrite(LED, buttonState);
}