#include<SoftPWM.h>

int LED = 17; //Pin declaration
//IR related variables
int IR_pin = 27; 
int IR_value;
int IR_threshold = 300;
int active_IR=1;

//Frame by frame parameters
float current_millis; //Reset every frame
float elapsed_millis; //Time since last reset of current_millis
float frame_duration = 1; //Time between frames
int frame_count=0;
float active_time = 3000;
int delay_time=1000;
float increment = 255.00/active_time; 
float PWM_value; //PWM value

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //Pin Declaration
  pinMode(IR_pin, INPUT);
  current_millis = millis(); //Set current time for first iteration
  PWM_value=0;
  SoftPWMBegin(SOFTPWM_NORMAL);
  Serial.begin(9600);
}

void loop(){
  elapsed_millis = millis()-current_millis; //Time since last reset
  if(elapsed_millis > frame_duration || elapsed_millis < 0) // Elapsed time greater than frame duration
  {
    current_millis = millis();
    Serial.println(frame_count);
    IR_value = analogRead(IR_pin);
    //The key here is to use a variable that defines that the IR has been triggered. 
    if(IR_value > IR_threshold)
    {
      active_IR = 1;
    }
    //When the IR is active, the code within this conditional is the same as our previous code structure in frame_by_frame.ino
    if(active_IR==1)
    {
      frame_count++;
      if(frame_count<active_time)
      {
        PWM_value = PWM_value + increment;
      }

      if(frame_count > active_time)
      {
        PWM_value = 0;
      }

      if(frame_count>active_time + delay_time)
      {
        frame_count =0;
        active_IR=0;
      }

      SoftPWMSet(LED, PWM_value);
    }
  }
}
