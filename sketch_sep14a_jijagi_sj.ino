#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9150.h"
#define pi 3.141592
MPU9150 accelGyroMag;

int i;
double px, py, pz, qx, qy, qz;

//sensor setting
int signal = 2;
int signal2 = 3;
int signal3 = 4;

int onoff;
int onoff2;
int onoff3;



int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

double myaw, apit, arol;
double yaw, pitch, roll;
double gyaw = 0, gpit = 0, grol = 0, pre_gyaw, pre_gpit, pre_grol;
unsigned long used_millisec, pre_millisec = 0;
double Co_gain = 1;///change

void setup() {
    
    Wire.begin();
    Serial.begin(9600);
    
    accelGyroMag.initialize();
   
    
   for(i = 1 ; i <= 500 ; i++){
    accelGyroMag.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

px = 0 - gx;
py = 0 - gy;
pz = 0 - gz;
qx = qx * (i-1) / i + (px/i);
qy = qy * (i-1) / i + (py/i);
qz = qz * (i-1) / i + (pz/i);
}
    
    yaw = atan2(my, mx)*180/pi;
    pitch = atan2(az, ax)*180/pi;
    roll = atan2(az, ay)*180/pi;


    
}

void loop() 
{
   onoff = digitalRead(signal);
   onoff2 = digitalRead(signal2);
   onoff3 = digitalRead(signal3);  
  
  used_millisec = millis() - pre_millisec;
    pre_millisec = millis();
    
    gyaw = pre_gyaw * used_millisec / 1000;
    gpit = pre_gpit * used_millisec / 1000;
    grol = pre_grol * used_millisec / 1000;

    
    yaw += gyaw * (Co_gain - 1)/Co_gain + (myaw - yaw)/Co_gain;
    pitch += gpit * (Co_gain - 1)/Co_gain + (apit - pitch)/Co_gain;
    roll += grol * (Co_gain - 1)/Co_gain + (arol - roll)/Co_gain;
    
    delay(5);
    accelGyroMag.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    myaw = atan2(my, mx)*180/pi;
    apit = atan2(az, ax)*180/pi;
    arol = atan2(az, ay)*180/pi;
   delay(5);
   
    pre_gyaw = mz + qz;
    pre_gpit = my + qy;
    pre_grol = mx + qx;
    


if(onoff==0){

    Serial.print("@");
    Serial.print("{");
    Serial.print("b");
    Serial.print("12001");
    Serial.print("x");
    Serial.print(yaw);    
    Serial.print("y");
    Serial.print(pitch);
    Serial.print("z");
    Serial.print(roll);
    Serial.print("#");
    Serial.println("}");
}

if(onoff2==0){
  
    Serial.print("@");
    Serial.print("{");
    Serial.print("b");
    Serial.print("15001");
    Serial.print("x");
    Serial.print(yaw);    
    Serial.print("y");
    Serial.print(pitch);
    Serial.print("z");
    Serial.print(roll);
    Serial.print("#");
    Serial.println("}");
}
if(onoff3==0){
      
    Serial.print("@");
    Serial.print("{");
    Serial.print("b");
    Serial.print("16001");
    Serial.print("x");
    Serial.print(yaw);    
    Serial.print("y");
    Serial.print(pitch);
    Serial.print("z");
    Serial.print(roll);
    Serial.print("#");
    Serial.println("}");
}
}
