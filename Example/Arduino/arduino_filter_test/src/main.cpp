/* The same logic can be implemented in mbed Keil Studio. */
/* This example is for RPM data */
#include <Arduino.h>
#include <Ticker.h>
#include "FIR.h"

#define freq_pin 33

//#define filter
#define double_filter

/* Variables for filtering */
const float a = 0.6;
const float b = 0.65; 
FIR filtering;

/* Global variables and ESP32/STM32 Tools */
Ticker ticker5Hz;
bool dd=false;
bool flag=false;
bool blink=false;
uint8_t pulse_counter = 0;
uint64_t current_period = 0, last_count = 0;
float rpm_hz, rpm_logger=0;

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

  #ifdef double_filter
    dd |= 0x01;
  #endif  

  ticker5Hz.attach(1.0/5, ticker5HzISR);
  attachInterrupt(digitalPinToInterrupt(freq_pin), frequencyCounterISR, FALLING);
}

void loop() 
{
  if(flag)
  {
    Serial.println("f");

    detachInterrupt(digitalPinToInterrupt(freq_pin));

    if (current_period!=0)
    {
      //rpm_hz = ((float)pulse_counter/(current_period/1000000.0));    //calculates frequency in Hz

      rpm_logger = pulse_counter*5*60;
    } else {
      //rpm_hz = 0;
      rpm_logger = 0;
    }    

    Serial.printf("Dado Bruto: ");
    Serial.println(rpm_logger);

    #ifdef double_filter
      Serial.printf("Dado filtrado 2 vezes: ");
      Serial.println(filtering.filt(a, b, rpm_logger, dd));
    #else
      Serial.printf("Dado filtrado: ");
      Serial.println(filtering.filt(rpm_logger, a, b));
    #endif

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