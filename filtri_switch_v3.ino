// fork of https://github.com/cinosh07/Radioberry-Filters-Interface/tree/master?tab=readme-ov-file
#include <Wire.h>

const uint8_t I2C_ADDRESS = 0x22; //Generic Board Protocol
uint8_t received;
uint8_t message;
const uint8_t COMMAND_ON_OFF = 0x01;
const uint8_t COMMAND_SPEED = 0x02;

const int FILTER_160M = 8;
const int FILTER_80m = 4;
const int FILTER_60m = 2;
const int FILTER_40m = 802;
const int FILTER_30m = 401;
const int FILTER_20m = 101;
const int FILTER_17m = 164;
const int FILTER_15m = 264;
const int FILTER_12m = 232;
const int FILTER_10m = 232;
const int FILTER_6m = 232;
boolean genericMode = false;


//Pin definitions
#define lpf_board_qrp_lab
#if defined lpf_board_qrp_lab
int lpf_10m = 0;
int lpf_15m = 1;
int lpf_20m = 2;
int lpf_40m = 3;
int lpf_80m = 6;
#endif

#define bpf_board_qrp_lab
#if defined bpf_board_qrp_lab
int bpf_10m = 7;
int bpf_15m = 8;
int bpf_20m = 9;
int bpf_40m = 10;
int bpf_80m = 11;
#endif

int currentBand = 0;
boolean transmit = 0;
boolean transmitAllowed = true;

void setup() {

#if defined lpf_board_qrp_lab
  pinMode(lpf_10m, OUTPUT);
  pinMode(lpf_15m, OUTPUT);
  pinMode(lpf_20m, OUTPUT);
  pinMode(lpf_40m, OUTPUT);
  pinMode(lpf_80m, OUTPUT);
  digitalWrite(lpf_10m, LOW);
  digitalWrite(lpf_15m, LOW);
  digitalWrite(lpf_20m, LOW);
  digitalWrite(lpf_40m, LOW);
  digitalWrite(lpf_80m, LOW);
#endif

#if defined bpf_board_qrp_lab
  pinMode(bpf_10m, OUTPUT);
  pinMode(bpf_15m, OUTPUT);
  pinMode(bpf_20m, OUTPUT);
  pinMode(bpf_40m, OUTPUT);
  pinMode(bpf_80m, OUTPUT);
  digitalWrite(bpf_10m, LOW);
  digitalWrite(bpf_15m, LOW);
  digitalWrite(bpf_20m, LOW);
  digitalWrite(bpf_40m, LOW);
  digitalWrite(bpf_80m, LOW);
#endif

  //Start i2c as slave
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

}
void requestEvent()
{
  if (received == COMMAND_ON_OFF) {

  } else {
    Wire.write(0);
  }
}
int started = 0;
void loop() {


}


void receiveEvent(int bytes) {

  int byteCount = 0;
  int command = 0;
  uint8_t byte1 = 0;
  uint8_t byte2 = 0;
  uint8_t byte3 = 0;
  int freqHigh [8] = {0, 0, 0, 0, 0, 0, 0, 0};
  while (0 < Wire.available()) {
    byte x = Wire.read();
    if (genericMode == false) {
      if (byteCount == 0) {
        byte1 = x;
      }
      if (byteCount == 1) {
        byte2 = x;
        command = command + (byte2 * 100);
      }
      if (byteCount == 2) {
        byte3 = x;
        command = command + byte3;
      }
      if (byte1 == 2 && byte2 == 2 && byte3 == 3) {
        genericMode = true;
        byte1 = 0;
      }
      byteCount = byteCount + 1;
    } else {

      if (byteCount == 0) {
        byte1 = x;
      }
      if (byteCount == 1) {
        byte2 = x;
        command = command + (byte2 * 100);
      }
      if (byteCount == 2) {
        byte3 = x;
        command = command + byte3;
      }

      if (byteCount > 0) {
        freqHigh[byteCount - 1] = x;
      }

      byteCount = byteCount + 1;
    }
  }

  if (command != 0) {
    processCommand(command);
  }

}

void processCommand(int command) {
  started =  1;
  if (currentBand != command) {
    currentBand = command;
    switch (command) {
      /*
      case FILTER_160M:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_pin1, HIGH);
        digitalWrite(bpf_pin2, LOW);
        digitalWrite(bpf_pin3, LOW);
        digitalWrite(bpf_pin4, LOW);
#endif
#if defined lpf_board_qrp_lab
        //Not supported
        digitalWrite(lpf_15_10m, LOW);
        digitalWrite(lpf_20_17m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
        */
      case FILTER_80m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, HIGH);
#endif
#if defined lpf_board_qrp_lab
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, HIGH);
#endif
        break;
/*
      case FILTER_60m:
#if defined bpf_board_qrp_lab
        //Not supported
        digitalWrite(bpf_pin1, LOW);
        digitalWrite(bpf_pin2, LOW);
        digitalWrite(bpf_pin3, LOW);
        digitalWrite(bpf_pin4, LOW);
#endif
#if defined lpf_board_qrp_lab
        //Not supported
        digitalWrite(lpf_15_10m, LOW);
        digitalWrite(lpf_20_17m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
*/
      case FILTER_40m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, HIGH);
        digitalWrite(bpf_80m, LOW);
#endif
#if defined lpf_board_qrp_lab
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, HIGH);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
/*
      case FILTER_30m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_pin1, LOW);
        digitalWrite(bpf_pin2, LOW);
        digitalWrite(bpf_pin3, HIGH);
        digitalWrite(bpf_pin4, LOW);
#endif
#if defined lpf_board_qrp_lab
        //Not supported
        digitalWrite(lpf_15_10m, LOW);
        digitalWrite(lpf_20_17m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
*/
      case FILTER_20m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, HIGH);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, LOW);
#endif
#if defined lpf_board_qrp_lab
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, HIGH);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
/*
      case FILTER_17m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_pin1, LOW);
        digitalWrite(bpf_pin2, HIGH);
        digitalWrite(bpf_pin3, HIGH);
        digitalWrite(bpf_pin4, LOW);
#endif
#if defined lpf_board_qrp_lab
        digitalWrite(lpf_15_10m, LOW);
        digitalWrite(lpf_20_17m, HIGH);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
*/
      case FILTER_15m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, HIGH);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, LOW);
#endif
#if defined lpf_board_qrp_lab
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, HIGH);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
/*
      case FILTER_12m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_pin1, LOW);
        digitalWrite(bpf_pin2, LOW);
        digitalWrite(bpf_pin3, LOW);
        digitalWrite(bpf_pin4, HIGH);
#endif
#if defined lpf_board_qrp_lab
        digitalWrite(lpf_15_10m, HIGH);
        digitalWrite(lpf_20_17m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
        break;
*/
      case FILTER_10m:
#if defined bpf_board_qrp_lab
        digitalWrite(bpf_10m, HIGH);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, LOW);
         #endif
         #if defined lpf_board_qrp_lab
        digitalWrite(lpf_10m, LOW);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
#endif
         break;
      //                case FILTER_6m:
      //                        #if defined bpf_board_qrp_lab
      //                        digitalWrite(bpf_pin1, LOW);
      //                        digitalWrite(bpf_pin2, LOW);
      //                        digitalWrite(bpf_pin3, LOW);
      //                        digitalWrite(bpf_pin4, LOW);
      //                        #endif
      //                        #if defined lpf_board_qrp_lab
      //                        digitalWrite(lpf_15_10m, LOW);
      //                        digitalWrite(lpf_20_17m, LOW);
      //                        digitalWrite(lpf_40m, LOW);
      //                        digitalWrite(lpf_80m, LOW);
      //                        #endif
      //                        break;
      default:

         break;
    }
  }
}
