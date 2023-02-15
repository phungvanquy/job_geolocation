// include the library
#include <RadioLib.h>

// SX1280 has the following connections:
// NSS pin:   PA8
// DIO1 pin:  PB4
// NRST pin:  PA0
// BUSY pin:  PB3
SX1280 radio = new Module(PA8, PB4, PA0, PB3);

void setup() {
  Serial.begin(9600);

  Serial.print(F("[SX1280] Initializing ... "));
  // int state = radio.begin(2400.0, 812.5, 9, 7,RADIOLIB_SX128X_SYNC_WORD_PRIVATE, 12, 12);
  // int state = radio.begin( 2400.0, 812.5, 9, 7,RADIOLIB_SX128X_SYNC_WORD_PRIVATE, 10, 12);
  radio.begin();
  // perform calibration
  radio.calibrateImage();


    // print calibration data to serial port
  Serial.print("Calibration done, Freq Error: ");
  Serial.print(radio.getFrequencyError());
  Serial.print(", Phase Error: ");
  Serial.println(radio.getPhaseError());


}

void loop() {

}