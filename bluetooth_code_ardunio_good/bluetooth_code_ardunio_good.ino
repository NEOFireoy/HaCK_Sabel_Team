
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


const int trig_fowl = 22;
const int echo_fowl = 23;

const int trig_left = 24;
const int echo_left = 25;

const int trig_right = 26;
const int echo_right = 27;

const int trig_fowr = 28;
const int echo_fowr = 29; 

char in_value = 0;


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

 //move foward code here
  
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
  double right_dist = dist_right();
  double front_right_dist = dist_fowr();
  double front_left_dist = dist_fowl();
  double left_dist = dist_left();

  Serial.println(right_dist);
  delay(1);
  Serial.println(front_right_dist);
  delay(1);
  Serial.println(front_left_dist);
  delay(1);
  Serial.println(left_dist);
  delay(1);
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

  
    
}

void loop() 
{
  if(Serial.available() > 0)
  {
  
      initial_distance();
    
      char cmd = Serial.read();

      if(cmd == 'F')
      {
        //go foward 30cm 
        move_foward();

        //get distance
        double right_dist = dist_right();
        double front_right_dist = dist_fowr();
        double front_left_dist = dist_fowl();
        double left_dist = dist_left();

        Serial.println(right_dist);
        delay(1);
        Serial.println(front_right_dist);
        delay(1);
        Serial.println(front_left_dist);
        delay(1);
        Serial.println(left_dist);
        delay(1);
 
        
      }




    
  }

  

  

}
