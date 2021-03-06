
const int trig_fowl = 22;
const int echo_fowl = 23;

const int trig_left = 24;
const int echo_left = 25;

const int trig_right = 26;
const int echo_right = 27;

const int trig_fowr = 28;
const int echo_fowr = 29; 

char Incoming_value = 0;


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

  while(dist_travel < 30)
  {
        //move foward code here




        // keep this at the end
        dist_travel = ((dist1+dist2)/2) + ((dist_fowr() + dist_fowl())/2);
        Serial.println(dist_travel);
  }
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
  //all motors turn off
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


    if(cmd == '1')
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
