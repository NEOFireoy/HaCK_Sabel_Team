int turns = 0;
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
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  
  digitalWrite(motorPin5, LOW);
  digitalWrite(motorPin6, HIGH);
  
  digitalWrite(motorPin7, LOW);
  digitalWrite(motorPin8, HIGH);

  delay(1);

  return;
}

void rotate_right()
{
  //This code  will turn car right for 2 sec.
    digitalWrite(motorPin1, LOW); // front right
    digitalWrite(motorPin2, HIGH); 
    
    digitalWrite(motorPin3, HIGH); // front left
    digitalWrite(motorPin4, LOW);
    
    digitalWrite(motorPin5, LOW); // back right
    digitalWrite(motorPin6, HIGH); 
    
    digitalWrite(motorPin7, HIGH); // back left
    digitalWrite(motorPin8, LOW);   
    
    delay(2500);

    /*digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);

    digitalWrite(motorPin5, LOW);
    digitalWrite(motorPin6, LOW);
    digitalWrite(motorPin7, LOW);
    digitalWrite(motorPin8, LOW);*/

    turns++;
    
    return;
}

void initial_distance()
{
  String right_dist = String(dist_right());
  String front_right_dist = String(dist_fowr());
  String front_left_dist = String(dist_fowl());
  String left_dist = String(dist_left());

  String vals = right_dist + "s" + front_right_dist + "s" + front_left_dist + "s" + left_dist + "s" + turns;

  Serial.println(vals); // sends all 4 sensor distances to python as one string
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
    delay(10);
    
    return; 
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
    analogWrite(enableA1, 190);
    analogWrite(enableB1, 190);
    analogWrite(enableA2, 190);
    analogWrite(enableB2, 190); 
}

void loop() 
{
  initial_distance();// sends all 4 sensor distances to Serial
  Serial.flush();
     
  if(Serial.available() > 0)
  {
    char cmd = Serial.read();
    
    switch(cmd)
    {
      case 'F':
        move_foward();
        //delay(10);
        //stop_move();
        break;
      case 'R':
        rotate_right();
        break;
      default:
        stop_move();
        //delay(500);
    }

    Serial.end();
    Serial.begin(9600 );
      }
  }
