// 2nd-party libraries.
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
  //if (!isBlocked) {
    //if (isPumping) {
      Serial.print((byte)9);
    //  isPumping = false;
    //}
    if (Serial.available() > 0) {
      //isBlocked = true;
      switch (serialClient.readData()) {
        case '0':
          Serial.print((unsigned char)0);
          //isHeartbeatReceived = true;
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
          //sprintf(serialBuffer, "%d%d\0", connectedUno, 7);
          Serial.print((unsigned char)7);
          if (!isBlocked) {
            lights[lightDebug].turnOff();
            isBlocked = true;
          }
          //isBlocked = true;
          //isPumping = true;
          break;
        case '8':
          //sprintf(serialBuffer, "%d%d\0", connectedUno, 8);
          Serial.print((unsigned char)8);
          if (!isBlocked) {
            lights[lightDebug].turnOn();
            isBlocked = true;
          }
          //isBlocked = true;
          //isPumping = true;
          break;
        case '9':
          Serial.print((unsigned char)9);
          break;
        default:
          break;
      }
    }
  //}
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
  //sprintf(serialBuffer, "%d%d\0", connectedUno, 9);
  //Serial.print(serialBuffer);
  //Serial.print((byte)9);
  isBlocked = false;
}

void minorTimerFunction() {
  switch (state.getState()) {
    case stateAttract:
      //lights[lightDebug].toggle();
      break;
    case stateRunning:
      break;
    case stateTarget:
      //lights[lightDebug].turnOn();
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
