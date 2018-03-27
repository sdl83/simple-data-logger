#define trigPin 12
#define echoPin 13

unsigned long targetTime=0;
const unsigned long intervall=500;

//#define led 11
//#define led2 10

void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(led, OUTPUT);
  //pinMode(led2, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
//  if (distance < 4) {  // This is where the LED On/Off happens
//    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
//  digitalWrite(led2,LOW);
//}
//  else {
//    digitalWrite(led,LOW);
//    digitalWrite(led2,HIGH);
//  }
//  if (distance >= 200 || distance <= 0){
//    Serial.println("Out of range");
//  }
//  else {
  
  if(millis()>=targetTime){
    if (distance >= 200){
      Serial.println(200);
    } else if (distance <= 0) {
      Serial.println(0);
    }
    else {
      Serial.println(distance);
      targetTime= millis()+intervall;
    }
  }
}
