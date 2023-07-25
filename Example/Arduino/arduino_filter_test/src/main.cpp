/* The same logic can be implemented in mbed Keil Studio. */
#include <Arduino.h>
#include <Ticker.h>
#include "FIR.h"

#define freq_pin 33

/* Variables for filtering */
const float a=0.7,b=0.7; 
FIR filter;
FIR double_filter;

/* Global variables and ESP32/STM32 Tools */
Ticker ticker5Hz;
bool flag=false;
bool blink=false;
uint8_t pulse_counter = 0;
uint64_t current_period = 0, last_count = 0;
float rpm_hz, rpm_ilogger=0;

/* General and Interrupts functions */
void ticker5HzISR();
void frequencyCounterISR();

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    ; //wait for serial port to connect. Needed for native USB port only
  }

  pinMode(LED_BUILTIN, OUTPUT);
  
  ticker5Hz.attach(1/5, ticker5HzISR);
  attachInterrupt(digitalPinToInterrupt(freq_pin), frequencyCounterISR, FALLING);
}

void loop() 
{
  if (flag)
  {
    Serial.println("f");

    detachInterrupt(digitalPinToInterrupt(freq_pin));

    if (current_period!=0)
    {
      //rpm_hz = ((float)pulse_counter/(current_period/1000000.0));    //calculates frequency in Hz

      rpm_ilogger = pulse_counter*5*60;
    } else {
      //rpm_hz = 0;
      rpm_ilogger = 0;
    }

    Serial.printf("Dado Bruto: ");
    Serial.println(rpm_ilogger);
    Serial.printf("Dado filtrado: ");
    Serial.println((uint16_t)filter.filt(a,b,rpm_ilogger));
    Serial.printf("Dado filtrado novamente: ");
    Serial.println((uint16_t)double_filter.filt(a,b,filter.filt(a,b,rpm_ilogger)));

    pulse_counter = 0;
    current_period = 0;                                   // reset pulses related variables
    last_count = millis();
    attachInterrupt(digitalPinToInterrupt(freq_pin), frequencyCounterISR, FALLING);
    flag = false;
  }
}

void ticker5HzISR()
{
  flag = true;
}

void frequencyCounterISR()
{
  blink = !blink;
  digitalWrite(LED_BUILTIN, blink);

  pulse_counter++;
  current_period += millis() - last_count;
  last_count = millis();
}