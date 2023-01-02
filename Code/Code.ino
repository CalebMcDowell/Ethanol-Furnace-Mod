const int sensorPin = 5;
const int relayPin = 3;
const int analogPin = 0;
int raw = 0;
int count = 0;
const int Vin = 5;
float Vout = 0;
const float R1 = 200000;
float R2 = 0;
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
        R2 = R1*buffer;
//        Serial.print("R2: ");
//        Serial.println(R2);
  
        count++;
        avg = (avg+R2);
        delay(75);
      }
  }
//      Serial.print("PreAvg: ");
//      Serial.println(avg);
//      Serial.print("Count: ");
//      Serial.println(count);
      avg = avg/(count);
      Serial.print("Avg: ");
      Serial.println(avg);
      if(avg>150000){
        avgcheck++;
      }
      else{
        avgcheck--;
        if(avgcheck<0){
          avgcheck = 0;
        }
      }
      if(avgcheck>6){
        avgcheck--;
      }
      Serial.print("AvgCheck: ");
      Serial.println(avgcheck);
      Serial.println("\n");
      
      if (avgcheck<4) {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(relayPin, LOW);
      }
      else {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(relayPin, HIGH);
        delay(2000);
      }
}
