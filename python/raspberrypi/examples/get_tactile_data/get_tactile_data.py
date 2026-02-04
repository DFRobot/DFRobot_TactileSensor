# -*- coding: utf-8 -*
'''!
@file get_tactile_data.py
@brief This example demonstrates how to get the tactile data of the DFRobot Tactile Sensor.
@copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
@license The MIT License (MIT)
@author [JiaLi](zhixinliu@dfrobot.com)
@version V1.0
@date 2025-09-04
@url https://github.com/cdjq/DFRobot_TactileSensor
'''

from __future__ import print_function
import sys

sys.path.append("../../")
import time

from DFRobot_Tactile_Sensor import *

# note: Running 4*8 and 6*6 requires modifying the process code
# 6*6 -> 36
# array = 36
# 4*8 -> 32
array = 32

# device address
address = 1

tactile = DFRobot_Tactile_Sensor(address, 115200)


def setup():
  while tactile.begin(array) == -1:
    print("Sensor initialize failed,please check whether the sensor model or connection is correct!")
    time.sleep(1)
  print("Sensor  initialize success!")

  ver = version_info()
  # Get device information
  ver = tactile.get_device_info()
  print(" VID :", ver.VID, end='\n')
  print(" PID :", ver.PID, end='\n')
  print(" Version:", f"{ver.version:X}", end='\n')
  time.sleep(1)

  # Set threshold value,the range is 0-4095
  tactile.set_thld(50)
  time.sleep(0.1)

  # The sensor returns to its default value,Addr doesn't change
  # note: restoreSensor will reset the sensor threshold、address、uart and sample rate to default value
  # tactile.restore_sensor()
  # time.sleep(0.1)

  # Set device address,the address range is 1 to 255,0 is broadcast address,not writable.
  # tactile.set_dev_addr(1)
  # time.sleep(0.1)

  # set uart baudrate ，default is 115200,
  # After setting, please modify the uart of the driving sensor to the corresponding baudrate,stop bits and parity.
  # tactile.set_baudrate(tactile.BAUD_9600)
  # tactile.set_baudrate(tactile.BAUD_115200)
  # time.sleep(0.1)

  # Do not use modifying the baud rate and modifying parameters together
  # tactile.set_uart_param(tactile.STOP_BIT_1, tactile.PARITY_NONE)
  # tactile.set_uart_param(tactile.STOP_BIT_2, tactile.PARITY_EVEN)
  # time.sleep(0.1)

  # #set sample rate
  tactile.set_sample_rate(tactile.SAMPLE_RATE_20HZ)
  # tactile.set_sample_rate(tactile.SAMPLE_RATE_50HZ)
  time.sleep(0.1)


def loop():
  adc_datas = adc_data()
  # Get tactile data
  adc_datas = tactile.get_datas()
  # Print tactile data
  for i in range(tactile_sensor_array_y):
    for j in range(tactile_sensor_array_x):
      print(adc_datas.adcval[i][j], end='\t')
    print('\n')
  print('\n')

  time.sleep(0.1)


if __name__ == "__main__":
  setup()
  while True:
    loop()
