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
#include "Arduino.h"
// 2nd-party libraries.
#include "terrortronics_library.h"

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void State::startRunning() {
  state = stateRunning;
}

void State::startAttract() {
  state = stateAttract;
}

void State::startTarget() {
  state = stateTarget;
}

void State::startUntarget() {
  state = stateUntarget;
}

int State::getState() {
  return state;
}

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
SerialClient::SerialClient() {
}

int SerialClient::readData() {
  incomingMessage = Serial.read();
  return incomingMessage;
}

void SerialClient::reset() {
  incomingMessage = -1;
  Serial.flush();
}

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Timer::Timer(unsigned int period, void (*delegateFunction)()) {
  this->period = period;
  this->delegateFunction = (*delegateFunction);
}

int Timer::updateTimer() {
  int result = updateTimerSuccessLessThanPeriod;
  previous = current;
  current = millis();
  delta = current - previous;
  if (delta < 0) {
    result = updateTimerErrorOverflow;
  }
  accumulated += delta;
  if (accumulated > period) {
    delegateFunction();
    result = updateTimerSuccessGreaterThanPeriod;
    accumulated -= period;
  }
  return result;
}

void Timer::reset() {
  accumulated = 0L;
}

void ButtonTimer::pseudoConstructor(unsigned long periodStart,
                                    unsigned long periodStop) {
  this->periodStart = periodStart;
  this->periodStop = periodStop;
}

int ButtonTimer::updateStart(bool isRunning, int *stateDebouncedByTime) {
  int result = -1;
  previous = current;
  current = millis();
  delta = current - previous;
  if (delta < 0) {
    delta = 0;
    result = -1;
  }
  accumulated += delta;
  if (accumulated >= periodStart) {
    reset();
    result = 1;
  } else {
    stateDebouncedByTime = 0;
  }
  return result;
}

int ButtonTimer::updateStop(bool isRunning, int *stateDebouncedByTime) {
  int result = -1;
  previous = current;
  current = millis();
  delta = current - previous;
  if (delta < 0) {
    delta = 0;
    result = -1;
  }
  accumulated += delta;
  if (accumulated >= periodStop) {
    reset();
    result = 1;
  } else {
    stateDebouncedByTime = 0;
  }
  return result;
}

void ButtonTimer::reset() {
  accumulated = 0L;
}

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
ButtonActiveLow::ButtonActiveLow(int pin,
                                 ButtonTimer buttonTimer,
                                 unsigned long periodStart,
                                 unsigned long periodStop,
                                 void (*delegateFunctionPress)(),
                                 void (*delegateFunctionRelease)()) {
  this->pin = pin;
  this->buttonTimer = buttonTimer;
  this->buttonTimer.pseudoConstructor(periodStart, periodStop);
  this->delegateFunctionPress = (*delegateFunctionPress);
  this->delegateFunctionRelease = (*delegateFunctionRelease);
  pinMode(pin, INPUT_PULLUP);
}

int ButtonActiveLow::updateButton() {
  state = !digitalRead(pin);
  return state;
}

int ButtonActiveLow::debounceByBlockPress() {
  int result = 0;
  if (isBlocked == 0) {
    isBlocked = 1;
    result = 1;
  }
  return result;
}

int ButtonActiveLow::debounceByBlockRelease() {
  int result = 0;
  if (isBlocked == 1) {
    isBlocked = 0;
    result = 1;
  }
  return result;
}

int ButtonActiveLow::debounceByPositionPress() {
  int result = 0;
  statePositionPrevious = statePositionCurrent;
  statePositionCurrent = stateDebouncedByTime;
  if (statePositionCurrent != statePositionPrevious) {
    if (statePositionCurrent && !statePositionPrevious) {
      result = 1;
    } else {
      // Empty.
    }
  }
  return result;
}

int ButtonActiveLow::debounceByPositionRelease() {
  int result = 0;
  statePositionPrevious = statePositionCurrent;
  statePositionCurrent = stateDebouncedByTime;
  if (statePositionCurrent != statePositionPrevious) {
    // Empty.
  } else {
    result = 1;
  }
  return result;
}

int ButtonActiveLow::debounceByTimePress() {
  int result = 0;
  if (state) {
    result = buttonTimer.updateStart(true, &stateDebouncedByTime);
    if (result == 1) {
      stateDebouncedByTime = true;
    }
  }
  return result;
}

int ButtonActiveLow::debounceByTimeRelease() {
  int result = 0;
  if (!state) {
    result = buttonTimer.updateStop(true, &stateDebouncedByTime);
    if (result == 1) {
      stateDebouncedByTime = true;
    }
  }
  return result;
}

void ButtonActiveLow::startTargeting() {
  isTarget = true;
}

void ButtonActiveLow::stopTargeting() {
  isTarget = false;
}

int ButtonActiveLow::debounceByTargetPress() {
  int result = 0;
  if (isTarget) {
    result = 1;
  }
  return result;
}

int ButtonActiveLow::debounceByTargetRelease() {
  int result = 0;
  if (isTarget) {
    result = 1;
  }
  isTarget = false;
  return result;
}

void ButtonActiveLow::reset() {
  statePositionPrevious = 0;
  statePositionCurrent = 0;
}

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Light::Light(int pin) {
  this->pin = pin;
  if (pin < 15) {
    pinMode(pin, OUTPUT);
  }
}

bool Light::toggle() {
  bool result;
  if (state) {
    turnOff();
  } else {
    turnOn();
    result = true;
  }
  return result;
}

bool Light::turnOn() {
  bool result;
  if (state == HIGH) {
    return result;
  }
  result = true;
  state = HIGH;
  if (pin < 15) {
    digitalWrite(pin, state);
  } else {
    analogWrite(pin, 200);
  }
  return result;
}

bool Light::turnOff() {
  bool result;
  if (state == LOW) {
    return result;
  }
  result = true;
  state = LOW;
  if (pin < 15) {
    digitalWrite(pin, state);
  } else {
    analogWrite(pin, 0);
  }
  return result;
}
