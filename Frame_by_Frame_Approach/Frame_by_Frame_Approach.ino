/* Code to introduce the frame by frame approach.
 * Written: 16th Sept 2018
 */

#include<SoftPWM.h>

int LED = 13; //Pin declaration
//Frame by frame parameters
float current_millis; //Reset every frame
float elapsed_millis; //Time since last reset of current_millis
float frame_duration = 1; //Time between frames
int frame_count=0;
float active_time = 3000;
float increment = 255.00/active_time; 
float PWM_value; //PWM value

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //Pin Declaration
  current_millis = millis(); //Set current time for first iteration
  PWM_value=0;
  SoftPWMBegin(SOFTPWM_NORMAL);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  elapsed_millis = millis()-current_millis; //Time since last reset
  if(elapsed_millis > frame_duration || elapsed_millis < 0) // Elapsed time greater than frame duration
  {
    current_millis = millis();
    Serial.println(frame_count);
    frame_count++;
    if(frame_count < active_time)
    {
      PWM_value = PWM_value + increment; //Increase PWM value
      SoftPWMSet(LED, PWM_value); //Set PWM value
    }
    if(frame_count>active_time)
      {
        SoftPWMSet(LED, 0);
        PWM_value = 0;
      }
    if(frame_count > 5000)
    {
      frame_count=0;
    }
  }
}
