#include <Arduino.h>
#include <SparkFunESP8266WiFi.h>
#include <SparkFunESP8266Client.h>
#include <HttpClient.h>

//Structure of this example is taken from SimpleHTTPExample.ino
// Server put content in response headers, so that check had to be removed. The response status code check was also failing, so it was removed

const char mySSID[] = "Test";
const char myPSK[] = "";

char server[] = "10.42.0.1";
char path[] = "/a";
int timeout = 3000;

void setup() 
{
  Serial.begin(115200);
  while (esp8266.begin() != true)
  {
    Serial.print("Error connecting to ESP8266.");
  delay(1000);
  }
  
  if (esp8266.status() <= 0)
  {
    while (esp8266.connect(mySSID, myPSK) < 0)
      delay(1000);
  }
  delay(1000);

  Serial.println(esp8266.test());
  Serial.println(esp8266.ping("10.42.0.1"));
}

void loop()
{
int err =0;
  
  ESP8266Client c;
  HttpClient http(c);
  
  err = http.get(server,path);
  if (err == 0)
  {
    Serial.println("startedRequest ok");
    err = http.responseStatusCode();
    Serial.print("Got status code: ");
    Serial.println(err);
    
    // Usually you'd check that the response code is 200 or a
    // similar "success" code (200-299) before carrying on,
    // but we'll print out whatever response we get
    
    int bodyLen = http.contentLength();
    Serial.print("Content length is: ");
    Serial.println(bodyLen);
    Serial.println();
    Serial.println("Body returned follows:");
    
    // Now we've got to the body, so we can print it out
    unsigned long timeoutStart = millis();
    char c;
    // Whilst we haven't timed out & haven't reached the end of the body
    while ( (http.connected() || http.available()) &&
           ((millis() - timeoutStart) < timeout) )
    {
      if (http.available())
      {
          c = http.read();
          // Print out this character
          Serial.print(c);
         
          bodyLen--;
          // We read something, reset the timeout counter
          timeoutStart = millis();
      }
      else
      {
          // We haven't got any data, so let's pause to allow some to
          // arrive
          delay(timeout);
      }
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();
  delay(5000);
  Serial.print("\n\n\n");
}
