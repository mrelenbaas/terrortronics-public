// 2nd-party libraries.
#include "game.h"

int _tmain(int argc, _TCHAR* argv[]) {
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
  //system("adb shell \"cd /sdcard && rm -rf *.txt\"");
  //system("adb -s G762XR00004P push ./state.txt ./sdcard/");
  //system("adb -s 192.168.4.5 push ./state.txt ./sdcard/");
  while (!isDiscoveryComplete) {
    findNextConnection();
  }
  incomingData[0] = '\0';
	int dataLength = 1;
  while(1) {
    //serialUno->WriteData(setTarget);
    //serialDue->WriteData(setTarget);
    //serialFeather->WriteData(setTarget);
    //serialMicro->WriteData(setTarget);
    /*
    if (isUnoTarget) {
      serialUno->WriteData(setTarget);
    } else {
      serialUno->WriteData(setUntarget);
    }
    if (isDueTarget) {
      serialDue->WriteData(setTarget);
    } else {
      serialDue->WriteData(setUntarget);
    }
    if (isFeatherTarget) {
      serialFeather->WriteData(setTarget);
    } else {
      serialFeather->WriteData(setUntarget);
    }
    if (isMicroTarget) {
      serialMicro->WriteData(setTarget);
    } else {
      serialMicro->WriteData(setUntarget);
    }
    */
    if (serialFeather && serialFeather->IsConnected()) {
      readSize = serialFeather->ReadData(incomingData, dataLength);
      if (readSize > 0) {
        //printf("---\n(Feather) incomingData: %s, %d\n", incomingData, readSize);
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
          //printf("Heartbeat (Feather):\n");
          //serialFeather->WriteData(setTarget);
          break;
      };
    }
    if (serialDue && serialDue->IsConnected()) {
      readSize = serialDue->ReadData(incomingData, dataLength);
      if (readSize > 0) {
        //printf("(Due) incomingData: %s, %d\n", incomingData, readSize);
      }
      /*
      if (isIncoming) {
        if (incomingData[0] == '0') {
        } else if (incomingData[0] == '1') {
        } else if (incomingData[0] == '2') {
        } else if (incomingData[0] == '3') {
        } else if (incomingData[0] == 'd' || 
                   incomingData[0] == 'e' ||
                   incomingData[0] == 'f' ||
                   incomingData[0] == 'g' ||
                   incomingData[0] == 'h') {
          ++score;
          if (score > 9) {
            score = 9;
          }
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
          //isIncoming = false;
          isHeartbeatReceived = false;
        } else if (incomingData[0] == '5') {
        } else if (incomingData[0] == '6') {
        } else if (incomingData[0] == '7') {
        } else if (incomingData[0] == '8') {
        } else if (incomingData[0] == '9') {
          printf("Heartbeat (Due) (Incoming):\n");
          serialDue->WriteData(requestRandom);
        }
        if (incomingData[0]) {
          if (incomingData[0] == '3') {
            //printf("target (Feather): %c\n", incomingData[0]);
            //isIncoming = true;
          } else if (incomingData[0] == '4') {
            //printf("target (Due): %c\n", incomingData[0]);
            //isIncoming = true;
          } else if (incomingData[0] == '5') {
            //printf("target (Micro): %c\n", incomingData[0]);
            //isIncoming = true;
          } else if (incomingData[0] == '6') {
            //printf("target (Uno): %c\n", incomingData[0]);
            //isIncoming = true;
          } else if (incomingData[0] == '7') {
          } else if (incomingData[0] == '8') {
          } else if (incomingData[0] == '9') {
            printf("Heartbeat (Due) (Incoming):\n");
            serialDue->WriteData(requestRandom);
          } else if (incomingData[0] == 'd') {
          } else if (incomingData[0] == 'e') {
          } else if (incomingData[0] == 'f') {
          } else if (incomingData[0] == 'g') {
          } else if (incomingData[0] == 'h') {
          }
        }
        */
      //} else {
        if (incomingData[0] == '0') {
        } else if (incomingData[0] == '1') {
          printf("HERE HERE HERE: %d\n", score);
          ++score;
          printf("%c\n", incomingData[0]);
        } else if (incomingData[0] == '2') {
          printf("%c\n", incomingData[0]);
        } else if (incomingData[0] == '3') {
          printf("target (Feather): %c\n", incomingData[0]);
          serialUno->WriteData(setUntarget);
          //serialDue->WriteData(setUntarget);
          serialFeather->WriteData(setTarget);
          serialMicro->WriteData(setUntarget);
          //isUnoTarget = false;
          //isDueTarget = false;
          //isFeatherTarget = true;
          //isMicroTarget = false;
          //isIncoming = true;
        } else if (incomingData[0] == '4') {
          printf("target (Due): %c\n", incomingData[0]);
          serialUno->WriteData(setUntarget);
          //serialDue->WriteData(setTarget);
          serialFeather->WriteData(setUntarget);
          serialMicro->WriteData(setUntarget);
          //isUnoTarget = false;
          //isDueTarget = true;
          //isFeatherTarget = false;
          //isMicroTarget = false;
          //isIncoming = true;
        } else if (incomingData[0] == '5') {
          printf("target (Micro): %c\n", incomingData[0]);
          serialUno->WriteData(setUntarget);
          //serialDue->WriteData(setUntarget);
          serialFeather->WriteData(setUntarget);
          serialMicro->WriteData(setTarget);
          //isUnoTarget = false;
          //isDueTarget = false;
          //isFeatherTarget = false;
          //isMicroTarget = true;
          //isIncoming = true;
        } else if (incomingData[0] == '6') {
          printf("target (Uno): %c\n", incomingData[0]);
          serialUno->WriteData(setTarget);
          //serialDue->WriteData(setUntarget);
          serialFeather->WriteData(setUntarget);
          serialMicro->WriteData(setUntarget);
          //isUnoTarget = true;
          //isDueTarget = false;
          //isFeatherTarget = false;
          //isMicroTarget = false;
          //isIncoming = true;
        } else if (incomingData[0] == '7') {
        } else if (incomingData[0] == '8') {
        } else if (incomingData[0] == '9') {
          //printf("Heartbeat (Due) (Not Incoming):\n");
          serialDue->WriteData(requestRandom);
        }
      //}
    }
    if (serialMicro && serialMicro->IsConnected()) {
      readSize = serialMicro->ReadData(incomingData, dataLength);
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
          //printf("(Micro) 7\n");
          break;
        case '8':
          //printf("(Micro) 8\n");
          break;
        case '9':
          //printf("Heartbeat (Micro):\n");
          //printf("SPECIAL CASE\n");
          if (isHeartbeatOn) {
            //serialMicro->WriteData(setTarget);
          } else {
            //serialMicro->WriteData(setUntarget);
          }
          isHeartbeatOn = !isHeartbeatOn;
          break;
      };
    }
    //if (!isBlocked2) {
    //  Sleep(3000);
    //  serialUno->WriteData(receivedHeartbeat);
    //  isBlocked2 = true;
    //}
    if (serialUno && serialUno->IsConnected()) {
      //serialUno->WriteData(receivedHeartbeat);
      readSize = serialUno->ReadData(incomingData, dataLength);
      if (readSize > 0) {
        //printf("---\n(Uno) incomingData: %s, %d\n", incomingData, readSize);
      }
      switch (incomingData[0]) {
          case '0':
            if (isZeroExpected) {
              //printf("Uno: 0\n");
              isZeroExpected = false;
            }
            break;
          case '1':
            if (isOneExpected) {
              //printf("Uno: 1\n");
              isOneExpected = false;
            }
            break;
          case '2':
            if (isTwoExpected) {
              //printf("Uno: 2\n");
              isTwoExpected = false;
            }
            break;
          case '3':
            if (isThreeExpected) {
              //printf("Uno: 3\n");
              isThreeExpected = false;
            }
            break;
          case '4':
            if (isFourExpected) {
              //printf("Uno: 4\n");
              isFourExpected = false;
            }
            break;
          case '5':
            if (isFiveExpected) {
              //printf("Uno: 5\n");
              isFiveExpected = false;
            }
            break;
          case '6':
            if (isSixExpected) {
              //printf("Uno: 6\n");
              isSixExpected = false;
            }
            break;
          case '7':
            if (isPreviousEight) {
              //printf("Uno: 7\n");
              //serialUno->WriteData(setUntarget);
            }
            isPreviousSeven = true;
            isPreviousEight = false;
            break;
          case '8':
            if (isPreviousSeven) {
              //serialUno->WriteData(setTarget);
              //printf("Uno: 8\n");
            }
            isPreviousSeven = false;
            isPreviousEight = true;
            break;
          case '9':
            //if (isNineExpected) {
              //if (isSevenReceived && isEightReceived) {
                //printf("Uno: 9\n");
              //}
              //printf("Uno: 9\n");
              //if (isLightOn) {
                //serialUno->WriteData(setTarget);
                //isEightExpected = true;
                //isLightOn = false;
              //} else {
                //serialUno->WriteData(setUntarget);
                //isSevenExpected = true;
                //isLightOn = true;
              //}
              //if (isSevenReceived && isEightReceived) {
              //  isNineExpected = false;
              //}
              //isNineExpected = false;
            //}
              previousChar = '9';
            break;
        };
    }
    incomingData[0] = '\0';
    //Sleep(3000);
    //printf("HERE\n");
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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
    DCB dcbSerialParams = {0};
    if (GetCommState(this->hSerial, &dcbSerialParams)) {
      //dcbSerialParams.BaudRate = CBR_9600;
      dcbSerialParams.BaudRate = 9600;
      dcbSerialParams.ByteSize = 8;
      //dcbSerialParams.StopBits = ONESTOPBIT;
      //dcbSerialParams.Parity = NOPARITY;
      //dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;
      if(SetCommState(hSerial, &dcbSerialParams)) {
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

int Serial::ReadData(char * buffer, unsigned int nbChar) {
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

void Serial::WriteData(const char * buffer) {
  //printf("buffer: %s\n", buffer);
  DWORD bytesSend;
  WriteFile(this->hSerial, (void *)buffer, NB_CHAR, &bytesSend, 0);
}

bool Serial::IsConnected() {
  return this->connected;
}

void findNextConnection() {
  printf("Find next connection.\n");
  while (deviceIndex <= 256) {
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
    SP = new Serial(device);
    if (SP->IsConnected()) {
      printf("Connected: %s\n", device);
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
            deviceMicro[i] = device[i];
            break;
        };
      }
      switch (serialIndex) {
        case 0:
          delete SP;
          serialUno = new Serial(deviceUno);
          //serialUno->WriteData(setTarget);
          printf("deviceUno: %s\n", deviceUno);
          break;
        case 1:
          delete SP;
          serialDue = new Serial(deviceDue);
          //serialDue->WriteData(setTarget);
          printf("deviceDue: %s\n", deviceDue);
          break;
        case 2:
          delete SP;
          serialFeather = new Serial(deviceFeather);
          //serialFeather->WriteData(setTarget);
          printf("deviceFeather: %s\n", deviceFeather);
          break;
        case 3:
          delete SP;
          serialMicro = new Serial(deviceMicro);
          //serialMicro->WriteData(setTarget);
          printf("deviceMicro: %s\n", deviceMicro);
          break;
        };
      ++serialIndex;
      break;
    } else {
      ++deviceIndex;
      if (deviceIndex >= 256) {
        printf("DISCOVERY COMPLETE.\n");
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
