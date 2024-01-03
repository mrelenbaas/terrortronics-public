// 2nd-party libraries.
#include "arduino_due_controller.h"

void setup() {
  Serial.begin(BAUD_RATE);
  Keyboard.begin();
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
  serialReset();
  state.startAttract();
  //keyboardTimer.reset();
  //startTerminal();
  //startServer();
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
  // The Due, Uno, Micro, or Teensy sets this after their own double-confirmation.
  if (digitalRead(49) == LOW) {
    sprintf(serialBuffer, "%dd\0", connectedDue);
    Serial.print(serialBuffer);
    isIncoming = false;
  } else if (digitalRead(50) == LOW) {
    sprintf(serialBuffer, "%de\0", connectedDue);
    Serial.print(serialBuffer);
    isIncoming = false;
  } else if (digitalRead(51) == LOW) {
    sprintf(serialBuffer, "%df\0", connectedDue);
    Serial.print(serialBuffer);
    isIncoming = false;
  } else if (digitalRead(52) == LOW) {
    sprintf(serialBuffer, "%dg\0", connectedDue);
    Serial.print(serialBuffer);
    isIncoming = false;
  } else if (digitalRead(53) == LOW) {
    sprintf(serialBuffer, "%dh\0", connectedDue);
    Serial.print(serialBuffer);
    isIncoming = false;
  }
  if (Serial.available() > 0) {
    switch (serialClient.readData()) {
      case '0':
        sprintf(serialBuffer, "%d%d\0", connectedDue, 1);
        Serial.print(serialBuffer);
        break;
      case '1':
        sprintf(serialBuffer, "%d%d\0", connectedDue, 2);
        Serial.print(serialBuffer);
        break;
      case '2':
        targetIndex = 0;
        if (targetIndex == 0) {
          sprintf(serialBuffer, "%d%d\0", connectedDue, random(3, 7));
        }
        Serial.print(serialBuffer);
        break;
      case '3':
        digitalWrite(44, LOW);
        isIncoming = true;
        break;
      case '4':
        break;
      case '5':
        break;
      case '6':
        break;
      case '7':
        lights[lightDebug].turnOff();
        /*
        if (digitalRead(pinLightDebug) == LOW) {
          lights[lightDebug].turnOn();
        } else {
          lights[lightDebug].turnOff();
        }
        */
        break;
      case '8':
        lights[lightDebug].turnOn();
        /*
        if (digitalRead(pinLightDebug) == LOW) {
          lights[lightDebug].turnOn();
        } else {
          lights[lightDebug].turnOff();
        }
        */
        break;
      case '9':
        break;
      default:
        break;
    }
  }
  serialClient.reset();
  /*
  if (Serial.available() > 0) {
    incomingMessage = Serial.read();
    switch (incomingMessage) {
      case '0':
        sprintf(serialBuffer, "%d%d\0", connectedDue, 1);
        Serial.print(serialBuffer);
        break;
      case '1':
        sprintf(serialBuffer, "%d%d\0", connectedDue, 2);
        Serial.print(serialBuffer);
        break;
      case '2':
        targetIndex = 0;
        if (targetIndex == 0) {
          sprintf(serialBuffer, "%d%d\0", connectedDue, 3);
        }
        Serial.print(serialBuffer);
        break;
      case '3':
        digitalWrite(44, LOW);
        isIncoming = true;
        break;
      case '4':
        //restartServer();
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
  incomingMessage = -1;
  Serial.flush();
  */
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
void serialReset() {
  for (unsigned int i = 0; i < (sizeof(serialBuffer) / sizeof(serialBuffer[0])); ++i) {
    serialBuffer[i] = '\0';
  }
}

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void mainTimerFunction() {
  sprintf(serialBuffer, "%d%d\0", connectedDue, 9);
  Serial.print(serialBuffer);
  isBlocked = false;
  isBlocked2 = false;
  //if (!isBlocked) {
  //  sprintf(serialBuffer, "%d\0", 0);
  //  Serial.print(serialBuffer);
  //}
}

void minorTimerFunction() {
  /*
  switch (state.getState()) {
    case stateAttract:
      result = lights[lightDebug].toggle();
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
  //digitalWrite(7, LOW);
  timeoutTimer.reset();
  state.startRunning();
}

void startButtonFunctionRelease() {
  lights[lightDebug].turnOff();
  //digitalWrite(7, HIGH);
  timeoutTimer.reset();
  //state.startRunning();
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
void targetTimerFunction8() {
  digitalWrite(8, HIGH);
}

void targetTimerFunction9() {
  digitalWrite(9, HIGH);
}

void targetTimerFunction10() {
  digitalWrite(10, HIGH);
}

void targetTimerFunction11() {
  digitalWrite(11, HIGH);
}

void targetTimerFunction12() {
  digitalWrite(12, HIGH);
}

//void keyboardRelease() {
/*
  if (isKeyboardBlocked) {
  keyboardTimer.reset();
  return;
  }
  switch (keyIndex) {
  case 0:
    Keyboard.press(KEY_LEFT_CTRL);
    break;
  case 1:
    Keyboard.press(KEY_LEFT_ALT);
    break;
  case 2:
    Keyboard.press('t');
    break;
  case 3:
    Keyboard.release(KEY_LEFT_CTRL);
    break;
  case 4:
    Keyboard.release(KEY_LEFT_ALT);
    break;
  case 5:
    Keyboard.release('t');
    break;
  default:
    keyIndex = 0;
    isKeyboardBlocked = true;
    break;
  }
  ++keyIndex;
  keyboardTimer.reset();
*/
//}

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
  //delay(5000);
  Keyboard.press(KEY_LEFT_CTRL);
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.press('z');
  delay(DELAY_BETWEEN_KEY_PRESS);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release('z');
  //delay(10000);
}

void restartServer() {
  stopServer();
  delay(1000);
  startServer();
}
