// Copyright 2024 Bradley Elenbaas
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// 2nd-party libraries.
#include "arduino_uno_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(12, LOW);
  delay(1000);
  digitalWrite(12, HIGH);
  buttonsSize = sizeof(buttons) / sizeof(ButtonActiveLow);
}

void loop() {
  result = mainTimer.updateTimer();
  switch (result) {
    case updateTimerErrorOverflow:
      return;
    case updateTimerSuccessLessThanPeriod:
      break;
    case updateTimerSuccessGreaterThanPeriod:
      minorTimerFunction();
      break;
  }
  timeoutTimer.updateTimer();
  for (unsigned int i = 0; i < buttonsSize; ++i) {
    if (buttons[i].updateButton() == 1) {
      if (buttons[i].debounceByTimePress() == 1) {
        if (buttons[i].debounceByPositionPress() == 1) {
          if (buttons[i].debounceByBlockPress() == 1) {
            if (buttons[i].debounceByTargetPress() == 1) {
              switch (state.getState()) {
                case stateAttract:
                  break;
                case stateRunning:
                  break;
                case stateTarget:
                  break;
                case stateUntarget:
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
                case stateAttract:
                  break;
                case stateRunning:
                  break;
                case stateTarget:
                  break;
                case stateUntarget:
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
  if (Serial.available() > 0) {
    switch (serialClient.readData()) {
      case '0':
        Serial.print((unsigned char)0);
        break;
      case '1':
        Serial.print((unsigned char)1);
        break;
      case '2':
        Serial.print((unsigned char)2);
        break;
      case '3':
        Serial.print((unsigned char)3);
        break;
      case '4':
        Serial.print((unsigned char)4);
        break;
      case '5':
        Serial.print((unsigned char)5);
        break;
      case '6':
        Serial.print((unsigned char)6);
        break;
      case '7':
        if (!isBlocked) {
          Serial.print((unsigned char)7);
          lights[lightDebug].turnOff();
          isBlocked = true;
          isTarget = false;
          isScoreSent = false;
        }
        break;
      case '8':
        if (!isBlocked) {
          Serial.print((unsigned char)8);
          lights[lightDebug].turnOn();
          isBlocked = true;
          isTarget = true;
          isScoreSent = false;
        }
        break;
      case '9':
        break;
      default:
        break;
    }
  }
  serialClient.reset();
  delay(10);
}

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void mainTimerFunction() {
  isBlocked = false;
  switch (state.getState()) {
    case stateAttract:
      break;
    case stateRunning:
      break;
    case stateTarget:
      break;
    case stateUntarget:
      break;
  }
}

void minorTimerFunction() {
  switch (state.getState()) {
    case stateAttract:
      break;
    case stateRunning:
      break;
    case stateTarget:
      break;
    case stateUntarget:
      break;
  }
}

void timeoutTimerFunction() {
  switch (state.getState()) {
    case stateAttract:
      break;
    case stateRunning:
      state.startAttract();
      break;
    case stateTarget:
      break;
    case stateUntarget:
      break;
  }
}

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void startButtonFunctionPress() {
  if (digitalRead(pinLightDebug) == HIGH) {
    if (isTarget) {
      if (!isScoreSent) {
        Serial.print((unsigned char)1);
        isScoreSent = true;
        delay(1000);
        digitalWrite(12, LOW);
      }
    }
  }
}

void startButtonFunctionRelease() {
  digitalWrite(12, HIGH);
}

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Wifi ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Mouse and Keyboard //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Reused Variables ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
