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

#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

// 1st-party libraries.
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <windows.h>

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void incrementScore();
char digit(char);
void com(int);

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum stateEnum {
  stateWaiting,
  stateRunning
};
class State {
  public:
    void startRunning();
    void startWaiting();
    int getState();
  private:
    int state = -1;
};
State state = State();

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
enum connectedEnum {
  connectedFeather = '0',
  connectedDue = '1',
  connectedMicro = '2',
  connectedNano = '3',
  connectedUno = '4'
};
enum incomingEnum {
  incomingName = 0,
  incomingMessage = 1
};
const int BYTE_SIZE = 8;
const int BUFFER_SIZE = 1;
const int DEVICE_SIZE = 11;
const unsigned int NB_CHAR = 4;
class Serial {
    public:
        Serial(const char *);
        ~Serial();
        int readData(char *, unsigned int);
        void writeData(const char *);
        bool isConnected();
    private:
        HANDLE hSerial;
        bool connected;
        COMSTAT status;
        DWORD errors;
};
char incomingData[BUFFER_SIZE];
char data;
void findNextConnection();
Serial* SP;
Serial* serialFeather = NULL;
Serial* serialDue = NULL;
//Serial* serialMicro = NULL;
Serial* serialUno = NULL;
int deviceIndex;
unsigned int deviceSize;
char device[DEVICE_SIZE] = {
  '\\',
  '\\',
  '.',
  '\\',
  'C',
  'O',
  'M',
  '\0',
  '\0',
  '\0',
  '\0'
};
int serialIndex;
const int SERIAL_MAX = 4;
char deviceUno[DEVICE_SIZE] = {
  '\\',
  '\\',
  '.',
  '\\',
  'C',
  'O',
  'M',
  '\0',
  '\0',
  '\0',
  '\0'
};
char deviceDue[DEVICE_SIZE] = {
  '\\',
  '\\',
  '.',
  '\\',
  'C',
  'O',
  'M',
  '\0',
  '\0',
  '\0',
  '\0'
};
char deviceFeather[DEVICE_SIZE] = {
  '\\',
  '\\',
  '.',
  '\\',
  'C',
  'O',
  'M',
  '\0',
  '\0',
  '\0',
  '\0'
};
/*
char deviceMicro[DEVICE_SIZE] = {
  '\\',
  '\\',
  '.',
  '\\',
  'C',
  'O',
  'M',
  '\0',
  '\0',
  '\0',
  '\0'
};
* */

////////////////////////////////////////////////////////////////////////
// Timers //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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
const char receivedHeartbeat[] = {'0'};
const char receivedConfirmation[] = {'1'};
const char requestRandom[] = {'2'};
//const char targetArduinoDue[] = {'3', '\0'};
//const char targetArduinoMicro[] = {'4', '\0'};
//const char targetArduinoUno[] = {'5', '\0'};
//const char targetTeensyLC[] = {'6', '\0'};
//const char targetFeatherESP32[] = {'7', '\0'};
//unsigned char setUntarget0 = '7';
const char setUntarget[] = {'7'};
const char setTarget[] = {'8'};
const char setHeartbeat[] = {'8'};
//const char two[] = {'2'};
//const char three[] = {'3'};
//const int SERIAL_BUFFER_SIZE = 256;
//char serialBuffer[SERIAL_BUFFER_SIZE];
char charBuffer[2];
const int TARGET_SIZE = 5;
bool isBlocked;
int target;
//const char randomZero[] = {'4'};
//const char randomOne[] = {'5'};
//const char randomTwo[] = {'6'};
//const char randomThree[] = {'7'};
//const char randomFour[] = {'8'};
/*
enum targetMicrocontrollerEnum {
  targetArduinoDue,
  targetArduinoMicro,
  targetArduinoUno,
  targetTeensyLC,
  targetFeatherESP32
};
* */
unsigned int score;
bool isIncoming;
int readSize;
bool isHeartbeatReceived;
bool isAllHeartbeatsReceived;
bool isLightOn;
bool isDiscoveryComplete;
bool isUnoCleared;
bool isZeroExpected;
bool isOneExpected;
bool isTwoExpected;
bool isThreeExpected;
bool isFourExpected;
bool isFiveExpected;
bool isSixExpected;
bool isSevenExpected;
bool isEightExpected;
bool isNineExpected = true;
bool isSevenReceived;
bool isEightReceived;
bool isUnoTarget;
bool isDueTarget;
bool isFeatherTarget;
bool isMicroTarget;
char stateBuffer[5];
std::ofstream myfile;
bool isRunning = true;
int returnCode;
const int COM_MAX = 256;
const int TEN = 10;
const int ONE_HUNDRED = 100;
const int ASCII_ZERO = '0';
const int COM_DIGIT_ZERO = 7;
const int COM_DIGIT_ONE = 8;
const int COM_DIGIT_TWO = 9;
const char NULL_TERMINATOR = '\0';
const int SCORE_MAX = 9;

#endif
