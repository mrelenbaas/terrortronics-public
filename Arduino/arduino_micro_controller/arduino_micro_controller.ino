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
#include "arduino_micro_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  Keyboard.begin();
  state.startAttract();
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
      break;
  }
  result = minorTimer.updateTimer();
  result = stripTimer.updateTimer();
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
  bool result;
  isBlocked = false;
  switch (state.getState()) {
    case stateAttract:
      if (count > COUNT_MAX) {
        lights[lightDebug].turnOff();
        lights[lightRedLeft].turnOff();
        lights[lightRedRight].turnOff();
        lights[lightGreenLeft].turnOff();
        lights[lightGreenRight].turnOff();
        analogWrite(A0, ANALOG_MIN);
        analogWrite(A1, ANALOG_MIN);
        analogWrite(A2, ANALOG_MIN);
        analogWrite(A3, ANALOG_MIN);
        analogWrite(A4, ANALOG_MIN);
        analogWrite(A5, ANALOG_MIN);
        count = 0;
      } else {
        switch (count) {
          case 1:
            break;
          case 2:
            lights[lightDebug].turnOn();
            break;
          case 3:
          case 4:
          case 5:
            break;
          case 6:
            lights[lightRedRight].turnOn();
            break;
          case 7:
          case 8:
          case 9:
            break;
          case 10:
            lights[lightRedLeft].turnOn();
            break;
          case 11:
          case 12:
          case 13:
            break;
          case 14:
            lights[lightGreenLeft].turnOn();
            break;
          case 15:
          case 16:
          case 17:
            break;
          case 18:
            lights[lightGreenRight].turnOn();
            break;
          case 19:
          case 20:
          case 21:
            break;
          case 22:
            analogWrite(A1, ANALOG_MAX);
            break;
          case 23:
          case 24:
            break;
          case 25:
            analogWrite(A2, ANALOG_MAX);
            break;
          case 26:
          case 27:
            break;
          case 28:
            analogWrite(A0, ANALOG_MAX);
            break;
          case 29:
            break;
          case 30:
            analogWrite(A5, ANALOG_MAX);
            break;
          case 31:
            break;
          case 32:
            analogWrite(A3, ANALOG_MAX);
            break;
          case 33:
            break;
          case 34:
            analogWrite(A4, ANALOG_MAX);
            break;
          case 35:
            break;
          case 36:
            break;
        }
        break;
      case stateRunning:
        break;
      case stateTarget:
        break;
      case stateUntarget:
        break;
    }
  }
  ++count;
}

void stripTimerFunction() {
  bool result;
  switch (state.getState()) {
    case stateAttract:
      result = lights[lightRazer].turnOff();
      result = lights[lightStripState].turnOff();
      if (result == HIGH
          && isStripBlocked == false) {
        isStripBlocked = true;
      }
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
      isStripOn = !isStripOn;
      if (isStripOn) {
        lights[lightStripPower].turnOn();
      } else {
        lights[lightStripPower].turnOff();
      }
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
  lights[lightRazer].turnOn();
  result = lights[lightStripState].turnOn();
  if (result = HIGH
      && isStripBlocked == true) {
    isStripBlocked = false;
    stripTimer.reset();
  }
  /* TODO: Uncomment to reimplement IoTivity.
  if (!isTerminalStarted) {
    isTerminalStarted = true;
    startTerminal();
    startServer();
  } else {
    restartServer();
  }
  */
}

void startButtonFunctionRelease() {
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

////////////////////////////////////////////////////////////////////////
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void startTerminal() {
  delay(5000);
  Keyboard.press(KEY_LEFT_CTRL);
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.press(KEY_LEFT_ALT);
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.press('t');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release('t');
  delay(10000);
}

void startServer() {
  Keyboard.press('.');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('.');
  Keyboard.press('/');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('/');
  Keyboard.press('i');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('i');
  Keyboard.press('o');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('o');
  Keyboard.press('t');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('t');
  Keyboard.press('i');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('i');
  Keyboard.press('v');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('v');
  Keyboard.press('i');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('i');
  Keyboard.press('t');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('t');
  Keyboard.press('y');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('y');
  Keyboard.press('-');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('-');
  Keyboard.press('l');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('l');
  Keyboard.press('i');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('i');
  Keyboard.press('t');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('t');
  Keyboard.press('e');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('e');
  Keyboard.press('/');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('/');
  Keyboard.press('p');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('p');
  Keyboard.press('o');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('o');
  Keyboard.press('r');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('r');
  Keyboard.press('t');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('t');
  Keyboard.press('/');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('/');
  Keyboard.press('l');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('l');
  Keyboard.press('i');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('i');
  Keyboard.press('n');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('n');
  Keyboard.press('u');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('u');
  Keyboard.press('x');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('x');
  Keyboard.press('/');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('/');
  Keyboard.press('s');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('s');
  Keyboard.press('i');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('i');
  Keyboard.press('m');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('m');
  Keyboard.press('p');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('p');
  Keyboard.press('l');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('l');
  Keyboard.press('e');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('e');
  Keyboard.press('s');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('s');
  Keyboard.press('e');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('e');
  Keyboard.press('r');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('r');
  Keyboard.press('v');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('v');
  Keyboard.press('e');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('e');
  Keyboard.press('r');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release('r');
  Keyboard.press(KEY_RETURN);
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release(KEY_RETURN);
}

void stopServer() {
  Keyboard.press(KEY_LEFT_CTRL);
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.press('z');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release('z');
}

void restartServer() {
  stopServer();
  delay(1000);
  startServer();
}
