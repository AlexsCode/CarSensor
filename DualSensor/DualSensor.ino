#define trigPin 10
#define echoPin 13
#define trigPin1 2
#define echoPin1 3


void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  } // setting up 2 sensors trigger and echo pins,

void loop() {
  float duration,duration1, distance,distance1; 
  digitalWrite(trigPin,LOW);
  digitalWrite(trigPin1,LOW);
  delayMicroseconds(2);
  // main loop starting conditions
  
  //Left Sensor sending out pulse and recording the response time
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2) * 0.0344; // converting the response into a distance.
  
  
  //Right Sensor sending out pulse and recording the response time
  digitalWrite(trigPin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1,LOW);
  duration1 = pulseIn(echoPin1,HIGH);
  distance1 = (duration1 /2) * 0.0344;

 // Serial Output 
    Serial.print("Left:");
    Serial.print(distance1);
    Serial.print(" ");
    Serial.print("Right");
    Serial.println(distance);       
//    Serial.println(" cm");
 
    delay(1000); // hard coded delay, can be adjusted for tuning the polling rate of sensors
}
