/* Code to introduce the frame by frame approach.
 * Written: 16th Sept 2018
 */

#include<SoftPWM.h>

int LED = 13; //Pin declaration
//Frame by frame parameters
float current_millis; //Reset every frame
float elapsed_millis; //Time since last reset of current_millis
float frame_duration = 1; //Time between frames
int PWM_value=0; //PWM value

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //Pin Declaration
  current_millis = millis(); //Set current time for first iteration

}

void loop() {
  // put your main code here, to run repeatedly:
  elapsed_millis = millis()-current_millis; //Time since last reset
  if(elapsed_millis > frame_duration || elapsed_millis < 0) // Elapsed time greater than frame duration
  {
    PWM_value = PWM_value + 10; //Increase PWM value
    if(PWM_value > 250)
    {
      PWM_value = 0; //Reset PWM value
    }

    SoftPWMSet(LED, PWM_value); //Set PWM value
  }
}
