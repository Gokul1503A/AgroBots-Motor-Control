#include<math.h>

// pins for leftside 1st motor

const int l1s1 = 2;

const int l1p1 = 5;
const int l1d1 = 4;

// state of l1 pulse from encoder
volatile bool l1s1s = LOW;


// count of l1 pulses from encoder
int l1s1c = 0;

 
// pins for rightside 1st motor
const int r1s1 = 3;

const int r1p1 = 6;
const int r1d1 = 8;

// state of r1 pulse from encoder
volatile bool r1s1s = LOW;


// count of r1 pulses from encoder
int r1s1c = 0;


//pins for lest side 2nd motor

const int l2p1 = 9;
const int l2d1 = 12;



//pins for rightside 2nd motor

const int r2p1 = 10;
const int r2d1 = 13;



// pins for left third motor
int l3p1 = 14;
int l3d1 = 15;

// pins for right third motor
int r3p1 = 16;
int r3d1 = 17;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //l1 control pins
  pinMode(l1p1, OUTPUT);
  pinMode(l1d1, OUTPUT);

  //l1 motor ISR 
  attachInterrupt(digitalPinToInterrupt(l1s1), l1ISR, RISING);
  

  //r1 control pins
  pinMode(r1p1, OUTPUT);
  pinMode(r1d1, OUTPUT);

  //r1Motor ISR
  attachInterrupt(digitalPinToInterrupt(r1s1), r1ISR, RISING);
  

  //l2 control pins
  pinMode(l2p1, OUTPUT);
  pinMode(l2d1, OUTPUT);

 

  //r2 control pins
  pinMode(r2p1, OUTPUT);
  pinMode(r2d1, OUTPUT);

  //l3 control 
  pinMode(l3p1, OUTPUT);
  pinMode(l3d1, OUTPUT);

  //r3 control

  pinMode(r3p1, OUTPUT);
  pinMode(r3d1, OUTPUT);

 

}

void moveForward(){
  
  // l1 motor run forward
  digitalWrite(l1p1,HIGH);
  digitalWrite(l1d1,HIGH);

  // r1 motor run forward
  digitalWrite(r1p1,HIGH);
  digitalWrite(r1d1,HIGH);

  // l2 motor run forward
  digitalWrite(l2p1,HIGH);
  digitalWrite(l2d1,LOW);

  // r2 motor run forward
  digitalWrite(r2p1,HIGH);
  digitalWrite(r2d1,LOW);


  // l3 motor run forward
  digitalWrite(l3p1,HIGH);
  digitalWrite(l3d1,HIGH);

  // r2 motor run forward
  digitalWrite(r3p1,HIGH);
  digitalWrite(r3d1,LOW);

}

void moveBackward(){
  
  // l1 motor run backward
  digitalWrite(l1p1,HIGH);
  digitalWrite(l1d1,LOW);

  // r1 motor run backward
  digitalWrite(r1p1,HIGH);
  digitalWrite(r1d1,LOW);

  // l2 motor run backward
  digitalWrite(l2p1,HIGH);
  digitalWrite(l2d1,HIGH);

  // r2 motor run backward
  digitalWrite(r2p1,HIGH);
  digitalWrite(r2d1,HIGH);

  // l3 motor run backward
  digitalWrite(l3p1,HIGH);
  digitalWrite(l3d1,LOW);

  // r2 motor run backward
  digitalWrite(r3p1,HIGH);
  digitalWrite(r3d1,HIGH);

}

void Stop(){
  digitalWrite(l1p1,LOW);
  digitalWrite(r1p1,LOW);
  digitalWrite(l2p1,LOW);
  digitalWrite(r2p1,LOW);
  digitalWrite(l3p1,LOW);
  digitalWrite(r3p1,LOW);

}


void moveStraight(int count){
  
  //measuring rotaions of wheel
  while(r1s1c<count )
  {
    moveForward(); // print statemets to add necesary delay **required
    Serial.print("(");
      Serial.print(l1s1c);
      Serial.print(",");
      Serial.print(r1s1c);
      Serial.print(",");
      Serial.println(")");

    if(r1s1c>count )
    {
      break;
    }

  }

  Stop();
  
}

void moveBack(int count){
  
  //measuring rotaions of wheel
  while(l1s1c<count )
  {
    moveBackward();
    Serial.print("(");
      Serial.print(l1s1c);  // print statemets to add necesary delay **required
      Serial.print(",");
      Serial.print(r1s1c);
      Serial.print(",");
      Serial.println(")");

    if(l1s1c>count ) //and r1s2c>count and l2s2c>count and r2s2c>count
    {
      break;
    }

  }

  Stop();
  
}

void turn(int angle)
{
  float turning_raduis = (55/2.0);
  float circumference = 2.0*PI*turning_raduis;
  float distance = (angle / 360.0) * circumference;
  float rotations = distance/ (PI*10);

  

  if (angle<0)
  {
    l1s1c = 0;
    int lcount = rotations * 700;
    if (lcount< 0)
    {
      lcount = (lcount * -1);
    }
    
    

    
    r1s1c = 0;
    int rcount = rotations * 700;
    if (rcount< 0)
    {
      rcount = (rcount * -1);
    }

   
    while(l1s1c<lcount and r1s1c<rcount) //measuring rotaions of wheel
    {
      // l1 motor run backward
      digitalWrite(l1p1,HIGH);
      digitalWrite(l1d1,LOW);

      // r1 motor run forward
      digitalWrite(r1p1,HIGH);
      digitalWrite(r1d1,HIGH);

      // l2 motor run backward
      digitalWrite(l2p1,HIGH);
      digitalWrite(l2d1,HIGH);

      // r2 motor run forward
      digitalWrite(r2p1,HIGH);
      digitalWrite(r2d1,LOW);

      // l3 motor run backward
      digitalWrite(l3p1,HIGH);
      digitalWrite(l3d1,LOW);

      // r2 motor run Forward
      digitalWrite(r3p1,HIGH);
      digitalWrite(r3d1,LOW);

      Serial.print("(");
      Serial.print(l1s1c);
      Serial.print(",");
      Serial.print(r1s1c);
      Serial.print(",");
      Serial.println(")");
    }
    Stop();
  }

  

  if (angle>0)
  {
    l1s1c = 0;
    int lcount = rotations * 1400;
    if (lcount< 0)
    {
      lcount = (lcount * -1);
    }
    
    r1s1c = 0;

    r1s1c = 0;
    int rcount = rotations * 700;
    if (rcount< 0)
    {
      rcount = (rcount * -1);
    }
   
    while(l1s1c<lcount and r1s1c<rcount) //measuring rotaions of wheel
    {
      // l1 motor run forward
      digitalWrite(l1p1,HIGH);
      digitalWrite(l1d1,HIGH);

      // r1 motor run backward
      digitalWrite(r1p1,HIGH);
      digitalWrite(r1d1,LOW);

      // l2 motor run forward
      digitalWrite(l2p1,HIGH);
      digitalWrite(l2d1,LOW);

      // r2 motor run backward
      digitalWrite(r2p1,HIGH);
      digitalWrite(r2d1,HIGH);

      // l3 motor run forward
      digitalWrite(l3p1,HIGH);
      digitalWrite(l3d1,HIGH);

      // r2 motor run backward
      digitalWrite(r3p1,HIGH);
      digitalWrite(r3d1,HIGH);
      

      Serial.print("(");
      Serial.print(l1s1c);
      Serial.print(",");
      Serial.print(r1s1c);
      Serial.print(",");
      Serial.println(")");
    }

    Stop();
  }


}



void loop() {
  // put your main code here, to run repeatedly:
  char data = Serial.read();

  if(data == 'w')
  {
    l1s1c = 0;
    
    r1s1c = 0;
    

    moveStraight(350); // to move forward for encoder pulses of 350 because it was calculted that half rotaion gives 350 pulses
  }

  if(data == 's')
  {
    l1s1c = 0;
    
    r1s1c = 0;
   

    moveBack(350); // to move forward for encoder pulses of 350 because it was calculted that half rotaion gives 350 pulses
  } 

  if(data == 'a')
  {
    turn(-30.0);
  }

  if(data == 'd')
  {
    turn(30.0);
  }

}

// ISRS

// ISR of l1 
void l1ISR(){

  l1s1c++; // counting the pulses by incrementing each time for left motor 

}


// ISR of r1 
void r1ISR(){
  
  r1s1c++; // counting the pulses by incrementing each time for Right motor 
  
}





