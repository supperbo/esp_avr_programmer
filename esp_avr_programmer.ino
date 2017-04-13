#include <ESP8266WiFi.h>
#include "WebServ.h"

#define RESET_PIN 4

const char* ssid = "SSID";
const char* password = "PASSWORD";

WiFiServer server(80);

WebServ webServ(RESET_PIN);

void setup()
{
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  
  server.begin();
}

void loop() {
  
  WiFiClient client = server.available(); 
  
  if (client) {
    String line = client.readStringUntil('\r');
    int httpCmd = webServ.GetCommand(line);
    String urlParam = webServ.GetUrlParam(line);
    
    if(httpCmd == webServ.httpCmdIndex) {
      webServ.WSCmdIndex(&client);
    } else if(httpCmd == webServ.httpCmdDelete) {
      webServ.WSCmdDelete(&client, urlParam);
    } else if(httpCmd == webServ.httpCmdFlash) {
      webServ.WSCmdFlash(&client, urlParam);
    } else if(httpCmd == webServ.httpCmdList) {
      webServ.WSCmdList(&client);
    } else if(httpCmd == webServ.httpCmdUpload) {
      webServ.WSCmdUpload(&client, urlParam);
    } else {
      webServ.WSCmdIndex(&client);
    }
    
    delay(1); 
    client.stop();
  }
}

void formatDevice() {

  SPIFFS.begin();
  SPIFFS.format();
  SPIFFS.end();
  
}














