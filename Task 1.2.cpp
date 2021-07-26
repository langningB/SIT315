int LED = 13;
int GasSensorPin = A0;
int buttonPin = 2;
int buttonState = 0;
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt( buttonState, pin_ISR, CHANGE);
}
void loop() {
  float sensorValue, GasSensorPin;
  sensorValue = analogRead(GasSensorPin); 
  
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
  delay(10000);
}

void pin_ISR(){
  buttonState = digitalRead(buttonPin);
  digitalWrite(LED, buttonState);
}