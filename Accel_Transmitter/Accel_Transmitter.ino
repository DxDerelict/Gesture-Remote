#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

RF24 RF(9, 10);
const byte address = {"glove"};
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

void setup() {
  RF.begin();
  RF.openWritingPipe(address);


}

void loop() {
  int* accel_vals = getAccelData();
  transmitData(accel_vals[1], accel_vals[2], accel_vals[3]);

}

void transmitData(int x, int y, int z) {
  int msg[3] = {x, y, z};
  RF.write(&msg, sizeof(msg));
}

int* getAccelData() {
  int arrayVal[20];
  sensors_event_t event;
  accel.getEvent(&event);
  arrayVal[1] = event.acceleration.x;
  arrayVal[2] = event.acceleration.y;
  arrayVal[3] = event.acceleration.z;
 
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");


  return arrayVal;
}
