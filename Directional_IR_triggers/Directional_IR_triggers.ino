/* IR triggers - 2 IRs
 * Separate triggers and obtain direction using timing parameters
 * When you go from right to left, port H will be triggered
 * When you go from left to right, port C will be triggered
 */

//frame by frame approach parameters
float current_millis;
float elapsed_millis;
int frame_duration=1;

int IR_pin1 = A16; //IR on right Port A
int IR_pin2 = A11; //IR on left Port B

int threshold1= 300; //Threshold for IR trigger 1
int threshold2= 300; // Threshold for IR trigger 2

int timing1=0; //Timing Parameter 1
int timing2=0; //Timing Parameter 2

int IR_value1; //The value read on pin 1
int IR_value2; //The value read on pin 2

void setup() {
  // Declate all pins
  pinMode(IR_pin1, INPUT);
  pinMode(IR_pin2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(17, OUTPUT);
  current_millis = millis();
  Serial.begin(9600);
}

void loop() {
  elapsed_millis = millis() - current_millis; //Frame duration 
  if(elapsed_millis > frame_duration)
  {
    current_millis = millis();
    IR_value1 = analogRead(IR_pin1);
    IR_value2 = analogRead(IR_pin2);

  //When you detect the first trigger, start incrementing the timing parameter
    if(IR_value1>threshold1) 
      timing1++;
    if(IR_value2>threshold2)
      timing2++;

   // After the first trigger, keep incrementing the timing parameter. This will keep the IR as active.
    if(timing1>0)
      timing1++;
  
    if(timing2>0)
      timing2++;

  //When one IR is active, if a trigger is detected on the other IR, then the LED is actuated. 
    if(timing1>timing2)
    {
      if(timing2>0){
        //Going Left to right
        digitalWrite(3,HIGH);
      }
    }
  
    if(timing2>timing1)
    {
      if(timing1>0)
      {
        //Going Right to Left
        digitalWrite(17,HIGH);
      }
    }

  //Upper limit on timing parameter
    if(timing1>3000 || timing2>3000)
    {
      timing1=0;
      timing2=0;
      digitalWrite(3,LOW);
      digitalWrite(17,LOW);
    }

    Serial.print("Timing 1: ");
    Serial.println(timing1);
    Serial.print("Timing 2: ");
    Serial.println(timing2);
  }
}
