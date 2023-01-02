const int sensorPin = 5;
const int relayPin = 13;
const int analogPin = 0;
int raw = 0;
int count = 0;
const int Vin = 5;
float Vout = 0;
const float knownR = 200000;
float unknownR = 0;
float avg = 0;
int avgcheck = 0;
float buffer = 0;

void setup() {
  delay(500); // sanity delay

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  count = 0;
  avg = 0;
  while(count<10){
    raw = analogRead(analogPin);
    if(raw){
        buffer = raw * Vin;
        Vout = (buffer)/1024.0;
        buffer = (Vin/Vout) - 1;
        unknownR = knownR*buffer;
//        Serial.print("unknownR: ");
//        Serial.println(unknownR);

        count++;
        avg = (avg+unknownR);
        delay(50);
     }
  }
  
//  Serial.print("PreAvg: ");
//  Serial.println(avg);
//  Serial.print("Count: ");
//  Serial.println(count);
  avg = avg/count;
  Serial.print("Rough CAD Cell Resistance: ");
  Serial.println(avg);
  if(avg<900000){
    avgcheck++;
  }
  else{
    avgcheck--;
  }
  
  if(avgcheck>6){
    avgcheck = 6;
  }
  else if(avgcheck<0){
    avgcheck = 0;
  }
  Serial.print("Threshold (>=4?): ");
  Serial.println(avgcheck);

  if (avgcheck<4){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(relayPin, LOW);
    Serial.println("OFF\n");
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(relayPin, HIGH);
    Serial.println("ON\n");
    delay(1250);
  }
}
