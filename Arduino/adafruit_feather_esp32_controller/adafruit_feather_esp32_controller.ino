#include <WiFi.h>
//#include <WiFiMulti.h>
//#include <WiFiClient.h>
#include <WiFiAP.h>
#include "adafruit_feather_esp32_controller.h"

// Set these to your desired credentials.
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

WiFiServer server(80);

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println();
  Serial.println("Configuring access point...");
  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
  //wifiMulti.addAP("ESPap", "thereisnospoon");
  //Serial.println("Connecting Wifi...");
  //if (wifiMulti.run() == WL_CONNECTED) {
  //  Serial.println("WiFi connected");
  //  Serial.println("IP address: ");
  //  Serial.println(WiFi.localIP());
  //}
  state.startWaiting();
}

void loop() {
  result = mainTimer.updateTimer();
  switch (result)
  {
    case updateTimerErrorOverflow:
      return;
    case updateTimerSuccessLessThanPeriod:
      // Do nothing.
      break;
    case updateTimerSuccessGreaterThanPeriod:
      // The mainTimerFunction() is called automatically.
      minorTimerFunction();
      break;
  }
  timeoutTimer.updateTimer();
  for (unsigned int i = 0; i < (sizeof(buttons) / sizeof(ButtonActiveLow)); ++i) {
    if (buttons[i].updateButton() == 1) {
      if (buttons[i].debounceByTimePress() == 1) {
        if (buttons[i].debounceByPositionPress() == 1) {
          if (buttons[i].debounceByBlockPress() == 1) {
            if (buttons[i].debounceByTargetPress() == 1) {
              switch (state.getState()) {
                case stateWaiting:
                  // Do nothing.
                  break;
                case stateRunning:
                  // Do nothing.
                  break;
              }
            }
            buttons[i].delegateFunctionPress();
          }
        }
      }
    } else {
      if (buttons[i].debounceByTimeRelease() == 1) {
        if (buttons[i].debounceByPositionRelease() == 1) {
          if (buttons[i].debounceByBlockRelease() == 1) {
            if (buttons[i].debounceByTargetRelease() == 1) {
              switch (state.getState()) {
                case stateWaiting:
                  // Do nothing.
                  break;
                case stateRunning:
                  // Do nothing.
                  break;
              }
            }
            buttons[i].delegateFunctionRelease();
          }
        }
        buttons[i].reset();
      }
    }
  }
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          //digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          //digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void mainTimerFunction() {
  Serial.println(millis());
}

void minorTimerFunction() {
  switch (state.getState()) {
    case stateWaiting:
      for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
        lights[i].toggle();
      }
      break;
    case stateRunning:
      // Do nothing.
      break;
  }
  //if (wifiMulti.run() != WL_CONNECTED) {
  //  Serial.println("WiFi not connected!");
  //}
}

void timeoutTimerFunction() {
  switch (state.getState()) {
    case stateWaiting:
      // Do nothing.
      break;
    case stateRunning:
      state.startWaiting();
      break;
  }
}

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void startButtonFunctionPress() {
  for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
    lights[i].turnOn();
  }
  timeoutTimer.reset();
}

void startButtonFunctionRelease() {
  for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
    lights[i].turnOff();
  }
  timeoutTimer.reset();
  state.startRunning();
}

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Wifi ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Reused Variables ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
