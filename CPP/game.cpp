// 2nd-party libraries.
#include "game.h"

int _tmain(int argc, _TCHAR* argv[]) {
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
  //system("adb shell \"cd /sdcard && rm -rf *.txt\"");
  //system("adb -s G762XR00004P push ./state.txt ./sdcard/");
  //system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
  while (!isDiscoveryComplete) {
    findNextConnection();
  }
  incomingData[0] = '\0';
	int dataLength = 1;
  while(isRunning) {
    try {
      if (serialFeather && serialFeather->isConnected()) {
        readSize = serialFeather->readData(incomingData, dataLength);
        if (readSize > 0) {
          //printf("(Feather) incomingData: %s, %d\n", incomingData, readSize);
        }
        switch (incomingData[0]) {
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
        incomingData[0] = '\0';
      }
      /* TODO: Test and remove.
      if (serialDue && serialDue->isConnected()) {
        readSize = serialDue->readData(incomingData, dataLength);
        if (readSize > 0) {
          //printf("(Due) incomingData: %s, %d\n", incomingData, readSize);
        }
        if (incomingData[0] == '0') {
        } else if (incomingData[0] == '1') {
          incrementScore();
        } else if (incomingData[0] == '2') {
        } else if (incomingData[0] == '3') {
          printf("target (Feather)\n");
          serialUno->writeData(setUntarget);
          serialFeather->writeData(setTarget);
          //serialMicro->writeData(setUntarget);
        } else if (incomingData[0] == '4') {
          printf("target (Due)\n");
          serialUno->writeData(setUntarget);
          serialFeather->writeData(setUntarget);
          //serialMicro->writeData(setUntarget);
        } else if (incomingData[0] == '5') {
          printf("target (Uno)\n");
          serialUno->writeData(setTarget);
          serialFeather->writeData(setUntarget);
          //serialMicro->writeData(setUntarget);
        } else if (incomingData[0] == '6') {
        } else if (incomingData[0] == '7') {
        } else if (incomingData[0] == '8') {
        } else if (incomingData[0] == '9') {
          serialDue->writeData(requestRandom);
        }
        incomingData[0] = '\0';
      }
      */
      if (serialDue && serialDue->isConnected()) {
        readSize = serialDue->readData(incomingData, dataLength);
        if (readSize > 0) {
          //printf("(Due) incomingData: %s, %d\n", incomingData, readSize);
        }
        switch (incomingData[0]) {
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
            //serialMicro->writeData(setUntarget);
            break;
          case '4':
            printf("target (Due)\n");
            serialUno->writeData(setUntarget);
            serialFeather->writeData(setUntarget);
            //serialMicro->writeData(setUntarget);
            break;
          case '5':
            printf("target (Uno)\n");
            serialUno->writeData(setTarget);
            serialFeather->writeData(setUntarget);
            //serialMicro->writeData(setUntarget);
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
        incomingData[0] = '\0';
      }
      /*
      if (serialMicro && serialMicro->isConnected()) {
        readSize = serialMicro->readData(incomingData, dataLength);
        if (readSize > 0) {
          //printf("(Micro) incomingData: %s, %d\n", incomingData, readSize);
        }
        switch (incomingData[0]) {
          case '1':
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
        incomingData[0] = '\0';
      }
      */
      if (serialUno && serialUno->isConnected()) {
        readSize = serialUno->readData(incomingData, dataLength);
        if (readSize > 0) {
          //printf("(Uno) incomingData: %s, %d\n", incomingData, readSize);
        }
        switch (incomingData[0]) {
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
          incomingData[0] = '\0';
      }
      //incomingData[0] = '\0';
    } catch (...) {
      // TODO: Test this catch block.
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
  /* TODO. Test and remove.
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
  */
  switch (score) {
    case 0:
      //system("adb -s G762XR00004P push ./state.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
      break;
    case 1:
      //system("adb -s G762XR00004P push ./state1.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state1.txt ./sdcard/");
      break;
    case 2:
      //system("adb -s G762XR00004P push ./state2.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state2.txt ./sdcard/");
      break;
    case 3:
      //system("adb -s G762XR00004P push ./state3.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state3.txt ./sdcard/");
      break;
    case 4:
      //system("adb -s G762XR00004P push ./state4.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state4.txt ./sdcard/");
      break;
    case 5:
      //system("adb -s G762XR00004P push ./state5.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state5.txt ./sdcard/");
      break;
    case 6:
      //system("adb -s G762XR00004P push ./state6.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state6.txt ./sdcard/");
      break;
    case 7:
      //system("adb -s G762XR00004P push ./state7.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state7.txt ./sdcard/");
      break;
    case 8:
      //system("adb -s G762XR00004P push ./state8.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state8.txt ./sdcard/");
      break;
    case 9:
      //system("adb -s G762XR00004P push ./state9.txt ./sdcard/");
      system("adb -s 192.168.4.5 push ./state9.txt ./sdcard/");
      break;
  };
  // system("adb -s G762XR00004P push ./state.txt ./sdcard/");
  // system("adb -s 192.168.4.3 push ./state.txt ./sdcard/");
  // adb shell input tap 100 300
  // adb exec-out screencap -p > screen.png
  // adb shell input tap 965 1977
  // system("adb -s G762XR00004P shell input tap 965 1977");
  // system("adb -s 192.168.4.3 shell input tap 965 1977");
  // system("adb push ./state.txt ./");
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
      //dcb.BaudRate = 9600;
      dcb.ByteSize = 8;
      //dcb.StopBits = ONESTOPBIT;
      //dcb.Parity = NOPARITY;
      //dcb.fDtrControl = DTR_CONTROL_ENABLE;
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

// TODO: Remove this getter.
bool Serial::isConnected() {
  return this->connected;
}

void findNextConnection() {
  while (deviceIndex <= COM_MAX) {
    /* TODO: Test and remove.
    if (deviceIndex < 10) {
      device[7] = 48 + deviceIndex;
      device[8] = '\0';
      device[9] = '\0';
    }
    else if (deviceIndex < 100) {
      device[7] = 48 + (deviceIndex / 10);
      device[8] = 48 + (deviceIndex % 10);
      device[9] = '\0';
    } else {
      device[7] = 48 + (deviceIndex / 100);
      device[8] = 48 + (deviceIndex % 100 / 10);
      device[9] = 48 + (deviceIndex % 100 % 10);
    }
    */
    if (deviceIndex < TEN) {
      device[COM_DIGIT_ZERO] = ASCII_ZERO + deviceIndex;
      device[COM_DIGIT_ONE] = NULL_TERMINATOR;
      device[COM_DIGIT_TWO] = NULL_TERMINATOR;
    }
    else if (deviceIndex < ONE_HUNDRED) {
      device[COM_DIGIT_ZERO] = ASCII_ZERO + (deviceIndex / TEN);
      device[COM_DIGIT_ONE] = ASCII_ZERO + (deviceIndex % TEN);
      device[COM_DIGIT_TWO] = NULL_TERMINATOR;
    } else {
      device[COM_DIGIT_ZERO] = ASCII_ZERO + (deviceIndex / ONE_HUNDRED);
      device[COM_DIGIT_ONE] = ASCII_ZERO + (deviceIndex % ONE_HUNDRED / TEN);
      device[COM_DIGIT_TWO] = ASCII_ZERO + (deviceIndex % ONE_HUNDRED % TEN);
    }
    SP = new Serial(device);
    if (SP->isConnected()) {
    //if (SP) {
      for (unsigned int i = 0; i < (sizeof(device) / sizeof(device[0])); ++i) {
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
          case 3:
            //deviceMicro[i] = device[i];
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
        //case 3: // TODO: Test and remove.
          //delete SP;
          //serialMicro = new Serial(deviceMicro);
          //printf("deviceMicro: %s\n", deviceMicro);
          //break;
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
