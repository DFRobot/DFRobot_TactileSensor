# DFRobot_TactileSensor

===========================
* [English Version](./README.md)

触觉传感器是一种可以将物理接触、压力或力分布信息转换为可测量电信号的装置，常被视为机器人的“电子皮肤”。它通过感知作用在其表面上的压力的大小、位置分布甚至变化趋势，为设备提供关键的触觉反馈。

![产品效果图片]

## 产品链接（）

    SKU：SEN0704/SEN0705

## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

- 支持4*8和6*6的ADC阵列
- 压力阈值、串口参数可配置
- 支持Modbus RTU通讯

## 库安装

要使用这个库, 首先下载库文件( https://github.com/DFRobot/DFRobot_TactileSensor )和依赖文件( https://github.com/DFRobot/DFRobot_RTU ), 将其粘贴到\Arduino\libraries目录中, 然后打开示例文件夹并在文件夹中运行演示。

## 方法

```C++
  /**
   * @fn begin
   * @brief 初始化传感器
   * @param array 传感器的型号，32代表4*8阵列，36代表6*6阵列
   * @return int8_t
   */
  int8_t begin(uint8_t array);
/**
 * @fn setThld
 * @brief 设置传感器压力阈值
 * @param thld 传感器阀的阈值。默认值：50，范围：0-4095
 */
  void setThld(uint16_t thld);

  /**
   * @fn getAdcValue
   * @brief 获取ADC阵列数据值
   * @return sAdcDatas_t
   * @n       result        result字段表示读取状态，0表示成功，default表示失败。
   * @n       adcval        adcval字段是传感器阵列的ADC数据的二维数组。
   */
  sAdcDatas_t getDatas(void);

  /**
   * @fn restoreSensor
   * @brief 重置传感器,恢复传感器阈值，地址，端口和采样率为默认值
   */
  void restoreSensor(void);

  /**
   * @fn setDevAddr
   * @brief 设置设备地址，地址范围为1-255，0是广播地址，不可写入
   * @param addr
   */
  void setDevAddr(uint8_t addr);

  /**
   * @fn setBaudrate
   * @brief 设置设备波特率
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
   * @brief 获取设备信息
   * @return sVersionInfo_t
   * @n       VID           产品VID
   * @n       PID           产品PID
   * @n       version       产品版本
   */
  sVersionInfo_t getDeviceInfo(void);

      /**
   * @fn setSampleRate
   * @brief 设置传感器阵列采样频率
   * @param sampleRate
   * @n     eSampleRate20Hz
   * @n     eSampleRate50Hz
  */
  void setSampleRate(eSampleRate_t sampleRate);
```


## 兼容性

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |
Micro:bit          |              | nonsupport uart |             |

## 历史
- 2025-09-04 - 1.0.0 版本

## 创作者

Written by JiaLi(zhixinliu@dfrobot.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))
