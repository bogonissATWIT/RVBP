/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.
  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

//Libraries necessary for below code
#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <WiFiAP.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Variable declarations
float voltage;
const char *ssid = "Battery";
const char *password = "password1234";
String header;
WiFiServer server(80);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); //Initializes the display with -1 as the reset pin
//Some functions that need to be initialized first to be called right away
//DHT dht(4, DHT22); //Initalizes humid/temp sensor on pin 4 with make DHT22 
/*
void readv() {
  float voltage = (float)analogRead(36) / 4096 * 21 * 3728.814 / 3000;
}
*/
/* Function to read from the humidity sensor
void dht() {
  float hum = dht.readHumidity();
  float tempc = dht.readTemperature();
  float tempf = dht.readTemperature(true);
}
*/
void setup() {
  Serial.begin(115200);
  Serial.println();
  //dht.begin();
  //Initialization of the Access Point for client connection
  Serial.println("Configuring access point...");
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
  /* Initialization of the OLED display, commented out until PCB comes in and can be tested
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(voltage,1);
  display.println("v.<br>");
  display.println("IP address: ");
  display.print(myIP);
  */
}
      
void loop() {
  String hum = String(random(0,100));
  String tempf = String(random(10,130));
  String tempc = String(random(-20, 45));
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("New Client.");          // print a message out the serial port
    String currentLine = "";
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {
        char c = client.read();
        Serial.write(c);        //If client has information, read it and output to the serial monitor
        header += c;
        if (c == '\n') {
          if(currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            //Formatting for HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; text-align: center;}");
            client.println("h1 {background-color: #2a914e; border: groove; black: white; padding: 16px 30px;}");
            client.println("p {background-color: #000000; border: solid; padding: 16px 30px; color: white}");
            client.println("bad { color: #FF0000;}");
            client.println("good { color: #00FF00;}</style></head>");
            client.println("<h1>Battery Information</h1>");
            client.print("<p>Total Voltage/Voltage per Series Pack = 20.7V<br>");
            client.println("Battery Humidity = " + hum + "%<br>Safe?<good> Yes</good><br>");
            client.println("Battery Temperature = " + tempf + " F, " + tempc + " C<br>Safe?<bad> No</bad><br>");
            client.println("Battery Percentage = 98.5%</p>");
            client.println("</html>");
            client.println();
            break;
          }
          else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;    // add it to the end of the currentLine
        }
      }
    }
    header = "";
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}