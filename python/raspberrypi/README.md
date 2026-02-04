# DFRobot_Tactile_Sensor
===========================

- [中文版](./README_CN.md)

The tactile sensor is a device that can convert physical contact, pressure or force distribution information into measurable electrical signals, and is often regarded as the "electronic skin" of robots. It provides crucial tactile feedback to the equipment by sensing the magnitude, location distribution and even the changing trend of the pressure acting on its surface.

![产品效果图]

## Product Link ()

    SKU：SEN0704/SEN0705

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

The library has used modbus_tk, detect whether modbus_tk has been imported into Raspberry Pi before use, if not, run the following command to install modbus_tk library. python2: pip install modbus_tk python3: pip3 install modbus_tk

Download the library file before use, paste them into the specified directory, then open the Examples folder and run the demo in the folder.

## Methods

```python
  def begin(self):
    '''!
    @brief Init the sensor
    @param array The array of the sensor,32 or 36
    @return True(init succeed)/False(init failed)
    '''

  def set_thld(self, thld):
    '''!
    @brief Set the threshold of the sensor
    @param thld The threshold of the sensor,the range is 0-4095,default value: 50
    '''

  def get_datas(self):
    '''!
    @brief Get the ADC data of the sensor
    @return ADC data
    @retval    result    The result of get data from the sensor
    @retval    adcval    The ADC data of the sensor,the ordered two-dimensional array that can be accessed directly
    '''

  def restore_sensor(self):
    '''!
    @brief Reset the sensor.restoreSensor will reset the sensor threshold、address、uart and sample rate to default value
    '''

  def set_dev_addr(self,addr):
    '''!
    @brief Set the device address of the sensor
    @param addr The device address of the sensor,The address range is 1 to 255,0 is broadcast address,not writable.
    '''

  def set_baudrate(self, baud):
    '''!
    @brief Set the parameters of the serial baudrate of the sensor
    @param Baud rate
    '''

  def set_uart_param(self, stop ,parity):
    '''
    @braief Set serial port parameters
    @param stop stop bit,parity parity bit
    '''

  def get_device_info(self):
    '''!
    @brief Get device information
    @return Device information
    @retval    VID        The vendor ID of the sensor
    @retval    PID        The product ID of the sensor
    @retval    Version    The version of the sensor
    '''

  def set_sample_rate(self, rate):
    '''!
    @brief Set the sample rate of the sensor
    @param rate:The sample rate of the sensor
    @n     SAMPLE_RATE_20HZ = 0
    @n     SAMPLE_RATE_50HZ = 1
    '''
```

## Compatibility

* RaspberryPi Version

| Board         | Work Well | Work Wrong | Untested | Remarks |
| ---------- -- | :-------: | :--------: | :------: | ------- |
| Raspberry Pi2 |           |            |    √     |         |
| Raspberry Pi3 |           |            |    √     |         |
| Raspberry Pi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |

## History

- 2025-09-04 - Version 1.0.0 released.

## Credits

Written by JiaLi(zhixinliu@dfrobot.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))
