#include <Arduino.h>

String responseBuffer = "";
String commandBuffer = "";

void setup() {
  //Open Serial to talk to PC, wait until it's working
  Serial.begin(115200);
  while(!Serial);
  
  //Open Serial connection to ESP8266 module
  Serial1.begin(115200);
  while(!Serial1);

  Serial.println("I'm running Command Capture Test");
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
    responseBuffer += Serial1.readStringUntil('\n') + '\n';
    //Check if this is the end of the Reponse TODO: Handle all possible response cases
    if(responseBuffer.endsWith("OK\r\n")||responseBuffer.endsWith("ERROR\r\n")){
      Serial.println("RECEIVED: " + responseBuffer); //Display to Serial Monitor
      responseBuffer = ""; //Clear Buffer
    }
  }
  //Otherwise, end loop
}
