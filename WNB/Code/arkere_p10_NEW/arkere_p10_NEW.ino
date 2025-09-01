//#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DMDESP.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/Mono5x7.h>

// #include "PageIndex.h" 
//ESP8266WebServer server(80);
AsyncWebServer server(80);

const char* ssid = "runshaw2g";
const char* password = "143Runshaw$";


#define DISPLAYS_WIDE 4 //--> Panel Columns
#define DISPLAYS_HIGH 1 //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

char *Text[] = {"WELCOME to ARKERE POLYTECHNIC COLLEGE"}; //--> Variable for scrolling Text. Don't leave this variable blank
String Incoming_Text = ""; 

const char* PARAM_INPUT_1 = "input1";
String message;
String inputParam;
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>GOVT. POLYTECHNIC ARKERE</title>
  <meta name="viewport" content="width=device-width, initial-scale=5">
<p> <font size="9" face="sans-serif"> <marquee> GOVT. POLYTECHNIC ARKERE </marquee> </font> </p>
  </head><body><center>
  <form action="/get">
    Enter Text to Display: <input type="text" name="input1">
    <input type="submit" value="Send">
  </form><br>
 
</center></body></html>)rawliteral";
 
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

//void handleRoot() {
//  server.send(200, "text/html", MAIN_page); //--> Send web page
//}

void handle_Incoming_Text(String data) {
  Incoming_Text = data;
//  server.send(200, "text/plane", ""); //--> Send web page
  Process_Incoming_Text();
}

void Process_Incoming_Text() {
  delay(500);
  Serial.println("Incoming text : ");
  Serial.println(Incoming_Text);
  Serial.println();
  int str_len = Incoming_Text.length() + 1;
  char char_array[str_len];
  Incoming_Text.toCharArray(char_array, str_len);
  strcpy(Text[0], char_array);
  Incoming_Text = "";
}
 
void setup(){
  Serial.begin(115200);
  //delay(500);

  //----------------------------------------DMDESP Setup
  Disp.start(); //--> Run the DMDESP library
  Disp.setBrightness(50); //--> Brightness level
  Disp.setFont(Mono5x7); //--> Determine the font used
  //----------------------------------------
//  
//  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point
//  Serial.println("");
//  
//  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
//  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
//  Serial.println(ssid);
//  Serial.print("Visit this IP : ");
//  Serial.print(apip); //--> Prints the IP address of the server to be visited
//  Serial.println(" in your browser.");
// 
//  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
//  server.on("/setText", handle_Incoming_Text);  //--> Routine to handle handle_Incoming_Text Subroutines
//  
//  server.begin(); //--> Start server
//  Serial.println("HTTP server started");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
 
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //String message;
    //String inputParam;
    if (request->hasParam(PARAM_INPUT_1)) {
      message = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      handle_Incoming_Text(message);
      //Text = message;
//       lcd.clear();
//      lcd.setCursor(0,1);
//      lcd.print(message);
    }
    else {
      message = "No message sent";
      handle_Incoming_Text(message);
      inputParam = "none";
    }
    Serial.println(message);
   
  request->send(200, "text/html", index_html);
  });
  server.onNotFound(notFound);
  server.begin();
}


void loop(){
//  server.handleClient();  //--> Handle client requests

  Disp.loop(); //--> Run "Disp.loop" to refresh the LED
  Disp.drawText(16, 0, "INSPIRE ACADEMY"); //--> Display text "Disp.drawText(x position, y position, text)"
  Scrolling_Text(9, 50); //--> Show running text "Scrolling_Text(y position, speed);"
}

void Scrolling_Text(int y, uint8_t scrolling_speed) {
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(Mono5x7);
  int fullScroll = Disp.textWidth(Text[0]) + width;
  if((millis() - pM) > scrolling_speed) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, Text[0]);
  }  
}
