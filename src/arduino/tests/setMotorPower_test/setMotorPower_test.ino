// Tetrix Prizm
#include <PRIZM.h>
#include <Wire.h>
PRIZM prizm;

// Direction
#define FWD 1
#define BKWD 0

void setMotorPower(int channel, int power)       // set Motor Channel power on PRIZM
{

        if(channel==1){channel = 0x40;}   // DC channel 1
        if(channel==2){channel = 0x41;}   // DC channel 2

        Wire.beginTransmission(5);
        Wire.write(channel);
        Wire.write(power);
        Wire.endTransmission();
}
void setup() {
//PRIZM
  prizm.PrizmBegin();

}

void loop() {
  setMotorPower(1,25);
  delay(2000);
  setMotorPower(1,0);
  delay(2000);
}
