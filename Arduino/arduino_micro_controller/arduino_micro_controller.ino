// 2nd-party libraries.
#include "arduino_micro_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  Keyboard.begin();
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
  Serial.println("HERE");
  lights[lightDebug].turnOn();
  if (!isTerminalStarted) {
    isTerminalStarted = true;
    startTerminal();
    startServer();
  } else {
    restartServer();
  }
}

void startButtonFunctionRelease() {
  lights[lightDebug].turnOff();
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
