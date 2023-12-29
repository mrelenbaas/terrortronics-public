#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <tchar.h>
#include <string>
#include "stdlib.h"
//#include <random>

#include "game.h"

Serial::Serial(const char *portName) {
  this->connected = false;
  this->hSerial = CreateFile(portName,
                             GENERIC_READ | GENERIC_WRITE,
                             0,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
  if(this->hSerial==INVALID_HANDLE_VALUE) {
    if(GetLastError()==ERROR_FILE_NOT_FOUND){
      //printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);
    } else {
      //printf("ERROR!!!");
    }
  } else {
    DCB dcbSerialParams = {0};
    if (!GetCommState(this->hSerial, &dcbSerialParams)) {
      //printf("failed to get current serial parameters!");
    } else {
      dcbSerialParams.BaudRate=CBR_9600;
      dcbSerialParams.ByteSize=8;
      dcbSerialParams.StopBits=ONESTOPBIT;
      dcbSerialParams.Parity=NOPARITY;
      dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;
      if(!SetCommState(hSerial, &dcbSerialParams)) {
        //printf("ALERT: Could not set Serial Port parameters");
      } else {
        this->connected = true;
        PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
        Sleep(ARDUINO_WAIT_TIME);
      }
    }
  }
}

Serial::~Serial() {
  if(this->connected) {
    this->connected = false;
    CloseHandle(this->hSerial);
  }
}

int Serial::ReadData(char *buffer, unsigned int nbChar) {
  DWORD bytesRead;
  unsigned int toRead;
  ClearCommError(this->hSerial, &this->errors, &this->status);
  if(this->status.cbInQue>0) {
    if(this->status.cbInQue>nbChar) {
      toRead = nbChar;
    } else {
      toRead = this->status.cbInQue;
    }
    if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) ) {
      return bytesRead;
    }
  }
  return 0;
}


bool Serial::WriteData(const char *buffer, unsigned int nbChar) {
    DWORD bytesSend;
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0)) {
        ClearCommError(this->hSerial, &this->errors, &this->status);
        return false;
    } else {
        return true;
    }
}

bool Serial::IsConnected() {
    return this->connected;
}

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//void State::startRunning() {
//  state = stateRunning;
//}

//void State::startWaiting() {
//  state = stateWaiting;
//}

//int State::getState() {
//  return state;
//}

int _tmain(int argc, _TCHAR* argv[]) {
  //FILE fp = FILE("./state.txt");
  //fp.close();
  char stateBuffer[5];
  stateBuffer[0] = '0';
  stateBuffer[1] = ',';
  stateBuffer[2] = '0';
  stateBuffer[3] = '\0';
  stateBuffer[4] = '\n';
  std::ofstream myfile;
  myfile.open("./state.txt");
  myfile << stateBuffer;
  myfile.close();
  system("adb shell \"cd /sdcard && rm -rf *.txt\"");
  //system("adb -s G762XR00004P push ./state.txt ./sdcard/");
  system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
  //Sleep(30000);
  char device[] = {'\\', '\\', '.', '\\', 'C', 'O', 'M', '\0', '\0', '\0', '\0'};
  Serial* SP;
  for(int i = 0; i < 256; ++i) {
    if (i < 10) {
      device[7] = 48 + i;
      device[8] = '\0';
      device[9] = '\0';
    }
    else if (i < 100) {
      device[7] = 48 + (i / 10);
      device[8] = 48 + (i % 10);
      device[9] = '\0';
    } else {
      device[7] = 48 + (i / 100);
      device[8] = 48 + (i % 100 / 10);
      device[9] = 48 + (i % 100 % 10);
    }
    SP = new Serial(device);
    if (SP->IsConnected()) {
      //printf("%s\n", device);
      //printf("Connected.\n");
      break;
    }
    printf("%d\n", i);
  }
  printf("broken\n");
	char incomingData[2];
  incomingData[0] = '\0';
  incomingData[1] = '\0';
	int dataLength = 2;
	//while(SP->IsConnected()) {
  while(1) {
		readSize = SP->ReadData(incomingData, dataLength);
    if (readSize > 0) {
      //printf("read: %s\n", incomingData);
    }
    if (isIncoming) {
      if (incomingData[0] == '0') {
      } else if (incomingData[0] == '1') {
      } else if (incomingData[0] == '2') {
      } else if (incomingData[0] == '3') {
      } else if (incomingData[0] == 'd') {
        printf("received: %c\n", targetArduinoDue[0]);
        ++score;
        if (score > 9) {
          score = 9;
        }
        //stateBuffer[1] = score;
        sprintf(charBuffer, "%d", score);
        stateBuffer[0] = charBuffer[0];
        myfile.open("./state.txt");
        myfile << stateBuffer;
        myfile.close();
        system("adb shell \"cd /sdcard && rm -rf *.txt\"");
        if (score == 0) {
          //system("adb -s G762XR00004P push ./state.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
        } else if (score == 1) {
          //system("adb -s G762XR00004P push ./state1.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state1.txt ./sdcard/");
        }  else if (score == 2) {
          //system("adb -s G762XR00004P push ./state2.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state2.txt ./sdcard/");
        }  else if (score == 3) {
          //system("adb -s G762XR00004P push ./state3.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state3.txt ./sdcard/");
        }  else if (score == 4) {
          //system("adb -s G762XR00004P push ./state4.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state4.txt ./sdcard/");
        }  else if (score == 5) {
          //system("adb -s G762XR00004P push ./state5.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state5.txt ./sdcard/");
        }  else if (score == 6) {
          //system("adb -s G762XR00004P push ./state6.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state6.txt ./sdcard/");
        }  else if (score == 7) {
          //system("adb -s G762XR00004P push ./state7.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state7.txt ./sdcard/");
        }  else if (score == 8) {
          //system("adb -s G762XR00004P push ./state8.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state8.txt ./sdcard/");
        }  else if (score == 9) {
          //system("adb -s G762XR00004P push ./state9.txt ./sdcard/");
          system("adb -s 192.168.4.5 push ./state9.txt ./sdcard/");
        }
        //system("adb -s G762XR00004P push ./state.txt ./sdcard/");
        //system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
        // adb shell input tap 100 300
        // adb exec-out screencap -p > screen.png
        // adb shell input tap 965 1977
        //system("adb -s G762XR00004P shell input tap 965 1977");
        system("adb -s 192.168.4.5 shell input tap 965 1977");
        //system("adb push ./state.txt ./");
        printf("score: %d\n", score);
        isIncoming = false;
        isHeartbeatReceived = false;
      } else if (incomingData[0] == '5') {
      } else if (incomingData[0] == '6') {
      } else if (incomingData[0] == '7') {
      } else if (incomingData[0] == '8') {
      } else if (incomingData[0] == '9') {
      }
    } else {
      if (incomingData[0] == '0') {
        if (!isHeartbeatReceived) {
          printf("%c\n", incomingData[0]);
          SP->WriteData(receivedHeartbeat, 4);
          isHeartbeatReceived = true;
        }
      } else if (incomingData[0] == '1') {
        printf("%c\n", incomingData[0]);
        SP->WriteData(receivedConfirmation, 4);
      } else if (incomingData[0] == '2') {
        printf("%c\n", incomingData[0]);
        SP->WriteData(requestRandom, 4);
      } else if (incomingData[0] == '3') {
        printf("target: %c\n", incomingData[0]);
        SP->WriteData(targetArduinoDue, 4);
        isIncoming = true;
        Sleep(10000);
      } else if (incomingData[0] == '4') {
      } else if (incomingData[0] == '5') {
      } else if (incomingData[0] == '6') {
      } else if (incomingData[0] == '7') {
      } else if (incomingData[0] == '8') {
      } else if (incomingData[0] == '9') {
      }
    }
    incomingData[0] = '\0';
    incomingData[1] = '\0';
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
