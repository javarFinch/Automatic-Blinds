int phototrans1 = A0;
int phototrans2 = A1;
int reading = 0;
int redLED = 4;
bool closed = true;
#include <Servo.h>
Servo myservo;
Servo servo2;
void setup() {
  // put your setup code here, to run once:
  pinMode(phototrans1,INPUT);
  pinMode(phototrans2,INPUT);
  myservo.attach(9);
  servo2.attach(10);
  Serial.begin(9600);

}

bool getSamples() {
  int count = 0;
  for (int i = 0; i < 50; i++) {
    reading = analogRead(phototrans2);
    
    if (reading > 750) {
      count++;
    }
    int second = analogRead(phototrans1);
    if (second > 750) {
      count++;
    }
    }
    if (count >= 75) {
      return false;
    } else {
      return true;
    }
}


void closeBlinds() {
  myservo.write(180);
  servo2.write(158);
  delay(7000);
  //myservo.write(889);
  closed = true;
  Serial.println("Blinds closed");
}

void openBlinds() {
  myservo.write(0);
  servo2.write(20);
  delay(7000);
  closed = false;
  Serial.println("Blinds Opened");
}

int getAvgReading(int val, int val2) {
  int avg = (val + val2)/2;
  return avg;
}

void loop() {
  unsigned long currentTime = millis();
     bool shouldOpen = getSamples();
  if (closed) {
    if (shouldOpen) {
        openBlinds();
        myservo.write(90);
        delay(120000);
    } else {
      myservo.write(90);
    }
  } else {
    if (shouldOpen) {
      myservo.write(90);
    } else {
        closeBlinds();
        myservo.write(90);  
        delay(120000);
    }
  }
  delay(100);

}
