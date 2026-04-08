/*!
 * @file DFRobot_TactileSensor.h
 * @brief This file demostrates the method for using tactile sensor library.
 * @copyright   Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [JiaLi](zhixinliu@dfrobot.com)
 * @version  V1.0.0
 * @date  2025-09-04
 * @url https://github.com/DFRobot/DFRobot_TactileSensor.git
 */
#ifndef DFRobot_TactileSENSOR_H
#define DFRobot_TactileSENSOR_H

#include "Arduino.h"
#include "DFRobot_RTU.h"
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif

extern uint8_t tactileSensorArrayX;
extern uint8_t tactileSensorArrayY;

/**
 * @enum eBaudrate_t
 * @brief Baud rate enumeration
 */
typedef enum {
  eBaudrate9600   = 0x0003,    ///< 9600 baud rate
  eBaudrate57600  = 0x0007,    ///< 57600 baud rate
  eBaudrate115200 = 0x0008,    ///< 115200 baud rate
  eBaudrate921600 = 0x0009,    ///< 921600 baud rate
} eBaudrate_t;

/**
 * @enum eParity_t
 * @brief Parity enumeration
 */
typedef enum {
  eParityNone = 0x00,    ///< No parity
  eParityEven = 0x01,    ///< Even parity
  eParityOdd  = 0x02,    ///< Odd parity
} eParity_t;

/**
 * @enum eStopBit_t
 * @brief Stop bit enumeration
 */
typedef enum {
  eStopBit0_5 = 0x00,    ///< 0.5 stop bit
  eStopBit1   = 0x01,    ///< 1 stop bit
  eStopBit1_5 = 0x02,    ///< 1.5 stop bit
  eStopBit2   = 0x03,    ///< 2 stop bit
} eStopBit_t;

/**
 * @struct sAdcDatas_t
 * @brief ADC data structure
 */
typedef struct {
  uint8_t  result;
  uint16_t adcval[6][8];
} sAdcDatas_t;

/**
 * @struct sVersionInfo_t
 * @brief Device version information structure
*/
typedef struct {
  uint16_t VID;
  uint16_t PID;
  uint16_t version;
} sVersionInfo_t;

/**
 * @enum eSampleRate_t
 * @brief Sample rate enumeration
 */
typedef enum {
  eSampleRate20Hz = 0x0000,
  eSampleRate50Hz = 0x0001,
} eSampleRate_t;

class DFRobot_TactileSensor : public DFRobot_RTU {
public:
#define BROADCAST_ADDR 0x0000    ///< Broadcast address
//Input Register
#define INPUTREG          0
#define INPUTREG_VID      0x0000    ///< Device VID
#define INPUTREG_PID      0x0001    ///< VID of the device, fixed to be 0x3343
#define INPUTREG_VERSION  0x0005    ///< Firmware version information
#define INPUTREG_DEVSTATE 0x0006    ///< Device state
#define INPUTREG_GETDATAS 0x0007    ///< Device ADC data.36*16 bytes
#define INPUTREG_MODEL    0x002B    ///< Device model

//Holding register
#define HOUTINGREG                 1
#define HOUTINGREG_ADDR            0X0002    ///< The gesture that can trigger interrupt
#define HOUTINGREG_BAUDRATE        0X0003    ///< The baud rate of the serial port
#define HOUTINGREG_VERIFY_AND_STOP 0X0004    ///< Reset the device
#define HOUTINGREG_THLD            0X0006    ///< Sensor valve value
#define HOUTINGREG_RESET           0X0007    ///< Restore the default value
#define HOUTINGREG_SAMPLE_RATE     0X0008    ///< Sample rate of the sensor

  DFRobot_TactileSensor(uint8_t addr, Stream *s);
  ~DFRobot_TactileSensor() {};

  /**
   * @fn begin
   * @brief Initialize the sensor.
   * @param array The number of the sensor array,4*8 or 6*6.
   * @return int8_t
   */
  int8_t begin(uint8_t array);

  /**
 * @fn setThld
  * @brief Set the Thld object.
  * @param thld The threshold value of the sensor valve. Default value: 50 ,range: 0-4095
  */
  void setThld(uint16_t thld);

  /**
   * @fn getAdcValue
   * @brief Get the Datas object.
   * @return sAdcDatas_t
   * @n       result        The result field indicates the status of the reading, 0 indicates success, defult indicates failure.
   * @n       adcval        The ADC data of the sensor,the ordered two-dimensional array that can be accessed directly
   */
  sAdcDatas_t getDatas(void);

  /**
   * @fn restoreSensor
   * @brief Restore sensor threshold、address、uart and sample rate to default value
   */
  void restoreSensor(void);

  /**
   * @fn setDevAddr
   * @brief Set the device address.
   * @param addr The device address,The address range is 1 to 255,0 is broadcast address,not writable.
   */
  void setDevAddr(uint8_t addr);

  /**
   * @fn setBaudrate
   * @brief Set the Baudrate object
   * @param baud
   * @n     eBaudrate9600
   * @n     eBaudrate57600
   * @n     eBaudrate115200
   * @n     eBaudrate921600
   * @param stopBits
   * @n     eStopBit0_5
   * @n     eStopBit1
   * @n     eStopBit1_5
   * @n     eStopBit2
   * @param parity
   * @n     eParityNone
   * @n     eParityEven
   * @n     eParityOdd
   */
  void setBaudrate(eBaudrate_t baud, eStopBit_t stopBits = eStopBit1, eParity_t parity = eParityNone);

  /**
   * @fn getDeviceInfo
   * @brief Get the device information object.
   * @return sVersionInfo_t
   * @n       VID           The vendor ID of the device.
   * @n       PID           The product ID of the device.
   * @n       version       The version of the device.
   */
  sVersionInfo_t getDeviceInfo(void);

  /**
   * @fn setSampleRate
   * @brief Set the SampleRate object.
   * @param sampleRate
   * @n     eSampleRate20Hz
   * @n     eSampleRate50Hz
  */
  void setSampleRate(eSampleRate_t sampleRate);

protected:
  int      getAdcValue(uint8_t x, uint8_t y);
  uint16_t getPID(void);
  uint16_t getVID(void);
  uint16_t getVersion(void);
  int      getModel(void);
  bool     getDevState(void);
  uint8_t  readReg(uint8_t reg, void *pBuf, uint8_t size, uint8_t regType);
  uint8_t  writeReg(uint8_t reg, void *pBuf, size_t size);

  Stream  *_s = NULL;
  uint16_t _addr;

  uint16_t _array;
};
#endif
