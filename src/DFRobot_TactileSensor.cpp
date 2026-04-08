/*!
 * @file DFRobot_TactileSensor.cpp
 * @brief This is the method implementation file of the tactile sensor
 * @copyright   Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [JiaLi](zhixinliu@dfrobot.com)
 * @version  V1.0.0
 * @date  2025-09-04
 * @url https://github.com/DFRobot/DFRobot_TactileSensor.git
 */

#include "DFRobot_TactileSensor.h"

uint8_t tactileSensorArrayX = 8;
uint8_t tactileSensorArrayY = 4;

DFRobot_TactileSensor::DFRobot_TactileSensor(uint8_t addr, Stream *s) : DFRobot_RTU(s)
{
  _s    = s;
  _addr = addr;
}

int8_t DFRobot_TactileSensor::begin(uint8_t array)
{
  delay(500);
  int driverTemp = 0;

  _array = array;
  if (array == 32) {
    tactileSensorArrayX = 8;
    tactileSensorArrayY = 4;
    driverTemp          = 0;
  } else if (array == 36) {
    tactileSensorArrayX = 6;
    tactileSensorArrayY = 6;
    driverTemp          = 1;
  }

  int driver = getModel();

  if (driver == -1 || driver != driverTemp) {
    return -1;
  } else {
    return 0;
  }
}

void DFRobot_TactileSensor::setThld(uint16_t thld)
{
  uint8_t sendBuf[2] = { 0 };
  sendBuf[0]         = (thld >> 0) & 0xFF;
  sendBuf[1]         = (thld >> 8) & 0xFF;

  writeReg(HOUTINGREG_THLD, sendBuf, 2);
  delay(50);
}

sAdcDatas_t DFRobot_TactileSensor::getDatas(void)
{
  sAdcDatas_t adcDatas;
  uint8_t     recvBuf[36 * 2];
  uint16_t    ret = 0;
  uint8_t     tempX, tempY;

  ret = readReg(INPUTREG_GETDATAS, recvBuf, _array * 2, INPUTREG);

  for (uint8_t i = tactileSensorArrayY; i > 0; i--) {
    tempY = tactileSensorArrayY - i;
    for (uint8_t j = 0; j < tactileSensorArrayX; j++) {
      tempX                     = ((i - 1) * tactileSensorArrayX + j);
      adcDatas.adcval[tempY][j] = recvBuf[tempX * 2] << 8 | recvBuf[tempX * 2 + 1];
    }
  }
  adcDatas.result = ret;
  return adcDatas;
}

sVersionInfo_t DFRobot_TactileSensor::getDeviceInfo(void)
{
  sVersionInfo_t versionInfo;

  versionInfo.VID     = getVID();
  versionInfo.PID     = getPID();
  versionInfo.version = getVersion();

  return versionInfo;
}

uint16_t DFRobot_TactileSensor::getVID(void)
{
  uint16_t VID = 0;
  uint8_t  recvBuf[10];

  if (readReg(INPUTREG_VID, recvBuf, 2, INPUTREG) == 0xff) {
    //Serial.println("Read PID error.");
    return 0;
  }
  VID = recvBuf[0] << 8 | recvBuf[1];
  return VID;
}

uint16_t DFRobot_TactileSensor::getPID(void)
{
  uint16_t PID = 0;
  uint8_t  recvBuf[10];
  if (readReg(INPUTREG_PID, recvBuf, 2, INPUTREG) == 0xff) {
    //Serial.println("Read PID error.");
    return 0;
  }
  PID = recvBuf[0] << 8 | recvBuf[1];
  return PID;
}

uint16_t DFRobot_TactileSensor::getVersion(void)
{
  uint16_t version = 0;
  uint8_t  recvBuf[10];
  if (readReg(INPUTREG_VERSION, recvBuf, 2, INPUTREG) == 0xff) {
    //Serial.println("Read version error.");
    return 0;
  }
  version = recvBuf[0] << 8 | recvBuf[1];
  return version;
}

int DFRobot_TactileSensor::getAdcValue(uint8_t x, uint8_t y)
{
  uint16_t adcValue = 0;
  uint8_t  recvBuf[10];

  if (x > tactileSensorArrayX || y > tactileSensorArrayY) {
    // Serial.println("Invalid ADC coordinates.");
    return -1;
  }
  uint16_t instructionAddr = y * tactileSensorArrayY + x;
  if (readReg(INPUTREG_GETDATAS + instructionAddr, recvBuf, 2, INPUTREG) == 0xff) {
    // Serial.println("Read ADC value error.");
    return -1;
  }
  adcValue = recvBuf[0] << 8 | recvBuf[1];

  return adcValue;
}

void DFRobot_TactileSensor::restoreSensor(void)
{
  uint8_t sendBuf[2] = { 0 };
  sendBuf[0]         = 0x00;
  sendBuf[1]         = 0x00;
  writeReg(HOUTINGREG_RESET, sendBuf, 2);
  delay(50);
}

void DFRobot_TactileSensor::setDevAddr(uint8_t addr)
{
  uint8_t sendBuf[2] = { 0 };
  if (addr == BROADCAST_ADDR) {
    return;
  }
  sendBuf[0] = addr;
  sendBuf[1] = 0x00;
  writeReg(HOUTINGREG_ADDR, sendBuf, 2);
  _addr = addr;
  delay(50);
}

void DFRobot_TactileSensor::setBaudrate(eBaudrate_t baud, eStopBit_t stopBits, eParity_t parity)
{
  uint8_t sendBuf[4] = { 0 };

  sendBuf[0] = baud & 0xff;
  sendBuf[1] = baud >> 8 & 0xff;
  sendBuf[2] = stopBits & 0xff;
  sendBuf[3] = parity & 0xff;

  writeReg(HOUTINGREG_BAUDRATE, sendBuf, 4);
  delay(50);
}

uint8_t DFRobot_TactileSensor::readReg(uint8_t reg, void *pBuf, uint8_t size, uint8_t regType)
{
  uint8_t *pBufs = (uint8_t *)pBuf;
  if (pBuf == NULL) {
    return 0;
  }
  if (regType == INPUTREG) {
    return readInputRegister(_addr, reg, pBufs, size);
  } else {
    return readHoldingRegister(_addr, reg, pBufs, size);
  }
}

uint8_t DFRobot_TactileSensor::writeReg(uint8_t reg, void *pBuf, size_t size)
{
  uint8_t *pBufs = (uint8_t *)pBuf;
  uint8_t  ret   = 0;
  ret            = writeHoldingRegister(_addr, reg, pBufs, size);

  return ret;
}

bool DFRobot_TactileSensor::getDevState(void)
{
  uint8_t  recvBuf[10];
  uint16_t ret = 0;
  if (readReg(INPUTREG_DEVSTATE, recvBuf, 2, INPUTREG) == 0xff) {
    //Serial.println("Read version error.");
    return false;
  }
  ret = recvBuf[0] << 8 | recvBuf[1];
  if (ret == 0x0001) {
    return true;
  } else {
    return false;
  }
}

int DFRobot_TactileSensor::getModel(void)
{
  int     model = 0;
  uint8_t recvBuf[10];
  if (readReg(INPUTREG_MODEL, recvBuf, 2, INPUTREG) == 0xff) {
    return -1;
  }
  model = recvBuf[0] << 8 | recvBuf[1];
  return model;
}

void DFRobot_TactileSensor::setSampleRate(eSampleRate_t sampleRate)
{
  uint8_t sendBuf[2] = { 0 };
  sendBuf[0]         = sampleRate & 0xff;
  sendBuf[1]         = sampleRate >> 8 & 0xff;
  writeReg(HOUTINGREG_SAMPLE_RATE, sendBuf, 2);
  delay(50);
}
