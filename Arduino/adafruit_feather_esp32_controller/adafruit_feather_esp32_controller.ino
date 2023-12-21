#include <WiFi.h>
#include <WiFiMulti.h>
#include "adafruit_feather_esp32_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  wifiMulti.addAP("ESPap", "thereisnospoon");
  Serial.println("Connecting Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
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
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
  }
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
