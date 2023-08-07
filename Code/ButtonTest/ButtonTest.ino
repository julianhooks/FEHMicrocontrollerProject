void setup() {
  Serial.begin(115200);
  pinMode(47,INPUT);
  pinMode(48,INPUT);
  pinMode(49,INPUT);
  pinMode(50,INPUT);
}

void loop() {
  int pin = 50;
  
  if (digitalRead(pin)){
    Serial.println("HIGH");
  }
  else {
    Serial.println("LOW");
  }
}
