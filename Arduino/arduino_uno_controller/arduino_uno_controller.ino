#include "arduino_uno_controller.h"

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
                case stateAttract:
                  // Do nothing.
                  break;
                case stateRunning:
                  // Do nothing.
                  break;
                case stateTarget:
                  // Do nothing.
                  break;
                case stateUntarget:
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
                case stateAttract:
                  // Do nothing.
                  break;
                case stateRunning:
                  // Do nothing.
                  break;
                case stateTarget:
                  // Do nothing.
                  break;
                case stateUntarget:
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
  if (Serial.available() > 0) {
    switch (serialClient.readData()) {
      case '0':
        break;
      case '1':
        break;
      case '2':
        break;
      case '3':
        break;
      case '4':
        break;
      case '5':
        break;
      case '6':
        break;
      case '7':
        //sprintf(serialBuffer, "%d%d\0", connectedUno, 7);
        //Serial.print(serialBuffer);
        lights[lightDebug].turnOff();
        //isTarget = false;
        //state.startUntarget();
        //for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
        //  lights[i].turnOff();
        //}
        break;
      case '8':
        //sprintf(serialBuffer, "%d%d\0", connectedUno, 8);
        //Serial.print(serialBuffer);
        lights[lightDebug].turnOn();
        //isTarget = true;
        //state.startTarget();
        //for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
        //  lights[i].turnOn();
        //}
        break;
      case '9':
        break;
      default:
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
  sprintf(serialBuffer, "%d%d\0", connectedUno, 9);
  Serial.print(serialBuffer);
}

void minorTimerFunction() {
  /*
  switch (state.getState()) {
    case stateAttract:
      lights[lightDebug].toggle();
      break;
    case stateRunning:
      // Do nothing.
      break;
    case stateTarget:
      lights[lightDebug].turnOn();
      //for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
      //  lights[i].turnOn();
      //}
      break;
    case stateUntarget:
      //for (unsigned int i = 0; i < (sizeof(lights) / sizeof(Light)); ++i) {
      //  lights[i].turnOff();
      //}
      break;
  }
  */
}

void timeoutTimerFunction() {
  /*
  switch (state.getState()) {
    case stateAttract:
      // Do nothing.
      break;
    case stateRunning:
      state.startAttract();
      break;
    case stateTarget:
      // Do nothing.
      break;
    case stateUntarget:
      // Do nothing.
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
