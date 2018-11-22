int Motor = 17; //Pin H Connection
int test_LED=13; //Test LED on Teensy

void setup() {
  // put your setup code here, to run once:
  pinMode(Motor, OUTPUT);
  pinMode(test_LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Motor,HIGH);
  digitalWrite(test_LED, HIGH);

  delay(1000); // Time to keep on

  digitalWrite(Motor,LOW);
  digitalWrite(test_LED, LOW);

  delay(1000); //Time to keep off

}
