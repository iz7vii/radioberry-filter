// for raspberry pi pico :P


#include <Wire.h>
const uint8_t I2C_ADDRESS = 0x20;
// Costanti per i filtri di banda
//const int FILTER_160m = 8;
const int FILTER_80m = 1;
//const int FILTER_60m = 2;
const int FILTER_40m = 2;
//const int FILTER_30m = 401;
const int FILTER_20m = 3;
//const int FILTER_17m = 164;
const int FILTER_15m = 4;
//const int FILTER_12m = 232;
const int FILTER_10m = 5;
//const int FILTER_6m = 232;

// Assegnazione PIN per LPF e BPF
int lpf_10m = 0;  // pin 1
int lpf_15m = 1;  // pin 2
int lpf_20m = 2;  // pin 4
int lpf_40m = 3;  // pin 5
int lpf_80m = 6;  // pin 9

int bpf_10m = 7;  // pin 10
int bpf_15m = 8;  // pin 11
int bpf_20m = 9;  // pin 12
int bpf_40m = 10; // pin 14
int bpf_80m = 11; // pin 15
int currentBand = 0;

void setup()
{
  Wire.begin(I2C_ADDRESS);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  // Setup dei PIN per LPF
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

  // Setup dei PIN per BPF
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

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  processCommand(x);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);                      // wait for a second

}

// Funzione per processare i comandi ricevuti e selezionare i filtri
void processCommand(int command) {
  if (currentBand != command) {
    currentBand = command;
    switch (command) {
      case FILTER_80m:
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, HIGH);
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, HIGH);
        break;
      case FILTER_40m:
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, HIGH);
        digitalWrite(bpf_80m, LOW);
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, HIGH);
        digitalWrite(lpf_80m, LOW);
        break;
      case FILTER_20m:
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, HIGH);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, LOW);
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, HIGH);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
        break;
      case FILTER_15m:
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, HIGH);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, LOW);
        digitalWrite(lpf_10m, HIGH);
        digitalWrite(lpf_15m, HIGH);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
        break;
      case FILTER_10m:
        digitalWrite(bpf_10m, HIGH);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, LOW);
        digitalWrite(lpf_10m, LOW);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
        break;
      default:
        // Reset dei pin dei filtri
        digitalWrite(bpf_10m, LOW);
        digitalWrite(bpf_15m, LOW);
        digitalWrite(bpf_20m, LOW);
        digitalWrite(bpf_40m, LOW);
        digitalWrite(bpf_80m, LOW);
        digitalWrite(lpf_10m, LOW);
        digitalWrite(lpf_15m, LOW);
        digitalWrite(lpf_20m, LOW);
        digitalWrite(lpf_40m, LOW);
        digitalWrite(lpf_80m, LOW);
        break;
    }
  }
}
