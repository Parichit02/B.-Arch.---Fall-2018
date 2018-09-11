/* SoftPWM - Software based pulse width modulation
 * Commands like digitalWrite are discrete. They can either be HIGH or LOW
 * Software PWM can be used to gradually increase or decrease actuation value.
 * This creates the effect of fading up and fading down.
 * 
 * More information: https://www.pjrc.com/teensy/td_libs_SoftPWM.html
 */

#include<SoftPWM.h> //Library with softpwm functions

int LED_pin = 17;

void setup() {
  // put your setup code here, to run once:
  SoftPWMBegin(SOFTPWM_NORMAL);
  pinMode(LED_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<255; i+=5)
  {
    SoftPWMSet(LED_pin, i);
    SoftPWMSet(13,i);
    delay(100);
  }

  for(int i=255; i<0; i-=5)
  {
    SoftPWMSet(LED_pin, i);
    SoftPWMSet(13,i);
    delay(100);
  }

}
