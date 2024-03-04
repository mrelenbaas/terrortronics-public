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

// 2nd-party libraries.
#include "game.h"

int _tmain(int argc, _TCHAR* argv[]) {
  std::cout << "Game start." << std::endl;
  deviceSize = sizeof(device) / sizeof(device[0]);
  stateBuffer[0] = '0';
  stateBuffer[1] = ',';
  stateBuffer[2] = '0';
  stateBuffer[3] = '\0';
  stateBuffer[4] = '\n';
  myfile.open("./state.txt");
  myfile << stateBuffer;
  myfile.close();
  system("adb shell \"cd /sdcard && rm -rf *.txt\"");
  system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
  std::cout << "Discovery start." << std::endl;
  while (!isDiscoveryComplete) {
    findNextConnection();
  }
	int dataLength = 1;
  
  std::cout << "Runtime start." << std::endl;
  while(isRunning) {
    try {
      if (serialFeather && serialFeather->isConnected()) {
        readSize = serialFeather->readData(incomingData, dataLength);
        data = incomingData[0];
        if (readSize > 0) {
          printf("(Feather) incomingData: %s, %d\n",
                 incomingData,
                 readSize);
        }
        switch (data) {
          case '1':
            incrementScore();
            break;
          case '2':
            break;
          case '3':
            break;
          case '4':
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
        };
      }
      if (serialDue && serialDue->isConnected()) {
        readSize = serialDue->readData(incomingData, dataLength);
        if (readSize > 0) {
          printf("(Due) incomingData: %s, %d\n",
                 incomingData,
                 readSize);
        }
        switch (data) {
          case '0':
            break;
          case '1':
            incrementScore();
            break;
          case '2':
            break;
          case '3':
            break;
            printf("target (Feather)\n");
            serialUno->writeData(setUntarget);
            serialFeather->writeData(setTarget);
            break;
          case '4':
            printf("target (Due)\n");
            serialUno->writeData(setUntarget);
            serialFeather->writeData(setUntarget);
            break;
          case '5':
            printf("target (Uno)\n");
            serialUno->writeData(setTarget);
            serialFeather->writeData(setUntarget);
            break;
          case '6':
            break;
          case '7':
            break;
          case '8':
            break;
          case '9':
            serialDue->writeData(requestRandom);
            break;
        };
      }
      if (serialUno && serialUno->isConnected()) {
        readSize = serialUno->readData(incomingData, dataLength);
        if (readSize > 0) {
          printf("(Uno) incomingData: %s, %d\n",
                 incomingData,
                 readSize);
        }
        switch (data) {
            case '0':
              break;
            case '1':
              incrementScore();
              break;
            case '2':
              break;
            case '3':
              break;
            case '4':
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
          };
      }
    } catch (...) {
      isRunning = false;
      returnCode = 1;
      if (serialDue->isConnected()) {
        serialDue->Serial::~Serial();
      }
      if (serialFeather->isConnected()) {
        serialFeather->Serial::~Serial();
      }
      if (serialUno->isConnected()) {
        serialUno->Serial::~Serial();
      }
    }
	}
	return returnCode;
}

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void incrementScore() {
  ++score;
  if (score > SCORE_MAX) {
    score = SCORE_MAX;
  }
  sprintf(charBuffer, "%d", score);
  stateBuffer[0] = charBuffer[0];
  myfile.open("./state.txt");
  myfile << stateBuffer;
  myfile.close();
  system("adb shell \"cd /sdcard && rm -rf *.txt\"");
  switch (score) {
    case 0:
      system("adb -s G762XR00004P push ./state.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
      break;
    case 1:
      system("adb -s G762XR00004P push ./state1.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state1.txt ./sdcard/");
      break;
    case 2:
      system("adb -s G762XR00004P push ./state2.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state2.txt ./sdcard/");
      break;
    case 3:
      system("adb -s G762XR00004P push ./state3.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state3.txt ./sdcard/");
      break;
    case 4:
      system("adb -s G762XR00004P push ./state4.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state4.txt ./sdcard/");
      break;
    case 5:
      system("adb -s G762XR00004P push ./state5.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state5.txt ./sdcard/");
      break;
    case 6:
      system("adb -s G762XR00004P push ./state6.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state6.txt ./sdcard/");
      break;
    case 7:
      system("adb -s G762XR00004P push ./state7.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state7.txt ./sdcard/");
      break;
    case 8:
      system("adb -s G762XR00004P push ./state8.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state8.txt ./sdcard/");
      break;
    case 9:
      system("adb -s G762XR00004P push ./state9.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state9.txt ./sdcard/");
      break;
  };
  system("adb -s G762XR00004P shell input tap 965 1977");
}

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Serial::Serial(const char *portName) {
  this->connected = false;
  this->hSerial = CreateFile(portName,
                             GENERIC_READ | GENERIC_WRITE,
                             0,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
  if(this->hSerial != INVALID_HANDLE_VALUE) {
    DCB dcb = {0};
    if (GetCommState(this->hSerial, &dcb)) {
      dcb.BaudRate = CBR_9600;
      dcb.ByteSize = BYTE_SIZE;
      if(SetCommState(hSerial, &dcb)) {
        this->connected = true;
        PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
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

int Serial::readData(char * buffer, unsigned int nbChar) {
  DWORD bytesRead;
  unsigned int toRead;
  ClearCommError(this->hSerial, &this->errors, &this->status);
  if(this->status.cbInQue >= BUFFER_SIZE) {
    if(this->status.cbInQue > nbChar) {
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

void Serial::writeData(const char * buffer) {
  DWORD bytesSend;
  WriteFile(this->hSerial, (void *)buffer, NB_CHAR, &bytesSend, 0);
}

bool Serial::isConnected() {
  return this->connected;
}

char digit(char modifier) {
  return ASCII_ZERO + modifier;
}

void com(int i) {
  if (i < TEN) {
    device[COM_DIGIT_ZERO] = digit(i);
    device[COM_DIGIT_ONE] = NULL_TERMINATOR;
    device[COM_DIGIT_TWO] = NULL_TERMINATOR;
  }
  else if (i < ONE_HUNDRED) {
    device[COM_DIGIT_ZERO] = digit(i / TEN);
    device[COM_DIGIT_ONE] = digit(i % TEN);
    device[COM_DIGIT_TWO] = NULL_TERMINATOR;
  } else {
    device[COM_DIGIT_ZERO] = digit(i / ONE_HUNDRED);
    device[COM_DIGIT_ONE] = digit(i % ONE_HUNDRED / TEN);
    device[COM_DIGIT_TWO] = digit(i % ONE_HUNDRED % TEN);
  }
}

void findNextConnection() {
  while (deviceIndex <= COM_MAX) {
    com(deviceIndex);
    SP = new Serial(device);
    if (SP->isConnected()) {
      for (unsigned int i = 0; i < deviceSize; ++i) {
        switch (serialIndex) {
          case 0:
            deviceUno[i] = device[i];
            break;
          case 1:
            deviceDue[i] = device[i];
            break;
          case 2:
            deviceFeather[i] = device[i];
            break;
        };
      }
      switch (serialIndex) {
        case 0:
          delete SP;
          serialUno = new Serial(deviceUno);
          printf("deviceUno: %s\n", deviceUno);
          break;
        case 1:
          delete SP;
          serialDue = new Serial(deviceDue);
          printf("deviceDue: %s\n", deviceDue);
          break;
        case 2:
          delete SP;
          serialFeather = new Serial(deviceFeather);
          printf("deviceFeather: %s\n", deviceFeather);
          break;
        };
      ++serialIndex;
      break;
    } else {
      ++deviceIndex;
      if (deviceIndex >= COM_MAX) {
        printf("Discovery complete.\n");
        isDiscoveryComplete = true;
        isHeartbeatReceived = true;
        isAllHeartbeatsReceived = true;
        break;
      }
    }
  }
}

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
// Untested ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
