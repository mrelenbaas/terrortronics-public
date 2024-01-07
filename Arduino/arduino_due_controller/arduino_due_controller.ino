// 2nd-party libraries.
#include "arduino_due_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, INPUT_PULLUP);
  pinMode(50, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
  state.startAttract();
  lights[lightDebug].turnOff();
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
        break;
      case '1':
        break;
      case '2':
        if (targetIndex == 3) {
          Serial.print((unsigned char)3);
          lights[lightDebug].turnOff();
          isTarget = false;
          isScoreSent = false;
        } else if (targetIndex == 4) {
          Serial.print((unsigned char)4);
          lights[lightDebug].turnOn();
          isTarget = true;
          isScoreSent = false;
        } else if (targetIndex == 5) {
          Serial.print((unsigned char)5);
          lights[lightDebug].turnOff();
          isTarget = false;
          isScoreSent = false;
        } else if (targetIndex == 6) {
          Serial.print((unsigned char)6);
          lights[lightDebug].turnOff();
          isTarget = false;
          isScoreSent = false;
        }
        targetIndex = random(3, 6);
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
        break;
      case '8':
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
  Serial.print((unsigned char)9);
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
  if (isTarget) {
    if (!isScoreSent) {
      Serial.print((unsigned char)1);
      isIncoming = false;
      isScoreSent = true;
    }
  }
}

void startButtonFunctionRelease() {
  timeoutTimer.reset();
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
