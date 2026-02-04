# DFRobot_TactileSensor

===========================

* [中文版](./README_CN.md)

The tactile sensor is a device that can convert physical contact, pressure or force distribution information into measurable electrical signals, and is often regarded as the "electronic skin" of robots. It provides crucial tactile feedback to the equipment by sensing the magnitude, location distribution and even the changing trend of the pressure acting on its surface.

![product image]

## Product Link ()
    SKU:SEN0704/SEN0705

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

* Supports 4*8 and 6*6 arrays<br/>
* The pressure threshold and serial port parameters can be configured<br/>
* Support Modbus RTU communication protocol

## Installation

Download the library file (https://github.com/DFRobot/DFRobot_TactileSensor) and its dependencies (https://github.com/DFRobot/DFRobot_RTU) before use, paste them into the \Arduino\libraries directory, then open the sample folder and run the demo in the folder.

## Methods

```C++

  /**
   * @fn begin
   * @brief Initialize the sensor.
   * @param array The number of the sensor array，4*8 or 6*6.
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
   * @n       adcval        The adcval field is an array of the ADC data of the sensor array.
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
```

## Compatibility

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |
Micro:bit          |              | nonsupport uart |             |

## History

- 2025-09-04 - Version 1.0.0 released.

## Credits

Written by JiaLi(zhixinliu@dfrobot.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))
