/*char Incoming_value = 0;    
void setup() 
{ 
    Serial.begin(9600);//Sets the baud rate for serial data       
         //transmission 
}
void loop() 
{
if(Serial.available() > 0) 
  {
    float val = 30.00;
    char cmd = Serial.read(); 
    if (cmd == 's')
    {
      Serial.println(val);
      delay(100);
    }
  }
  
  
}*/


const int trig_fowl = 37;
const int echo_fowl = 36;

const int trig_left = 35;
const int echo_left = 34;

const int trig_right = 45;
const int echo_right = 44;

const int trig_fowr = 47;
const int echo_fowr = 46; 

char Incoming_value = 0;

//enable motors
const int enableA1 = 8;
const int enableB1 = 13;

const int enableA2 = 7;
const int enableB2 = 2;

//Motor A
const int motorPin1  = 12;
const int motorPin2  = 11;
//Motor B
const int motorPin3  = 10;
const int motorPin4  = 9; 

//Motor C
const int motorPin5  = 6;
const int motorPin6  = 5;

//Motor D
const int motorPin7  = 4;
const int motorPin8  = 3;

double dist_right()
{
  digitalWrite(trig_right, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_right, LOW);

  long duration;
  
  duration = pulseIn(echo_right, HIGH);
  double distance = (double)duration * 345 / 2 / 1000000;

  return distance; 
}

double dist_left()
{
  digitalWrite(trig_left, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_left, LOW);

  long duration;
  
  duration = pulseIn(echo_left, HIGH);
  double distance = (double)duration * 345 / 2 / 1000000;

  return distance;
}

double dist_fowl()
{
  digitalWrite(trig_fowl, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig_fowl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_fowl, LOW);

  long duration;
  
  duration = pulseIn(echo_fowl, HIGH);
  double distance = (double)duration * 345 / 2 / 1000000;

  return distance;
}

double dist_fowr()
{
  digitalWrite(trig_fowr, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig_fowr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_fowr, LOW);

  long duration;
  
  duration = pulseIn(echo_fowr, HIGH);
  double distance = (double)duration * 345 / 2 / 1000000;

  return distance;
}

void move_foward()
{
  auto dist1 = dist_fowr();
  auto dist2 = dist_fowl();

  auto dist_travel = ((dist1+dist2)/2) + ((dist_fowr() + dist_fowl())/2);
  
  /*digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  
  digitalWrite(motorPin5, LOW);
  digitalWrite(motorPin6, HIGH);
  digitalWrite(motorPin7, LOW);
  digitalWrite(motorPin8, HIGH);*/
  
 while(dist_travel < 10)
  {
        Serial.print(dist_travel); //move foward code here
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        
        digitalWrite(motorPin5, LOW);
        digitalWrite(motorPin6, HIGH);
        digitalWrite(motorPin7, LOW);
        digitalWrite(motorPin8, HIGH);



        // keep this at the end
        dist_travel = ((dist1+dist2)/2) + ((dist_fowr() + dist_fowl())/2);
        Serial.println(dist_travel);
  }
  stop_move();
}

void rotate_right()
{
  //rotate right by 90deg code here
}

void rotate_left()
{
  //rotate left by 90deg code here
}

void initial_distance()
{
  String right_dist = String(dist_right());
  String front_right_dist = String(dist_fowr());
  String front_left_dist = String(dist_fowl());
  String left_dist = String(dist_left());

  String vals = right_dist + "s" + front_right_dist + "s" + front_left_dist + "s" + left_dist;

  Serial.println(vals);
 // Serial.println(data_send);

}



void stop_move()
{
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);

    digitalWrite(motorPin5, LOW);
    digitalWrite(motorPin6, LOW);
    digitalWrite(motorPin7, LOW);
    digitalWrite(motorPin8, LOW);
}



void setup() 
{ 
  Serial.begin(9600);
  
   pinMode(trig_fowl, OUTPUT);
   pinMode(echo_fowl, INPUT);

   pinMode(trig_left, OUTPUT);
   pinMode(echo_left, INPUT);

   pinMode(trig_right, OUTPUT);
   pinMode(echo_right, INPUT);

   pinMode(trig_fowr, OUTPUT);
   pinMode(echo_fowr, INPUT);

   pinMode(enableA1, OUTPUT);
    pinMode(enableB1, OUTPUT);
    pinMode(enableA2, OUTPUT);
    pinMode(enableB2, OUTPUT);
    
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(motorPin5, OUTPUT);
    pinMode(motorPin6, OUTPUT);
    pinMode(motorPin7, OUTPUT);
    pinMode(motorPin8, OUTPUT);
    
    //enable
    analogWrite(enableA1, 200);
    analogWrite(enableB1, 200);
    analogWrite(enableA2, 200);
    analogWrite(enableB2, 200);
  
    
}

void loop() 
{
  if(Serial.available() > 0)
  {

      initial_distance();
      
      char cmd = Serial.read();


    if(cmd == 'S')
    {
      stop_move();
    }
    else if(cmd == 'F')
    {
      //go foward 30cm 
      move_foward();        
    }
    
  }

  

  

}
