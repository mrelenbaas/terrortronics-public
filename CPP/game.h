#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

// 1st-party libraries.
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
// 3rd-party libraries.
#include <windows.h>

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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
        int ReadData(char *, unsigned int);
        void WriteData(const char *);
        bool IsConnected();
    private:
        HANDLE hSerial;
        bool connected;
        COMSTAT status;
        DWORD errors;
};
char incomingData[BUFFER_SIZE];
void findNextConnection();
Serial* SP;
Serial* serialFeather = NULL;
Serial* serialDue = NULL;
Serial* serialMicro = NULL;
Serial* serialUno = NULL;
int deviceIndex;
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
bool isHeartbeatOn;
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
char previousChar;
bool isPreviousSeven;
bool isPreviousEight;
bool isUnoTarget;
bool isDueTarget;
bool isFeatherTarget;
bool isMicroTarget;

#endif
