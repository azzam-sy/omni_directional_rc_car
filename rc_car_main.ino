//NOTES GO HERE

//when controller off
//ch2 betw 1400 and 1500
//ch3 betw 800 and 900
//ch5 betw 1400 and 1500
//ch7 betw 1400 and 1500

//this is sums what i learned from the controller tutorial
//pulsein(examplechannel, HIGH); //got this from a tutorial

//NOTES END HERE


//Servo stuff
#include <Servo.h> //got this from a tutorial
//Goes from front --- points forward
Servo servoR;
//Goes from back --- points backward
Servo servoL;
//Servo max angle
const int servoMax = 180;
//Servo min angle
const int servoMin = 0;
//Saves current time when the visible ServoPanic code runs
unsigned long servoTime = 0;
//The interval between each run of the visible ServoPanic code
unsigned long servoDur = 400;



//Saves current time for when car is too close to an object
unsigned long functionalTime = 0;
//Time spent going in automatic reverse
const int stoppedDur = 1000;




//Input states
int ch2Mode = 0;
int ch3Mode = 0;
int ch5Mode = 0;
int ch7Mode = 0;


//pins bundled together in human logic
const int ch2Pin = 2;
const int ch5Pin = 4;

//pins bundled together in human logic
const int ch3Pin = 3;
const int ch7Pin = 5;




//pins related to A0 = back right wheel
const int br1Pin = 30;
const int br2Pin = 32;
//pins related to A1 = front right wheel
const int fr1Pin = 34;
const int fr2Pin = 36;
//pins related to A2 = back left wheel
const int bl1Pin = 22;
const int bl2Pin = 24;
//pins related to A3 = front left wheel
const int fl1Pin = 26;
const int fl2Pin = 28;


//Globals for wheel HIGH/LOW values
//back right wheel
int br1G = LOW;
int br2G = LOW;
//front right wheel
int fr1G = LOW;
int fr2G = LOW;
//back left wheel
int bl1G = LOW;
int bl2G = LOW;
//front left wheel
int fl1G = LOW;
int fl2G = LOW;


//analogWrite value (changes from LOW or HIGH since wheels don't seem to change speed)
int PWM;




//Ultrasonic sensor pins
const int echoPin = 6;
const int trigPin = 7;
//interval betw trigPin LOW to HIGH for clean signal
const int initialSensorDur = 2;
//interval betw trigPin HIGH to LOW
const int pingSensorDur = 12; //got this from a tutorial
//stores time when trigPin LOW or HIGH
unsigned long pingSensorPreviousTime1 = 0;
unsigned long pingSensorPreviousTime2 = 0;
//the resulting distance stored here --- set to 40 intially so car can function right away without backing up for no reason
int distance = 40;




//Servo pins
const int servoPin1 = 8;
const int servoPin2 = 9;




//Front Left Wheel OFF
void FLW_OFF(){
  fl1G = LOW;
  fl2G = LOW;
}
//Front Right Wheel OFF
void FRW_OFF(){
  fr1G = LOW;
  fr2G = LOW;
}
//Back Left Wheel OFF
void BLW_OFF(){
  bl1G = LOW;
  bl2G = LOW;
}
//Back Right Wheel OFF
void BRW_OFF(){
  br1G = LOW;
  br2G = LOW;
}


//Front Left Wheel Clock-Wise
void FLW_CW(){
  fl1G = HIGH;
  fl2G = LOW;
}
//Front Left Wheel Counter-Clock-Wise
void FLW_CCW(){
  fl1G = LOW;
  fl2G = HIGH;
}


//Front Right Wheel Clock-Wise
void FRW_CW(){
  fr1G = HIGH;
  fr2G = LOW;
}
//Front Right Wheel Counter-Clock-Wise
void FRW_CCW(){
  fr1G = LOW;
  fr2G = HIGH;
}


//Back Left Wheel Clock-Wise
void BLW_CW(){
  bl1G = HIGH;
  bl2G = LOW;
}
//Back Left Wheel Counter-Clock-Wise
void BLW_CCW(){
  bl1G = LOW;
  bl2G = HIGH;
}


//Back Right Wheel Clock-Wise
void BRW_CW(){
  br1G = HIGH;
  br2G = LOW;
}
//Back Right Wheel Counter-Clock-Wise
void BRW_CCW(){
  br1G = LOW;
  br2G = HIGH;
}


//Wheels cannot move
void StandStill(){
  FLW_OFF();
  FRW_OFF();
  BLW_OFF();
  BRW_OFF();
}




//BOTH Left Button AND Right Button NEUTRAL ch5 = 2
//Straight FORWARD
void NeutralF(){
  FLW_CW();
  FRW_CW();
  BLW_CW();
  BRW_CW();
}
//Straight BACKWARD
void NeutralB(){
  FLW_CCW();
  FRW_CCW();
  BLW_CCW();
  BRW_CCW();
}
//Straight RIGHT
void CrabR(){
  FLW_CW();
  FRW_CCW();
  BLW_CCW();
  BRW_CW();
}
//Straight LEFT
void CrabL(){
  FLW_CCW();
  FRW_CW();
  BLW_CW();
  BRW_CCW();
}


//Right Button ON ch5 = 3
//Diagonal FORWARD to the right
void DiagRF(){
  FLW_CW();
  FRW_OFF();
  BLW_OFF();
  BRW_CW();
}
//Diagonal BACKWARD to the right
void DiagRB(){
  FLW_CCW();
  FRW_OFF();
  BLW_OFF();
  BRW_CCW();
}
//Diagonal FORWARD to the left
void DiagLF(){
  FLW_OFF();
  FRW_CW();
  BLW_CW();
  BRW_OFF();
}
//Diagonal BACKWARD to the left
void DiagLB(){
  FLW_OFF();
  FRW_CCW();
  BLW_CCW();
  BRW_OFF();
}


//Right Button OFF ch5 = 1
//Pivotting around the RIGHT wheels CLOCK-WISE
void PivotR_CW(){
  FLW_CW();
  FRW_OFF();
  BLW_CW();
  BRW_OFF();
}
//Pivotting around the right wheels COUNTER-CLOCK-WISE
void PivotR_CCW(){
  FLW_CCW();
  FRW_OFF();
  BLW_CCW();
  BRW_OFF();
}
//Pivotting around the LEFT wheels COUNTER-CLOCK-WISE
void PivotL_CW(){
  FLW_OFF();
  FRW_CW();
  BLW_OFF();
  BRW_CW();
}
//Pivotting around the left wheels CLOCK-WISE
void PivotL_CCW(){
  FLW_OFF();
  FRW_CCW();
  BLW_OFF();
  BRW_CCW();
}


//Left Button ON ch7 = 3
//Pivotting around the BACK wheels CLOCK-WISE
void PivotB_CW(){
  FLW_CW();
  FRW_CCW();
  BLW_OFF();
  BRW_OFF();
}
//Pivotting around the left wheels COUNTER-CLOCK-WISE
void PivotB_CCW(){
  FLW_CCW();
  FRW_CW();
  BLW_OFF();
  BRW_OFF();
}
//Pivotting around the FRONT wheels CLOCK-WISE
void PivotF_CW(){
  FLW_OFF();
  FRW_OFF();
  BLW_CW();
  BRW_CCW();
}
//Pivotting around the left wheels COUNTER-CLOCK-WISE
void PivotF_CCW(){
  FLW_OFF();
  FRW_OFF();
  BLW_CCW();
  BRW_CW();
}


//Left Button OFF ch7 = 1
//Pivotting around the center CLOCK-WISE
void PivotC_CW(){
  FLW_CW();
  FRW_CCW();
  BLW_CW();
  BRW_CCW();
}
//Pivotting around the center COUNTER-CLOCK-WISE
void PivotC_CCW(){
  FLW_CCW();
  FRW_CW();
  BLW_CCW();
  BRW_CW();
}



//The folliowinf status checkers will set the mode of their corresponding variables
//Checks the current status of the RIGHT controller button
void RCBStatus(){
  //button down
  if(pulseIn(ch5Pin, HIGH) < 1200){
    ch5Mode = -1;
  }
  //button up
  else if(pulseIn(ch5Pin, HIGH) > 1600){
    ch5Mode = 1;
  }
  //button neutral
  else{
    ch5Mode = 0;
  }
}


//Checks the current status of the LEFT controller button
void LCBStatus(){
  //button down
  if(pulseIn(ch7Pin, HIGH) < 1200){
    ch7Mode = -1;
  }
  //button up
  else if(pulseIn(ch7Pin, HIGH) > 1600){
    ch7Mode = 1;
  }
  //button neutral
  else{
    ch7Mode = 0;
  }
}


//Checks the current status of the RIGHT controller joystick
void RCTStatus(){
  //stick down
  if(pulseIn(ch2Pin, HIGH) < 1200){
    ch2Mode = 1;
  }
  //stick up
  else if(pulseIn(ch2Pin, HIGH) > 1600){
    ch2Mode = -1;
  }
  //stick neutral
  else{
    ch2Mode = 0;
  }
}


//Checks the current status of the LEFT controller joystick
void LCTStatus(){
  //stick down
  if(pulseIn(ch3Pin, HIGH) < 1200){
    ch3Mode = -1;
  }
  //stick up
  else if(pulseIn(ch3Pin, HIGH) > 1600){
    ch3Mode = 1;
  }
  //stick neutral
  else{
    ch3Mode = 0;
  }
}




//Updates Controller modes
void RCMode1(){
  //Joystick BOTH neutral does nothing
  if(ch2Mode == 0 && ch3Mode == 0){
    PWM = 0;
    StandStill();
  }
  //Right stick forward --- car forward
  else if(ch2Mode == 1 && ch3Mode == 0){
    PWM = 255;
    NeutralF();

    //Right servo forward
    servoR.write(180);
    servoL.write(0);
  }
  //Right stick backward --- car backward
  else if(ch2Mode == -1 && ch3Mode == 0){
    PWM = 255;
    NeutralB();

    //Left servo backward
    servoR.write(0);
    servoL.write(180);
  }
  //Left stick forward --- car crabs to the right
  else if(ch2Mode == 0 && ch3Mode == 1){
    PWM = 255;
    CrabR();
  }
  //Left stick backward --- car crabs to the left
  else if(ch2Mode == 0 && ch3Mode == -1){
    PWM = 255;
    CrabL();
  }
}
void RCMode2(){
  //Joystick BOTH neutral does nothing
  if(ch2Mode == 0 && ch3Mode == 0){
    PWM = 0;
    StandStill();
  }
  //Right stick forward --- car goes rightward diagonal forward
  else if(ch2Mode == 1 && ch3Mode == 0){
    PWM = 255;
    DiagRF();
  }
  //Right stick backward --- car goes righttward diagonal backward
  else if(ch2Mode == -1 && ch3Mode == 0){
    PWM = 255;
    DiagLB();
  }
  //Left stick forward --- car goes leftward diagonal forward
  else if(ch2Mode == 0 && ch3Mode == 1){
    PWM = 255;
    DiagLF();
  }
  //Left stick backward --- car goes leftward diagonal backward
  else if(ch2Mode == 0 && ch3Mode == -1){
    PWM = 255;
    DiagRB();
  }
}
void RCMode3(){
  //Joystick BOTH neutral does nothing
  if(ch2Mode == 0 && ch3Mode == 0){
    PWM = 0;
    StandStill();
  }
  //Right stick forward --- car pivots right side cw
  else if(ch2Mode == 1 && ch3Mode == 0){
    PWM = 255;
    PivotR_CW();
  }
  //Right stick backward --- car pivots right side ccw
  else if(ch2Mode == -1 && ch3Mode == 0){
    PWM = 255;
    PivotR_CCW();
  }
  //Left stick forward --- car pivots left side cw
  else if(ch2Mode == 0 && ch3Mode == 1){
    PWM = 255;
    PivotL_CW();
  }
  //Left stick backward --- car pivots left side ccw
  else if(ch2Mode == 0 && ch3Mode == -1){
    PWM = 255;
    PivotL_CCW();
  }
}
void RCMode4(){
  //Joystick BOTH neutral does nothing
  if(ch2Mode == 0 && ch3Mode == 0){
    PWM = 0;
    StandStill();
  }
  //Right stick forward --- car pivots backside cw
  else if(ch2Mode == 1 && ch3Mode == 0){
    PWM = 255;
    PivotB_CW();
  }
  //Right stick backward --- car pivots backside ccw
  else if(ch2Mode == -1 && ch3Mode == 0){
    PWM = 255;
    PivotB_CCW();
  }
  //Left stick forward --- car pivots frontside cw
  else if(ch2Mode == 0 && ch3Mode == 1){
    PWM = 255;
    PivotF_CW();
  }
  //Left stick backward --- car pivots frontside ccw
  else if(ch2Mode == 0 && ch3Mode == -1){
    PWM = 255;
    PivotF_CCW();
  }
}
void RCMode5(){
  //Joystick BOTH neutral does nothing
  if(ch2Mode == 0 && ch3Mode == 0){
    PWM = 0;
    StandStill();
  }
  //Right stick forward --- car pivots based on center cw
  else if(ch2Mode == 1 && ch3Mode == 0){
    PWM = 255;
    PivotC_CW();
  }
  //Right stick backward --- car pivots based on center ccw
  else if(ch2Mode == -1 && ch3Mode == 0){
    PWM = 255;
    PivotC_CCW();
  }
}




//Calculates the distance from front of the car to a nearby object
long CalcDist(){
  //LOW for 2ms
  if(millis() - pingSensorPreviousTime1 >= initialSensorDur){
    pingSensorPreviousTime1 = millis();//updates time
    digitalWrite(trigPin, HIGH);//HIGH //got this from a tutorial
  }
  //Waits for 10ms + 2ms due to the previous if statement
  if(pingSensorPreviousTime2 - millis() >= pingSensorDur){
    pingSensorPreviousTime2 = millis();//updates time
    digitalWrite(trigPin, LOW);//LOW //got this from a tutorial
  }
  // Sound 29 microsec/cm, divide by 29 to get cm; dist travel twice, so divide by 2
  return pulseIn(echoPin, HIGH)/29/2; //got this from a tutorial
}




//Kinda an alarm system --- servos move = controller disconnected
void ServoPanic(){
  //set to 0 or 180
  static int angle = 0;

  //Every 400ms the servo will change from lowest angle to max angle
  if(millis() - servoTime >= servoDur){
    //Saves time code was ran
    servoTime = millis();
    //Sets angle
    servoR.write(angle); //got this from a tutorial
    servoL.write(angle);
    //Changes from max to min and vice versa
    angle==180?angle=0:angle=180;
  }
}




void setup() {
  //Servo setup
  servoR.attach(servoPin1);
  servoL.attach(servoPin2);
  //Start servo at minimum angle first
  servoR.write(0);
  servoL.write(0);


  //A0 = back right wheel
  pinMode(br1Pin, OUTPUT);
  pinMode(br2Pin, OUTPUT);
  //A1 = front right wheel
  pinMode(fr1Pin, OUTPUT);
  pinMode(fr2Pin, OUTPUT);
  //A2 = back left wheel
  pinMode(bl1Pin, OUTPUT);
  pinMode(bl2Pin, OUTPUT);
  //A3 = front left wheel
  pinMode(fl1Pin, OUTPUT);
  pinMode(fl2Pin, OUTPUT);


  //right hand
  pinMode(ch2Pin, INPUT);
  pinMode(ch5Pin, INPUT);
  //left hand
  pinMode(ch3Pin, INPUT);
  pinMode(ch7Pin, INPUT);


  //Ping sensor
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  //Ensure pin is low initial
  digitalWrite(trigPin, LOW);
  Serial.begin(9600);
}




void loop() {
  //Stores distance
  distance = CalcDist();
  //Enables RC inputs
  RCBStatus();
  LCBStatus();
  RCTStatus();
  LCTStatus();

  //Checks if the controller isnt connected and the channels are outputting random values
  if((pulseIn(ch2Pin, HIGH)>=1400 && pulseIn(ch2Pin, HIGH)<=1500)  &&  (pulseIn(ch3Pin, HIGH)>=800 && pulseIn(ch3Pin, HIGH)<=900)  &&  (pulseIn(ch5Pin, HIGH)>=1400 && pulseIn(ch5Pin, HIGH)<=1500)  &&  (pulseIn(ch7Pin, HIGH)>=1400 && pulseIn(ch7Pin, HIGH)<=1500)){
    //stops car completely
    PWM = 0;
    StandStill();
    //servos start "spinning" to show controller is DC
    ServoPanic();
    //Serial.println("Controller Disconnected");
  }

  //Driving related enablers --- when car is not too close to an object
  else if(distance >= 20){
    //when both buttons neutral
    if(ch5Mode == 0 && ch7Mode == 0){
      RCMode1();
    }
    //right button up left button neutral
    else if(ch5Mode == 1 && ch7Mode == 0){
      RCMode2();
    }
    //right button down left button neutral
    else if(ch5Mode == -1 && ch7Mode == 0){
      RCMode3();
    }
    //right button neutral left button up
    else if(ch5Mode == 0 && ch7Mode == 1){
      RCMode4();
    }
    //right button neutral left button down
    else if(ch5Mode == 0 && ch7Mode == -1){
      RCMode5();
    }

    //stores the time the car is functioning as intended and not too close to an object
    functionalTime = millis();
  }

  //Automatically reverses when too close to a wall
  else{
    //checks if 2 seconds has passed
    if(millis() - functionalTime <= stoppedDur){
      //revs up the motors to max speed(the best kinda speed)
      PWM = 255;
      //goes backwards
      NeutralB();
    }
  }


  //got this from a tutorial
  //Sends out a signal to drive motors at LOW or HIGH
  analogWrite(A0, PWM);
  analogWrite(A1, PWM);
  analogWrite(A2, PWM);
  analogWrite(A3, PWM);
  //motors stall too much when it's not HIGH or LOW output
  //got this from a tutorial

  //got this from a tutorial
  //Determins direction by outputting LOW or HIGH
  digitalWrite(br1Pin, br1G);
  digitalWrite(br2Pin, br2G);

  digitalWrite(fr1Pin, fr1G);
  digitalWrite(fr2Pin, fr2G);

  digitalWrite(bl1Pin, bl1G);
  digitalWrite(bl2Pin, bl2G);

  digitalWrite(fl1Pin, fl1G);
  digitalWrite(fl2Pin, fl2G);
  //got this from a tutorial
}