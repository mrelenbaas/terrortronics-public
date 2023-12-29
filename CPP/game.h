#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

class Serial {
    private:
        HANDLE hSerial;
        bool connected;
        COMSTAT status;
        DWORD errors;
    public:
        Serial(const char *portName);
        ~Serial();
        int ReadData(char *buffer, unsigned int nbChar);
        bool WriteData(const char *buffer, unsigned int nbChar);
        bool IsConnected();
};

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
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
const char receivedHeartbeat[] = {'0', '\0'};
const char receivedConfirmation[] = {'1', '\0'};
const char requestRandom[] = {'2', '\0'};
const char targetArduinoDue[] = {'3', '\0'};
const char targetArduinoMicro[] = {'4', '\0'};
const char targetArduinoUno[] = {'5', '\0'};
const char targetTeensyLC[] = {'6', '\0'};
const char targetFeatherESP32[] = {'7', '\0'};
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

#endif
