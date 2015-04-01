#include <QTouchADC.h>

int refPin  = 0;
int sensePin =  1;
int ledPin = 9;
int speakerPin = 10;

int ref1 = 0;
int value1 = 0;

void setup() {
  Serial.begin(9600);
  
  QTouchADC.init();
  ref1 = QTouchADC.sense(sensePin, refPin, 500);
  
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  unsigned long time;
  time= micros();
  value1 = (QTouchADC.sense(sensePin, refPin, 500) - ref1);
  time= micros() - time;
  
  Serial.print(value1);
  Serial.print(' ');
  Serial.println(time);
  
  value1 = value1;
  
  if (value1<=3) value1 = 0;
  if (value1>=255) value1 = 255;
  
  tone (10, (value1 * 100));
  analogWrite(ledPin, value1);
  
  delay(200);
  
  
}
