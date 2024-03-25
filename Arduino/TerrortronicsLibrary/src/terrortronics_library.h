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

#ifndef Common_h
#define Common_h

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void resetFunction();
void startFunction();
void interruptFunction();
void startButtonFunctionPress();
void startButtonFunctionRelease();
void resetButtonFunctionPress();
void resetButtonFunctionRelease();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum stateEnum {
  stateAttract,
  stateRunning,
  stateTarget,
  stateUntarget
};
class State {
  public:
    void startRunning();
    void startAttract();
    void startTarget();
    void startUntarget();
    int getState();
  private:
    int state = -1;
};

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum serialEnum {
  serialZero = 48,
  serialOne = 49,
  serialTwo = 50,
  serialThree = 51,
  serialFour = 52,
  serialFive = 53,
  serialSix = 54,
  serialSeven = 55,
  serialEight = 56,
  serialNine = 57
};
enum connectedEnum {
  connectedFeather = 0,
  connectedDue = 1,
  connectedMicro = 2,
  connectedNano = 3,
  connectedUno = 4
};
const int BAUD_RATE = 9600;
const int SERIAL_BUFFER_SIZE2 = 2;
class SerialClient {
  public:
    SerialClient();
    int readData();
    void reset();
  private:
    int incomingMessage;
};

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum updateTimerResult {
  updateTimerErrorOverflow = -1,
  updateTimerSuccessLessThanPeriod = 0,
  updateTimerSuccessGreaterThanPeriod = 1
};
const unsigned int TIMEOUT_PERIOD = 10000L;
class Timer {
  public:
    Timer(unsigned int period, void (*)());
    int updateTimer();
    void reset();
  private:
    unsigned int previous;
    unsigned int current;
    unsigned int delta;
    unsigned int period;
    unsigned int accumulated;
    void (*delegateFunction)();
};

class ButtonTimer {
  public:
    void pseudoConstructor(unsigned long, unsigned long);
    int updateStart(bool, int *);
    int updateStop(bool, int *);
    void reset();
  private:
    unsigned long previous;
    unsigned long current;
    unsigned long delta;
    unsigned long accumulated;
    unsigned long periodStart;
    unsigned long periodStop;
};

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
class ButtonActiveLow {
  public:
    ButtonActiveLow(int,
                    ButtonTimer,
                    unsigned long,
                    unsigned long,
                    void (*)(),
                    void (*)());
    int printDefinitions();
    int updateButton();
    int debounceByBlockPress();
    int debounceByBlockRelease();
    int debounceByPositionPress();
    int debounceByPositionRelease();
    int debounceByTargetPress();
    int debounceByTargetRelease();
    int debounceByTimePress();
    int debounceByTimeRelease();
    void startTargeting();
    void stopTargeting();
    void reset();
    void (*delegateFunctionPress)();
    void (*delegateFunctionRelease)();
  private:
    int pin;
    bool state;
    int stateDebouncedByTime;
    int statePositionPrevious;
    bool statePositionCurrent;
    bool isTarget;
    int isBlocked;
    ButtonTimer buttonTimer;
};

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
class Light {
  public:
    Light(int);
    bool toggle();
    bool turnOn();
    bool turnOff();
  private:
    int pin;
    bool state;
};

#endif
