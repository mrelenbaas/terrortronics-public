// 2nd-party libraries.
#include "terrortronics_library.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void mainTimerFunction();
void minorTimerFunction();
void timeoutTimerFunction();
void redButtonFunctionPress();
void redButtonFunctionRelease();
void greenButtonFunctionPress();
void greenButtonFunctionRelease();
void blueButtonFunctionPress();
void blueButtonFunctionRelease();
void yellowButtonFunctionPress();
void yellowButtonFunctionRelease();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum pinEnum {
  pinButtonGreen = 5,
  pinButtonRed = 13,
  pinBuzzer = 14,
  pinLightBlue = 15,
  pinButtonBlue = 18,
  pinButtonYellow = 19,
  pinButtonReset = 20,
  pinButtonStart = 21,
  pinLightRed = 23,
  pinLightYellow = 32,
  pinLightGreen = 33
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
const unsigned int MAIN_PERIOD = 3000L;
Timer mainTimer = Timer(MAIN_PERIOD, mainTimerFunction);
Timer timeoutTimer = Timer(TIMEOUT_PERIOD, timeoutTimerFunction);

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
const unsigned long DEBOUNCE_PERIOD_START = 10L;
const unsigned long DEBOUNCE_PERIOD_STOP = 5L;
enum buttonEnum {
  buttonStart = 0,
  buttonRed = 1,
  buttonGreen = 2,
  buttonBlue = 3,
  buttonYellow = 4
};
ButtonActiveLow buttons[] = {
  ButtonActiveLow(
    pinButtonYellow,
    ButtonTimer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    startButtonFunctionPress,
    startButtonFunctionRelease),
  ButtonActiveLow(
    pinButtonRed,
    ButtonTimer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    redButtonFunctionPress,
    redButtonFunctionRelease),
  ButtonActiveLow(
    pinButtonGreen,
    ButtonTimer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    greenButtonFunctionPress,
    greenButtonFunctionRelease),
  ButtonActiveLow(
    pinButtonBlue,
    ButtonTimer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    blueButtonFunctionPress,
    blueButtonFunctionRelease),
  ButtonActiveLow(
    pinButtonYellow,
    ButtonTimer(),
    DEBOUNCE_PERIOD_START,
    DEBOUNCE_PERIOD_STOP,
    yellowButtonFunctionPress,
    yellowButtonFunctionRelease)
};

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum lightEnum {
  lightRed = 0,
  lightGreen = 1,
  lightBlue = 2,
  lightYellow = 3
};
Light lights[] {
  Light(pinLightRed),
  Light(pinLightGreen),
  Light(pinLightBlue),
  Light(pinLightYellow)
};

////////////////////////////////////////////////////////////////////////
// Wifi ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Reused Variables ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int result;

////////////////////////////////////////////////////////////////////////
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool isBlocked;
bool isTarget = true;
bool isScoreSent;
