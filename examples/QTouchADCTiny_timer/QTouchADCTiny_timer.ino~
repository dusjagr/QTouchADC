#include <QTouchADCTiny.h>

int refPin  = PB5;
int sensePin =  PB3;
int ledPin = PB4;
int speakerPin = PB0;

int value1 = 0;
int ref1 = 0;

int16_t idx = 0;
const uint16_t ledFadeTable[32] = {0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255}; // this is an exponential series to model the perception of the LED brightness by the human eye

void setup() {
  
  TCCR0B = TCCR0B & 0b1111011; //timer pre-scaler divided by 8
  TCCR0A = (TCCR0A & 0b00111100) | 0b01000010; //sets to CTC and toggle Mode
  QTouchADCTiny.init();
  ref1 = QTouchADCTiny.sense(sensePin, refPin, 10);
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  
  value1 = (QTouchADCTiny.sense(sensePin, refPin, 40) - ref1);
  
  int16_t idx= (value1); // offset probe_val by value of untouched probe
  if(idx<0) idx= 0; // limit the index!!!
  idx/= 1; // scale the index
  if(idx>31) idx= 31; // limit the index!!!
  
  if (value1 > 2) {
    OCR0A = (255 -value1 * 4);
  }
  else {
    OCR0A = 0;
  }
  analogWrite(ledPin, ledFadeTable[idx]);
  delay(1);

}

