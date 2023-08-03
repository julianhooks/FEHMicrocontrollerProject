#include <Arduino.h>

#define BUFFERSIZE 512

char commandBuffer[BUFFERSIZE]; 
char responseBuffer[BUFFERSIZE];
int commandBufferCharCount = 0;
int responseBufferCharCount = 0;

void setup() {
  //Open Serial to talk to PC, wait until it's working
  Serial.begin(115200);
  while(!Serial); //Ensure Serial Port opens //TODO: Add timeout
  
  //Open Serial connection to ESP8266 module
  Serial1.begin(115200);
  while(!Serial1); //Ensure Serial Port opens //TODO: Add timeout

  Serial.println("CharPtr test");
}

void loop() {
  //Listen for command from Serial
  if(Serial.available() > 0){
    if(commandBufferCharCount >= BUFFERSIZE) {
      Serial.println("Command exceeds character limit. Commands must be no more than 512 characters in length");
      commandBufferCharCount = 0;
    }
    commandBuffer[commandBufferCharCount] = char(Serial.read());
    if(commandBuffer[commandBufferCharCount] == char(10)){
      if(Serial.availableForWrite()){
        //Adjust for AT standard, since\r character isn't included by default
        commandBuffer[commandBufferCharCount] = '\r';
        commandBuffer[++commandBufferCharCount] = '\n';
        Serial1.write(commandBuffer,commandBufferCharCount+1);
        Serial.print("SENT: "); //Display to Serial Monitor
        Serial.write(commandBuffer, commandBufferCharCount+1);
        commandBufferCharCount = 0;
      }
      else {
        Serial.println("Failed to send command.");
        commandBufferCharCount = 0;
      }
    }
    else {
      commandBufferCharCount++;
    }
  }  
  //If no command in buffer, skip this step

  //Listen for response from Serial1
  if(Serial1.available() > 0){
    //Serial.println("Available");
    if(responseBufferCharCount >= BUFFERSIZE) {
      Serial.println(responseBuffer);
      responseBufferCharCount = 0;
    }
    responseBuffer[responseBufferCharCount] = char(Serial1.read());
    if(responseBuffer[responseBufferCharCount] == char(10)){
      Serial.print("RECEIVED: "); //Display to Serial Monitor
      Serial.write(responseBuffer,responseBufferCharCount + 1);
      responseBufferCharCount = 0;
    }
    else {
      responseBufferCharCount++;
    }
  }
  //Otherwise, end loop
}
