// 2nd-party libraries.
#include "arduino_micro_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  state.startAttract();
}

void loop() {
  result = mainTimer.updateTimer();
  switch (result) {
    case updateTimerErrorOverflow:
      return;
    case updateTimerSuccessLessThanPeriod:
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
    //sprintf(serialBuffer, "%d%s\0", connectedMicro, serialClient.readData());
    //Serial.print(serialBuffer);
    switch (serialClient.readData()) {
      case '0':
        //previousChar = 0;
        break;
      case '1':
        //previousChar = 1;
        break;
      case '2':
        //previousChar = 2;
        break;
      case '3':
        //previousChar = 3;
        break;
      case '4':
        //previousChar = 4;
        break;
      case '5':
        //previousChar = 5;
        break;
      case '6':
        //previousChar = 6;
        break;
      case '7':
        if (!isBlocked) {
          //previousChar = 8;
          //sprintf(serialBuffer, "%d%d\0", connectedMicro, 7);
          Serial.print((byte)7);
          //digitalWrite(pinLightDebug, LOW);
          //lights[lightDebug].turnOff();
          if (digitalRead(pinLightDebug) == LOW) {
            lights[lightDebug].turnOn();
          } else {
            lights[lightDebug].turnOff();
          }
          mainTimer.reset();
          //serialClient.reset();
          //isTarget = false;
          //state.startUntarget();
          //for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
          //  lights[i].turnOff();
          //}
          isBlocked = true;
        }
        break;
      case '8':
        if (!isBlocked) {
          //previousChar = 7;
          //sprintf(serialBuffer, "%d%d\0", connectedMicro, 8);
          Serial.print((byte)8);
          //digitalWrite(pinLightDebug, HIGH);
          //lights[lightDebug].turnOn();
          if (digitalRead(pinLightDebug) == LOW) {
            lights[lightDebug].turnOn();
          } else {
            lights[lightDebug].turnOff();
          }
          mainTimer.reset();
          //serialClient.reset();
          //isTarget = true;
          //state.startTarget();
          //for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
          //  lights[i].turnOn();
          //}
          isBlocked = true;
        }
        break;
      case '9':
        //previousChar = 8;
        //previousChar = 9;
        break;
      case '\0':
        break;
      default:
        //sprintf(serialBuffer, "%d%d\0", connectedMicro, 0);
        //Serial.print(serialBuffer);
        //serialClient.reset();
        break;
    }
  }
  serialClient.reset();
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
  //sprintf(serialBuffer, "%d%d\0", connectedMicro, previousChar);
  Serial.print("29\0");
  isBlocked = false;
  //mainTimer.reset();
}

void minorTimerFunction() {
  /*
    switch (state.getState()) {
    case stateAttract:
      lights[lightDebug].toggle();
      break;
    case stateRunning:
      break;
    case stateTarget:
      for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
        lights[i].turnOn();
      }
      break;
    case stateUntarget:
      for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
        lights[i].turnOff();
      }
      break;
    }
  */
}

void timeoutTimerFunction() {
  /*
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
  */
}

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void startButtonFunctionPress() {
  lights[lightDebug].turnOn();
  timeoutTimer.reset();
}

void startButtonFunctionRelease() {
  lights[lightDebug].turnOff();
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

////////////////////////////////////////////////////////////////////////
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
