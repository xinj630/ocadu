int pinBreath;
int pinSensor;
int pinFeedback;
int sensorRead;
int thresholdLow;
int thresholdMid;
int thresholdHigh;
unsigned long time;

// Breathing light function for frequency reference
// 600 ms interval roughly translate into 100 ticks per minute
int breathingLight(int min, int max, int frequency){
  float angle = (millis() % frequency) / (float)frequency * M_PI;
  float sine = sin(angle);
  return map(sine * 1000, -1000, 1000, min, max);
}

void setup() {
  pinBreath = 2;
  pinSensor = A0;
  pinFeedback = 12;
  sensorRead = 0;
  thresholdLow = 100;
  thresholdMid = 200;
  thresholdHigh = 255;
  Serial.begin(9600);
  pinMode(pinBreath, OUTPUT);
  pinMode(pinFeedback, OUTPUT);
}

void loop() {
  // Frequency lights
  int output = breathingLight(1, 255, 600);
  analogWrite(pinBreath, output);
  
  // Sensor reading for debugging, check serial monitor
  sensorRead = analogRead(pinSensor);
  constrain(sensorRead, 0, 255);
  Serial.print("sensorRead=");
  Serial.print(sensorRead);
  Serial.print('\n');
 
  // Feedback lights 
  if(sensorRead >= thresholdHigh){  
    analogWrite(pinFeedback, 255);
  }else if(sensorRead < thresholdHigh && sensorRead >= thresholdMid){
    analogWrite(pinFeedback, 128);
  }else{
    analogWrite(pinFeedback, 1);
  }
}
