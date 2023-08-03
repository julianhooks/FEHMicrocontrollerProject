#include <LiquidCrystal.h>

LiquidCrystal lcd(36,37,38,39,40,41,42,43,44,45,46);

//Initialize to empty since they're appended rather than set
String commandBuffer = ""; 
String responseBuffer = "";

void setup() {
  //Open Serial to talk to PC, wait until it's working
  Serial.begin(115200);
  while(!Serial);
  
  //Open Serial connection to ESP8266 module
  Serial1.begin(115200);
  while(!Serial1);

  //Initialize LCD screen
  lcd.begin(16,2);
  lcd.autoscroll();
}

void loop() {
   //Listen for command from Serial
  if(Serial.available() > 0){
    //If command in buffer, read buffer into memory and send to Serial1
    commandBuffer = Serial.readStringUntil('\n');
    Serial1.println(commandBuffer); //Send to ESP
    Serial.println("SENT: " + commandBuffer); //Display to Serial Monitor
    commandBuffer = ""; //Clear Buffer
  }  
  //If no command in buffer, skip this step

  //Listen for response from Serial1
  if(Serial1.available() > 0){
    //If there is a response in the buffer, read buffer into memory and send it to Serial
    responseBuffer = Serial1.readStringUntil('\n');
    Serial.println("RECEIVED: " + responseBuffer); //Display to Serial Monitor
    responseBuffer = ""; //Clear Buffer
  }
  //Otherwise, end loop
}
