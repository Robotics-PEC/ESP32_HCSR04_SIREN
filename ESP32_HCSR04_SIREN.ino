
// the setup function runs once when you press reset or power the board
#define trig 2
#define echo 4
#define min_trigger_interval 5 // in ms
#define detect_distance 25 // in cm
#define min_siren_on_time 500 // in ms
#define siren 19

bool previous_state = 0;
unsigned long t_start = 0;
unsigned long t_end = 0;
unsigned long t_last_trigger = 0;
unsigned long t_high_time= 0;
int distance = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  pinMode(siren , OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if(previous_state == 0 && millis() - t_last_trigger > min_trigger_interval)
  {
  digitalWrite(trig , LOW);
  delayMicroseconds(2);
  digitalWrite(trig , HIGH);
  delayMicroseconds(10);
  digitalWrite(trig , LOW);
  
  }
  if(previous_state == 0 && digitalRead(echo) == HIGH)
  {
    previous_state = 1;
    t_start = micros();
  }
  if(previous_state == 1 && digitalRead(echo) == LOW)
  {
    t_end = micros();
    previous_state = 0;
    distance = (unsigned long)(t_end - t_start) * 0.033/2;
    Serial.print("Distance is ");
    Serial.println(distance);
    delay(100);
    if(distance < detect_distance)
    {
      digitalWrite(siren,HIGH);
      t_high_time = millis();
    }
  }
  if(millis() - t_high_time > min_siren_on_time)
  {
    digitalWrite(siren,LOW);
  }
}
