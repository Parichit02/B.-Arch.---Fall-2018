/* Use of the frame by frame approach
 * Actuate 6 actuators one after another 
 * Provide a delay between consecutive  actuation
 * 
 * Written: 17th Sept, 2018
 */

#include<SoftPWM.h> //Include SoftPWM Library

int LED[6] = {3, 4, 5, 20, 16, 17}; //Declare all pins for Port P0
int frame_count[6]; //Track frames for each pin
float PWM_value[6]; //Track PWM value for each pin
float current_millis; //Frame-by-frame: Track current time. Reset after crossing frame duration
float elapsed_millis; //Frame-by-frame: Track time since last reset of current time. 
int frame_duration = 1; //Frame duration
int active_time = 3000; //Time LED is active
float increment = 255/active_time; //PWM value increment per frame
int delay_time = 1000; //Time between actuator pins

void setup() {
  
  current_millis = millis(); //First declaration of current millis
  for(int i=0; i<6; i++) //Run loop for 6 pins
  {
    pinMode(LED[i],OUTPUT); // Declare pins
    frame_count[i] = 0; // Frame counts to 0
    PWM_value[i] = 0; //PWM value to 0
  }
  SoftPWMBegin(SOFTPWM_NORMAL);
}

void loop() {
  elapsed_millis = millis() - current_millis; //Get time between frames.
  if(elapsed_millis > frame_duration || elapsed_millis <0) //When the difference greater than frame duration, implement code
  {
    current_millis = millis(); //Reset to get time between frames
    for(int i=0; i<6; i++)
    {
      frame_count[i]++; //Increment frame count
      if(frame_count[i]<(active_time + i*delay_time) && frame_count[i]>i*delay_time) //If statement for active or not
      {
        SoftPWMSet(LED[i], PWM_value[i]);
        PWM_value[i] = PWM_value[i] + increment; //Increment every frame
      }
      
      if(frame_count[i]>active_time+i*delay_time) //Shut off LED after active time is over.
      {
        SoftPWMSet(LED[i], 0);
        PWM_value[i] = 0;
      }
    }
     if(frame_count[5]>active_time+5*delay_time) //Reset frame count to 0 after 6th LED lit up
      {
        for(int i=0; i<6; i++){
          frame_count[i] = 0;    
        }    
      }
  }
}
