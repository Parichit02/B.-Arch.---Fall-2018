int pin_SMA = 3;
float current_millis;
float elapsed_millis;
float frame_duration = 1;
int frame_count = 0;

void setup() {
  // put your setup code here, to run once:
  current_millis = millis();
  pinMode(pin_SMA, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  elapsed_millis = millis()-current_millis;
  if(elapsed_millis >=frame_duration)
  {
    current_millis = millis();
    frame_count++;
    if(frame_count<2000)
    {
      digitalWrite(pin_SMA, HIGH);
    }
    if(frame_count>2000)
    {
      digitalWrite(pin_SMA, LOW);
    }

    if(frame_count>17000)
    {
      frame_count=0;
    }
  }
}
