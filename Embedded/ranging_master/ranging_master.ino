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
  // int state = radio.begin(2400.0, 812.5, 9, 7,RADIOLIB_SX128X_SYNC_WORD_PRIVATE, 0, 12);
  int state = radio.begin( 2400.0, 1625, 10, 7,RADIOLIB_SX128X_SYNC_WORD_PRIVATE, 10, 12);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  Serial.print(F("[SX1280] Ranging ... "));

  // start ranging exchange
  // range as master:             true
  // slave address:               0x12345678
  // int state = radio.range(true, 0x12345678);

  // the other module must be configured as slave with the same address
  /*
    int state = radio.range(false, 0x12345678);
  */

  // if ranging calibration is known, it can be provided
  // this should improve the accuracy and precision
  
  uint16_t calibration[3][6] = {
    { 10299, 10271, 10244, 10242, 10230, 10246 },
    { 11486, 11474, 11453, 11426, 11417, 11401 },
    { 13308, 13493, 13528, 13515, 13430, 13376 }
  };

  // int state = radio.range(true, 0x12345678);
  int state = radio.range(true, 0x12345678, calibration);
  

  if (state == RADIOLIB_ERR_NONE) {
    // ranging finished successfully
    Serial.println(F("success!"));
    Serial.print(F("[SX1280] Distance:\t\t\t"));
    Serial.print(radio.getRangingResult());
    Serial.println(F(" meters (raw)"));

  } else if (state == RADIOLIB_ERR_RANGING_TIMEOUT) {
    // timed out waiting for ranging packet
    Serial.println(F("timed out!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }

  // wait for a second before ranging again
  delay(500);
}