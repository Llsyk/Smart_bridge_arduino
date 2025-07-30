    #include <Servo.h>
#define pinab  6 
#define pin1ab 12
#define pin2ab 13
int ultra_1 = 1;
bool beep = 0;
int buzzerPin = 2;
int LED= 13;
// constants won't change
const int trig_pin_1 = 8; 
const int echo_pin_1 = 7;

const int trig_pin_2 = 4; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int echo_pin_2 = 5;

const int DISTANCE_THRESHOLD = 50; // centimeters
const int servo1Pin = 9;   
const int servo2Pin = 10; 
const int servo3Pin = 3;   
const int servo4Pin = 11; 
int delayTime =15;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
 // create servo object to control a servo

// variables will change:

long duration , distance ;
int sensor_1 , sensor_2 ;

void setup() {
  Serial.begin (9600); 
  
  pinMode(trig_pin_1, OUTPUT); 
  pinMode(echo_pin_1, INPUT); 

  pinMode(trig_pin_2, OUTPUT); 
  pinMode(echo_pin_2, INPUT); 

  pinMode (LED, OUTPUT);
  pinMode (buzzerPin, OUTPUT);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin); // attaches the servo on pin 9 to the servo object
pinMode(pinab,OUTPUT);
pinMode(pin1ab,OUTPUT);
pinMode(pin2ab,OUTPUT);
lift(0,90);
}

void loop() {
  analogWrite(pinab,125);
  SonarSensor(trig_pin_1, echo_pin_1);
  sensor_1=distance;
  sensor_1=check(sensor_1);
  Serial.print("sensor_1 :");
  Serial.println(sensor_1);
  SonarSensor(trig_pin_2, echo_pin_2);
  sensor_2=distance;
  sensor_2=check(sensor_2);
  Serial.print("sensor_2 :");
  Serial.println(sensor_2);
  if (ultra_1==1)
  {
  if( sensor_1==1)
  {
       down(90,0);beep=1;b_lift();
  }
  // if (beep==1){buzz_led();}
  // else off();
  if(sensor_2==1)
    {
       b_down();lift(0,90);
      ultra_1=0;beep=0; 
       return;     
    }
    Serial.println(ultra_1);
  }
  if (ultra_1==0)
  {
if( sensor_2==1)
    {beep=1;down(90,0);b_lift();}
  //   if (beep==1){buzz_led();}
  // else off();
if(sensor_1==1)
{
  lift(0,90);beep=0;b_down();
  ultra_1=1;return;
}
Serial.println(ultra_1);
}
  // if (ultra_1==0)
  // {
  //       if(sensor_2 < DISTANCE_THRESHOLD && sensor_2 > 0)
  //         {
  //           down();
  //         }
  //      if(sensor_1 > DISTANCE_THRESHOLD-20 && sensor_1 > 0 && sensor_1 < DISTANCE_THRESHOLD)
  //         {
  //           ultra_1 = 1;
  //           // ultra_2 = 1;
  //           lift();
  //         }
  //   Serial.println(ultra_1);
  // }
  // if(ultra_1 == 1 && ultra_2 == 0){
  //   servo1.write(90);
  //   servo2.write(90);
  //   delay(5000);
  //   servo3.write(90);
  //   servo4.write(90);

  //   ultra_1 = 1;
 
  // }

//   if( ultra_2 == 1){
    
// down();
//   }

  // if(ultra_1 == 0 && ultra_2 == 0){
    
  //   servo1.write(0);
  //   servo2.write(0);
  //   servo3.write(0);
  //   servo4.write(0);
   
    
  // }

  // if(ultra_1 == 0 && ultra_2 == 1){
  // lift();

  // }

delay(500);

}


void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}
void lift (int a, int b)
{
    for (int i = a; i <= b; i++) {
      servo1.write(i);
      servo2.write(i);
      servo3.write(i);
      servo4.write(i);      
      delay(delayTime);
    }
    Serial.println("up");
}
void down(int a,int b)
{
    for (int i = a; i >= b; i--) {
      servo1.write(i);
      servo2.write(i);
      delay(delayTime);
    }
    delay(2000);
    for (int i = a; i >= b; i--) {
      servo3.write(i);
      servo4.write(i);      
      delay(delayTime);
    }
    Serial.println("down");
}
void buzz_led()
{
  for(int i=0;i<4;i++){
digitalWrite(buzzerPin, HIGH);
  digitalWrite(LED, HIGH);
    delay(60);
digitalWrite(buzzerPin, LOW);
 digitalWrite(LED, LOW);
delay(30);}
}
int check(int a)
{
  if(a<DISTANCE_THRESHOLD&&a>0)
  {return 1;}
  else 
  {return 0;}
}
void off()
{
  digitalWrite(buzzerPin, LOW);
  delay(60);
  digitalWrite(LED, LOW);
}
void moveServosSlowly(int startPos, int endPos) {
  if (startPos < endPos) {
    for (int i = startPos; i <= endPos; i++) {
      servo1.write(i);
      servo2.write(i);
      delay(delayTime);
    }
    delay(2000);
    for (int i = startPos; i <= endPos; i++) {
      servo3.write(i);
      servo4.write(i);      
      delay(delayTime);
    }
  } else {
    for (int i = startPos; i >= endPos; i--) {
      servo1.write(i);
      servo2.write(i);
     
      servo3.write(i);
      servo4.write(i);
      delay(delayTime);
    }
  }
}
void b_lift()
{
  digitalWrite(pin1ab,HIGH);
  digitalWrite(pin2ab,LOW);
  delay(3000);
  digitalWrite(pin1ab,LOW);
  digitalWrite(pin2ab,LOW); 
  Serial.println("Bridge lift");
}
void b_down()
{
  digitalWrite(pin1ab,LOW);
  digitalWrite(pin2ab,HIGH);
  delay(3000);
  digitalWrite(pin1ab,LOW);
  digitalWrite(pin2ab,LOW);
  Serial.println("Bridge down");
}