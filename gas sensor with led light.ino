int LED = 13;
int GasSensorPin = A0;


void setup() 
{
  pinMode(LED, OUTPUT);
}

void loop() 
{
  float sensorValue, GasSensorPin;
  sensorValue = analogRead(GasSensorPin); 
  if(sensorValue >= 100)
  {
    digitalWrite(LED, HIGH);
    Serial.print(sensorValue);
    Serial.println(" | SMOKE DETECTED");
  } 
  else 
  {
  	digitalWrite(LED,LOW);
    Serial.println("Sensor Value: ");
    Serial.println(sensorValue);
  } 
  delay(1000);
}