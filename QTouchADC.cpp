#include "Arduino.h"
#include "QTouchADC.h"

void QTouchADCClass::init()
{
// define variables. not sure if its possible in the library or where, global stuff...

// int QTouchDelay = 5;
// int measurement1, measurement2;

// ADC
    ADMUX = (0<<REFS0); //REFS0=0:VCC reference, =1:internal reference 1.1V
    //ADCSRA = (1<<ADEN)| (0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC enable, prescaler 8
    ADCSRA = (1<<ADEN)| (1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0); //ADC enable, prescaler 16
    //ADCSRA = (1<<ADEN)| (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC enable, prescaler 128

  //while(ADCSRA & (1<<ADSC)){  } // wait for first conversion to complete . not sure if needed
  
return;
}


uint16_t QTouchADCClass::sense(byte adcPin, byte refPin, uint8_t samples)
{   
    long _value = 0;
    int muxAdc = 0;
    int muxRef = 0;
    int measurement1, measurement2;
    int QTouchDelay = 50;


   muxAdc = adcPin;
   muxRef = refPin;
  
  for(int _counter = 0; _counter < samples; _counter ++)
  {
    // first measurement: adcPin low, S/H high
    ADMUX = (0<<REFS0) | (muxRef); // set ADC sample+hold condenser to the free A0 (ADC0) 
    //delayMicroseconds(QTouchDelay);
    PORTC |= (1<<refPin); //PC0/ADC0 ref/ S/H high (pullup or output, doesn't matter)
    PORTC &= ~(1<<adcPin);
    DDRC |= (1<<adcPin) | (1<<refPin); // both output: adcPin low, S/H (ADC0) high
    delayMicroseconds(QTouchDelay);
    DDRC &= ~((1<<adcPin) | (1<<refPin)); // set pins to Input...
    PORTC &= ~((1<<adcPin) | (1<<refPin)); // ... and low: Tristate
    /*
    ADMUX = (0<<REFS0) | (adcPin); //  read extern condensator from adcPin
    ADCSRA |= (1<<ADSC); // start conversion
    while (!(ADCSRA & (1 << ADIF))); // wait for conversion complete
    ADCSRA |= (1 << ADIF); // clear ADIF
    measurement1=ADC;
    */
    measurement1 = analogRead(adcPin);

    // second measurement: adcPin high, S/H low
    ADMUX = (0<<REFS0) | (muxRef); // set ADC sample+hold condenser to the free PC0 (ADC0)
    //delayMicroseconds(QTouchDelay);
    PORTC |= (1<<adcPin); // sensePad/adcPin high
    //PORTB &= ~(1<<refPin);
    DDRC |= (1<<adcPin) | (1<<refPin); // both output: adcPin high, S/H (ADC0) low
    delayMicroseconds(QTouchDelay);
    DDRC &= ~((1<<adcPin) | (1<<refPin));
    PORTC &= ~((1<<adcPin) | (1<<refPin));
    /*
    ADMUX = (0<<REFS0) | (adcPin); //   read extern condensator from adcPin
    ADCSRA |= (1<<ADSC); // start conversion
    while (!(ADCSRA & (1 << ADIF))); // wait for conversion complete
    ADCSRA |= (1 << ADIF); // clear ADCIF
    measurement2=ADC;
    */
    measurement2 = analogRead(adcPin);
    
    _value += (measurement2 - measurement1);
    
  } 
  
  return _value / samples;
}

uint8_t QTouchADCClass::touch(byte ADCReadPin) // this doesn't work yet...
{
  int touchValue = QTouchADC.sense(ADCReadPin, PB2, 10);
  
  if (touchValue > 100){
    return 1;
  }
  else {
     return 0;
  }

  
}

QTouchADCClass QTouchADC;
