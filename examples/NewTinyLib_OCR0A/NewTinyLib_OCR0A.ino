#include <QTouchADCTiny.h>

int refPin  = PB2;
int sensePin =  PB3;
int ledPin = PB4;
int speakerPin = PB0;

int ref1 = 0;
int value1 = 0;

void setup() {
  
  TCCR0B = TCCR0B & 0b1111011; //timer pre-scaler divided by 8 or some other
  TCCR0A = (TCCR0A & 0b00111100) | 0b01000010; //sets to CTC and toggle Mode
  
  QTouchADCTiny.init();
  ref1 = QTouchADCTiny.sense(sensePin, refPin, 500);
  
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
}

void loop() {

  value1 = (QTouchADCTiny.sense(sensePin, refPin, 100) - ref1);
  
  if(value1<=0) value1 = 0;
  if(value1>=255) value1 = 255;
  
  if (value1 > 10) {
    OCR0A = (255 - value1);
  }
  
  else {
    OCR0A = 0;
  }
}
