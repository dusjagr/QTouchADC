/*
  QTouchSense.h - Library for Capacitive touch sensors using only one ADC PIN and a Reference
  modified from https://github.com/jgeisler0303/QTouchADCArduino
  Released into the public domain.
*/

#ifndef QTouchADC_h
#define QTouchADC_h

#include <Arduino.h>

class QTouchADCClass
{
  public:
    void init();
    uint16_t sense(byte ADCReadPin, byte ADCRef, uint8_t samples);
    uint8_t touch(byte ADCReadPin);
};

extern QTouchADCClass QTouchADC;

#endif

