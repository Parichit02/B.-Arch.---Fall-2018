/*  P2 is transmitting port
 *  P1 is listening port
 *  
 *  NC 1 communicating with NC 2
 *  NC1 - P0 to HCDM
 *  NC1 - P2 to NC2 
 * 
 *  HCDM 1 - IR on A, LED on H
 * 
 *  NC2 - P0 to HCDM
 *  NC2 - P1 from NC1 P2
 *  HCDM 2 - IR on A, LED on H
 *  
 *  This is a frame-by-frame approach. The NCs will be listening to IR triggers as well as the signals from neighboring NCs.
 *  While active, it'll use digitalWrite to actuate the LED and send command. 
 *  Connect the NC + HCDM setup as shown in the image attached.   
 *    
 *  Logic of implementation: When the NC detects an IR trigger, it sets the behavior identifier as true. While this identifier is true, it actuated the LED while also sending signal to the neighboring NC.
 *  When a number of frames are reached, it sets this behavior identifier to false. 
 *  When the NC detects a signal from a neighboring NC, it sets the behavior identifier as true. While this identifier is true, it actuated the LED while also sending signal to the neighboring NC.
 *  When a number of frames are reached, it sets this behavior identifier to false.
 *  
 *  Result of implementation:
 *  When IR on NC1 is triggered, NC1 will actuate its LED_pin and NC2 will also actuate its LED_pin.
 */

bool active_behaviors[2]; //Variable to keep track of which behavior is active. 
int frame_count[2]; //To keep track of time the behavior is active
int IR_triggered = 0; //Behavior 1
int Signal_NC = 1; //Behavior 2


float elapsed_millis; //Timing Parameter
float current_millis; //Timing Parameter

//IR - variable declaration
int IR_pin=A16; //Pin dec
int IR_value; //Value read from pin
int IR_threshold = 400; //Threshold
int LED_pin = 17; //LED pin actuated. Test with pin 13. 



int pin_send_signal = 30; //Pin to transmit signal through to neighboring NC
int active_time = 3000; //Time each pin is actuated to high

int pin_receive_signal = 31; // Pin to receive signal from neighboring NC
int Data_from_NC; //Data read from the pin above
int frame_duration = 1; //Duration of each frame. Kept as 1 ms here.
int delay_time_signal = 1000;

void setup() {
  // put your setup code here, to run once:
  current_millis = millis();
  pinMode(pin_send_signal, OUTPUT);
  pinMode(pin_receive_signal, INPUT);
  pinMode(IR_pin, INPUT);
  pinMode(LED_pin, OUTPUT);
  Serial.begin(9600);
}

//Function that is run when the IR triggered behavior is active
void actuate_LED(){
  frame_count[IR_triggered]++; //Increment frame count
  Serial.println("HERE");
  
  //If the behavior is active, then actuate LED to HIGH and transmiting pin to high
  digitalWrite(LED_pin, HIGH);  
  
  if(frame_count[IR_triggered]>delay_time_signal)
  {
    digitalWrite(pin_send_signal, HIGH);
  }
  
  if(frame_count[IR_triggered] > active_time) //Set upper limit on frame count that the behavior is active
  {
    Serial.println(frame_count[IR_triggered]);
    active_behaviors[IR_triggered] = false; //Set behavior identifier to false
    digitalWrite(LED_pin, LOW); //Actuate to 0
    digitalWrite(pin_send_signal, LOW); //Actuate to 0
    frame_count[IR_triggered] = 0;
  }
}

//Function that is run when the signal from neighboring NC is received
void send_signal()
{
  
  //Increment frame count
  frame_count[Signal_NC]++;
  
  //If the behavior is active, then actuate LED to HIGH and transmiting pin to high
  if(frame_count[Signal_NC]>delay_time_signal)
  {
    digitalWrite(pin_send_signal, HIGH);
  }
  digitalWrite(LED_pin, HIGH);

  if(frame_count[Signal_NC] > active_time) //Set upper limit on frame count that the behavior is active
  {
    active_behaviors[Signal_NC] = false; //Set behavior identifier to false
    frame_count[Signal_NC] = 0; 
    digitalWrite(pin_send_signal, LOW); //Actuate to 0
    digitalWrite(LED_pin, LOW); //Actuate to 0
  }
}


void loop() {
  elapsed_millis = millis()-current_millis; //Check how much time has passed between frames. If greater than frame duration, enter frame
  if( elapsed_millis > frame_duration || elapsed_millis<0)
  {
    current_millis = millis(); //Reset time to obtain new elapsed time for next frame.

//    Serial.print("IR Behavior:  ");
//    Serial.println(active_behaviors[Signal_NC]);
//    Serial.print("Send Signal Behavior:  ");
//    Serial.println(active_behaviors[Signal_NC]);
    IR_value = analogRead(IR_pin); //Read IR value. 
//    Serial.println(IR_value);
    if(IR_value > IR_threshold)
    {
      active_behaviors[IR_triggered] = true; //Turn IR triggered behavior on 
      frame_count[IR_triggered]= 0; //Reset frame count
    }

    Data_from_NC = analogRead(pin_receive_signal); //Read signal coming from neighboring NC. The value will either be 0-50 (some background noise) or 1023. 
    if(Data_from_NC > 1000)
    {
      active_behaviors[Signal_NC] = true; //Set behavior identifier as true
      frame_count[Signal_NC] = 0; //Reset frame count
    } 

    if(active_behaviors[IR_triggered] == true)
    {
      actuate_LED();
    }

    if(active_behaviors[Signal_NC] == true)
    {
      send_signal();
    }
    
  }
}
