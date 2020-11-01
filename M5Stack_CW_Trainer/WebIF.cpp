/**************************************************************************
 * WEB Encode I/F Control
 *
 *************************************************************************/
#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>

#include "TrainerConfig.h"
#include "Encode.h"

WebServer server(80);

bool isWEBIFEnabled = false;

//ESP32 SoftAP Configuration
const char ssid[] = TRAINER_SSID;
const char pass[] = TRAINER_PASS;
const IPAddress ip(TRAINER_IP_ADDR);
const IPAddress subnet(TRAINER_SUBNET);

//Html for Encode Interface
const char html_string[] =
"<html>\
  <head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1\">\
  </head>\
  <body bgcolor=\"black\" text=\"white\">\
    <center><br><br>\
    <font size=\"6\" color=\"red\">M5</font><br>\
    <font size=\"5\">CW Encoder</font><hr><br>\
    <form action=\"/encode\" method=\"post\">\
        <p><input type=\"text\" name=\"enc_txt\"></p>\
        <p><input type=\"submit\" value=\"Encode\">\
           <input type=\"reset\" value=\"Reset\">\
        </p>\
    </form>\
    <br><br><br><br>powerd by M5Stack.\
    </center>\
  </body>\
</html>";

//Html for out of service
const char html_noService[] =
"<html><body bgcolor=\"black\" text=\"white\">\
    <center><br><br>\
    <font size=\"6\" color=\"red\">No Service</font><br>\
    <font size=\"5\">Enable WebI/F Mode..</font><hr><br>\
    </center>\
</body></html>";


void handleRoot() {
  //Serial.println("handle [/]." );
  if( isWEBIFEnabled == true ) {
    server.send(200, "text/html", html_string);
  } else {
    server.send(200, "text/html", html_noService);    
  }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleEncode() {
  //Serial.println("handle [/encode]." );

  if( isWEBIFEnabled == true ) {
    //Serial.printf("server.args [%d]\n", server.args() );
    if( server.args() >0 ){
      //Serial.printf("server.arg: [%s]\n", server.arg("enc_txt"));
      ENCODE_execEncode( server.arg("enc_txt") );
    } else {
      Serial.printf("NO ARGS...\n");
    }
    server.send(200, "text/html", html_string);
  } else {
    server.send(200, "text/html", html_noService);    
  }  
}

void WEBIF_setup_wifi() {
  //SoftAP
  WiFi.softAP(ssid,pass);
  delay(100);
  WiFi.softAPConfig(ip,ip,subnet);
  IPAddress myIP = WiFi.softAPIP();

  Serial.println("ESP32 SoftAP Mode starting...");
  Serial.printf("SSID:%s\n", ssid);
  Serial.printf("PASS:%s\n", pass);
  Serial.printf("Use 'http://");
  Serial.print(myIP);
  Serial.println("' to connect");

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.on("/encode", handleEncode);

  server.begin();
  Serial.println("HTTP server started.");

  //  isWEBIFEnabled = false;
  isWEBIFEnabled = true;
}

void WEBIF_handleClient(){
  server.handleClient();
}

void WEBIF_enable() {
  isWEBIFEnabled = true;
}

void WEBIF_disable() {
  isWEBIFEnabled = false;
}

bool WEBIF_isEnable() {
  return isWEBIFEnabled;
}
