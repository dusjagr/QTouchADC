#include <QTouchADC.h>

int refPin  = 0;
int sensePin1 =  1;
int sensePin2 =  2;
int ledPin1 = 9;
int ledPin2 = 10;

int ref1 = 0;
int value1 = 0;

int ref2 = 0;
int value2 = 0;

void setup() {
  Serial.begin(9600);
  
  QTouchADC.init();
  ref1 = QTouchADC.sense(sensePin1, refPin, 500);
  ref2 = QTouchADC.sense(sensePin2, refPin, 500);
  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT);

  
}

void loop() {
  unsigned long time;
  time= micros();
  value1 = (QTouchADC.sense(sensePin1, refPin, 500) - ref1);
  time= micros() - time;
  value2 = (QTouchADC.sense(sensePin2, refPin, 500) - ref2);

  Serial.print(value1);
  Serial.print(' ');
  Serial.print(value2);
  Serial.print(' ');
  Serial.println(time);
  
  if (value1<=15) value1 = 0;
  if (value1>=255) value1 = 255;
  
  if (value2<=15) value2 = 0;
  if (value2>=255) value2 = 255;
  
  analogWrite(ledPin1, value1);
  analogWrite(ledPin2, value2);
  
  delay(200);
  
  
}
