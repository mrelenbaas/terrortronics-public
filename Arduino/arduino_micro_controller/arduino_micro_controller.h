// 2nd-party libraries.
#include "terrortronics_library.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void mainTimerFunction();
void minorTimerFunction();
void timeoutTimerFunction();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum pinEnum {
  pinButtonStart = 4,
  pinLightDebug = 13
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

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum lightEnum {
  lightDebug = 0
};
Light lights[] {
  Light(pinLightDebug)
};

////////////////////////////////////////////////////////////////////////
// Wifi ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Reused Variables ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int result;
bool isTarget;

////////////////////////////////////////////////////////////////////////
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int previousChar = 9;
bool isBlocked;
