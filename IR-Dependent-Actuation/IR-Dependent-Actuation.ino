/* Actuate LED as a response to an IR Trigger
 * When the proximity of the user to the IR becomes greater than a defined threshold, the LED/DC motor will be actuated 
 */

 int test_LED_pin = 17; //Test LED Code
 int IR_pin = A16; //IR pin in port P0
 int IR_value; //Values received from input pin
 int IR_threshold = 300; //Proximity above which LED actuated
 
 void setup()
 {
  pinMode(test_LED_pin, OUTPUT); //Declate pin 13 as an OUTPUT component
  pinMode(IR_pin, INPUT); //Declare Pin 27 as an input component
  Serial.begin(9600);
 }

 void loop()
 {
  IR_value = analogRead(IR_pin);
  Serial.println(IR_value);
  if(IR_value > IR_threshold)
  {
  digitalWrite(test_LED_pin, HIGH);
  delay(1000);
  digitalWrite(test_LED_pin, LOW);
  delay(1000);
  Serial.println("Triggered");
  }
  
 }
