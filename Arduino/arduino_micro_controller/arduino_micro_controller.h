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

// 1st-party libraries.
#include <Keyboard.h>
#include <Mouse.h>
// 2nd-party libraries.
#include "terrortronics_library.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void mainTimerFunction();
void stripTimerFunction();
void minorTimerFunction();
void timeoutTimerFunction();
void startChillHopLounge();
void startTerminal();
void startServer();
void stopServer();
void restartServer();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum pinEnum {
  pinLightDebug = 5,
  pinLightRazer = 6,
  pinlightStripPowerPower = 7, // TODO: Fix capitalization.
  pinlightStripPowerState = 8, // TODO: Fix capitalization.
  pinLightRedLeft = 9,
  pinLightRedRight = 10,
  pinLightGreenLeft = 11,
  pinLightGreenRight = 12,
  pinButtonStart = 13,
  //pinLightYellowRight = 14,
  //pinLightBlueLeft = 15,
  //pinLightBlueRight = 16,
  //pinLightYellowLeft = 17,
  //pinLightYellowMiddleleft = 18,
  //pinLightYellowMiddleright = 19
};

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The state of the game.
*/
State state = State();

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
char serialBuffer[2];
SerialClient serialClient;

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
const unsigned int MAIN_PERIOD_MAX = 20;
const unsigned int MAIN_PERIOD_MIN = 0;
const unsigned int MAIN_PERIOD_STEP = 50;
const unsigned int MINOR_PERIOD = 10000;
const unsigned int STRIP_PERIOD = 300L;
unsigned int mainPeriod = MAIN_PERIOD_MAX;
bool isStripBlocked = true;
Timer mainTimer = Timer(MAIN_PERIOD_MAX, mainTimerFunction);
Timer minorTimer = Timer(MINOR_PERIOD, minorTimerFunction);
Timer stripTimer = Timer(STRIP_PERIOD, stripTimerFunction);
Timer timeoutTimer = Timer(TIMEOUT_PERIOD, timeoutTimerFunction);
const long DELAY_BETWEEN_KEY_PRESS = 10;

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
const unsigned long DEBOUNCE_PERIOD_START = 10L;
const unsigned long DEBOUNCE_PERIOD_STOP = 50L;
enum buttonEnum {
  buttonStart = 0
};
ButtonActiveLow buttons[] = {
  ButtonActiveLow(
    pinButtonStart,
    ButtonTimer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    startButtonFunctionPress,
    startButtonFunctionRelease)
};
unsigned int buttonsSize;

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
const int ANALOG_MIN = 0;
const int ANALOG_MAX = 255;
const int COUNT_MIN = 0;
const int COUNT_MAX = 72;
int count;
bool isStripOn;
enum lightEnum {
  lightDebug = 0,
  lightRazer = 1,
  lightStripPower = 2,
  lightStripState = 3,
  lightRedLeft = 4,
  lightRedRight = 5,
  lightGreenLeft = 6,
  lightGreenRight = 7,
  //lightBlueLeft = 8,
  //lightBlueRight = 9,
  //lightYellowLeft = 10,
  //lightYellowMiddleleft = 11,
  //lightYellowMiddleright = 12,
  //lightYellowRight = 13
};
Light lights[] {
  Light(pinLightDebug),
  Light(pinLightRazer),
  Light(pinlightStripPowerPower),
  Light(pinlightStripPowerState),
  Light(pinLightRedLeft),
  Light(pinLightRedRight),
  Light(pinLightGreenLeft),
  Light(pinLightGreenRight),
  //Light(pinLightBlueLeft),
  //Light(pinLightBlueRight),
  //Light(pinLightYellowLeft),
  //Light(pinLightYellowMiddleleft),
  //Light(pinLightYellowMiddleright),
  //Light(pinLightYellowRight)
};

////////////////////////////////////////////////////////////////////////
// Wifi ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Mouse and Keyboard //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
const int DELAY_FOR_APPLICATION_LAUNCH = 30000;
const int DELAY_BEFORE_CLICKS = 3000;
const int DELAY_BETWEEN_CLICKS = 200;
const int X_POSITION = 960;
const int Y_POSITION = 540;
char TERMINAL_STARTUP[] = {
  's',
  'h',
  ' ',
  's',
  't',
  'a',
  'r',
  't',
  'u',
  'p',
  '.',
  's',
  'h'
};

////////////////////////////////////////////////////////////////////////
// Reused Variables ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int result;

////////////////////////////////////////////////////////////////////////
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int previousChar = 9;
bool isBlocked;
bool isTarget;
bool isScoreSent;
bool isTerminalStarted;
