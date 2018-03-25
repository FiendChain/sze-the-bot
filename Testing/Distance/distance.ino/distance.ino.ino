const int trigPin = 9;    // change pin here
const int echoPin = 10;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);   // make sure trig pin is clear
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);  // send signal out
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  //delay(500);                 // put delay in ms
  
}
