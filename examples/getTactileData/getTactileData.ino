/*!
 * @file getTactileData.ino
 * @brief This is an example to show how to get tactile data from DFRobot Tactile Sensor.
 * @copyright	Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [JiaLi](zhixinliu@dfrobot.com)
 * @version V1.0
 * @date 2025-09-04
 * @url https://github.com/cdjq/DFRobot_TactileSensor
 */
#include "DFRobot_TactileSensor.h"

/* ---------------------------------------------------------------------------------------------------------------------
 *    board   |             MCU                | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
 *     VCC    |              5V                |        VCC           |    VCC    |   VCC   |  VCC  |     X      |  vcc  |
 *     GND    |              GND               |        GND           |    GND    |   GND   |  GND  |     X      |  gnd  |
 *     RX     |              TX                |     Serial1 TX1      |     5     |   5/D6  |  D2   |     X      |  tx1  |
 *     TX     |              RX                |     Serial1 RX1      |     4     |   4/D7  |  D3   |     X      |  rx1  |
 * ----------------------------------------------------------------------------------------------------------------------*/
/*The default baud rate is 115200, and it supports 9600,57600, and 912600*/

#define DFRobot_TACTILE_ARRAY_SIZE 32    // if you use (4*8)32-channel tactile sensor
//#define DFRobot_TACTILE_ARRAY_SIZE 36  // if you use (6*6)36-channel tactile sensor

#define ADDRESS 1    // sensor address

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
SoftwareSerial        mySerial(/*rx =*/4, /*tx =*/5);
DFRobot_TactileSensor tactile(/*addr =*/ADDRESS, /*s =*/&mySerial);
#else
DFRobot_TactileSensor tactile(/*addr =*/ADDRESS, /*s =*/&Serial1);
#endif

void setup()
{
  //Init MCU communication serial port
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  mySerial.begin(115200);
#elif defined(ESP32)
  Serial1.begin(115200, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  Serial1.begin(115200);
#endif

  Serial.begin(115200);
  while (tactile.begin(DFRobot_TACTILE_ARRAY_SIZE) == -1) {
    Serial.println(" Sensor initialize failed,please check whether the sensor model or connection is correct!");
    delay(1000);
  }
  Serial.println(" Sensor  initialize success!");

  sVersionInfo_t ver;
  
  //Get device information
  ver = tactile.getDeviceInfo();
  Serial.print(" VID: ");
  Serial.println(ver.VID);
  Serial.print(" PID: ");
  Serial.println(ver.PID);
  Serial.print(" Version: ");
  Serial.println(ver.version, HEX);
  delay(1000);

  //Set threshold value,the range is 0-4095
  tactile.setThld(50);

  //The sensor returns to its default value
  //note: restoreSensor will reset the sensor threshold、address、uart and sample rate to default value
  //tactile.restoreSensor();

  //Set device address，the address range is 1 to 255,0 is broadcast address,not writable.
  //tactile.setDevAddr(1);

  //set uart baudrate,default is 115200,
  //After setting, please modify the uart of the driving sensor to the corresponding baudrate,stop bits and parity.
  //tactile.setBaudrate(eBaudrate115200,eStopBit1,eParityNone);

  tactile.setSampleRate(eSampleRate20Hz);
  //setSampleRate(eSampleRate50Hz);
  //set sample frequency, 20Hz or 50Hz
}

void loop()
{
  sAdcDatas_t adcDatas;
  //Get tactile data
  adcDatas = tactile.getDatas();
  //Print tactile data
  if (adcDatas.result == 0) {
    for (int i = 0; i < tactileSensorArrayY; i++) {
      for (int j = 0; j < tactileSensorArrayX; j++) {
        Serial.print(adcDatas.adcval[i][j]);
        Serial.print("\t");
      }
      Serial.println();
    }
  } else {
    Serial.println("Read ADC data failed!!");
  }
  Serial.println();
  delay(20);
}
