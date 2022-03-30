#include "Wire.h"

uint8_t DEVICE_ADDRESS = 0x20;

byte inputs = 0;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    Wire.write(0x01);
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x00); // IODIRA register
    Wire.write(0x00); // set all of bank A to outputs
    Wire.endTransmission();
}

void loop()
{
    // read the inputs of bank B.
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x13);
    Wire.endTransmission();
    Wire.requestFrom(0x20, 1);
    inputs = Wire.read();

    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x12); // GPIOA
    Wire.write(inputs);
    Wire.endTransmission();
    Serial.println(inputs, BIN);
    delay(100);
}