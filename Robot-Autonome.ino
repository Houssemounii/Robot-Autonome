#define servo_pence    3
#define servo_coude    5
#define servo_poignet  6
#define servo_rotation 9
#define IN1 7
#define IN2 8
#define IN3 12
#define IN4 A0
#define moteur_speed_ch_1 10 
#define moteur_speed_ch_2 11
#define Triger            2
#define echo              4



const byte pence_max=71;
const byte pence_min=50;

const byte coud_max=118;
const byte coud_min=30;

const byte poignet_max=173;
const byte poignet_min=70;

const byte rotation_max=170;
const byte rotation_min=30;
const byte rotation_centre=128;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++define part/*/

typedef enum{
   avant=0,
   arrier=1
}state;

typedef enum {
  ch1=moteur_speed_ch_1,
  ch2=moteur_speed_ch_2
}channel;

struct motor {
  state Sense;
  channel channels;
  byte Speed;
};

 
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++//struct part
#include <Servo.h>

Servo servoPence; 
Servo servoCoude;
Servo servoPoignet;
Servo servoRotation;




motor M1;
 motor M2;
void setup()
{
 Serial.begin(9600);
 M1.channels=ch1;
 M2.channels=ch2;
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 pinMode(Triger,OUTPUT);
 pinMode(echo,INPUT);
 
 digitalWrite(Triger, LOW);
 
 servoPence.attach(servo_pence);
 servoCoude.attach(servo_coude);
 servoPoignet.attach(servo_poignet);
 servoRotation.attach(servo_rotation);
 init_servo();
 delay(500);
     //Catch();
rotate_left();
 //Catch();
}


void loop()
{
  
 if (distance()<10)
  {
    Stop();
    Catch();
  }

  
  engine(&M1);
  engine(&M2);
  
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  long distance (void)
  {
    long lecture_echo;
    long cm;
    
  digitalWrite(Triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Triger, LOW);
  lecture_echo = pulseIn(echo,HIGH);
  cm = lecture_echo /58;
  
  Serial.println(cm);
  return cm;
  
  }
  
  void Catch(void)
  {
  
    for(byte q=31; q<128;q++)
    {Rotation(q);delay(25);}
    
    Pence(50);
    for(byte q=160; q>80;q--)
    {Poignet(q);delay(25);}
    
    for(byte q=31; q<115;q++)
    {Coude(q);delay(25);}
   
    
    for(byte q=80; q<120;q++)
    {Poignet(q);delay(35);}

    Pence(70);
   
     for(byte q=115; q>31;q--)
    {Coude(q);delay(25);}

     for(byte q=120; q < 173;q++)
    {Poignet(q);delay(35);}
   
    for(byte q=128; q>31;q--)
    {Rotation(q);delay(25);}
    
    delay(500);
    Pence(50);
    
    
    }
    

  


//-------------------------------------------------------------------------------------fonction
void init_servo(void)
{
Coude(31);
Poignet(160);
Rotation(31);
Pence(70);
}
 void Coude(byte x)
 {
  if (x <= coud_max && x >= coud_min)
        servoCoude.write(x);
 }

 void Poignet(byte x)
 {
  if (x <= poignet_max && x >= poignet_min)
      servoPoignet.write(x);
 }

 void Rotation(byte x)
 {
  if (x <= rotation_max && x >= rotation_min)
      servoRotation.write(x);
      
 }

 void Pence(byte x)
 {
  if (x <= pence_max && x >= pence_min)
      servoPence.write(x);
      
 }

//-------------------------------------------------------------------------------------fonction

void direction_(byte dir)
{
  if(dir)
{
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
}
else
{
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,1);
}
}
  void Stop(void)
 {
  M1.Sense=avant;
  M2.Sense=avant;
   digitalWrite(IN1,0);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,0);
  M1.Speed=0;
  M2.Speed=0;
 }
 
 void forward(void)
 {
  M1.Sense=avant;
  M2.Sense=avant;
  M1.Speed=150;
  M2.Speed=150;
 }

  void backward(void)
 {
  M1.Sense=arrier;
  M2.Sense=arrier;
  M1.Speed=150;
  M2.Speed=150;
 }

 
 void turn_right(void)
  {
    M1.Sense=avant;
    M1.Speed=150;
    
    M2.Sense=avant;
    M2.Speed=150;
    
  }

  void turn_left(void)
  {
    M1.Sense=avant;
    M1.Speed=50;
    
    M2.Sense=avant;
    M2.Speed=150;
  }
  void rotate_left(void)
  {
    M1.Sense=avant;
    M1.Speed=90;
    
    M2.Sense=arrier;
    M2.Speed=90;
  }
  
  void rotate_right(void)
  {
      M1.Sense=arrier;
      M1.Speed=150;
    
      M2.Sense=avant;
      M2.Speed=150;
  }
void engine(motor* X)
{ 
  direction_(X->Sense);
  analogWrite(X->channels,X->Speed);
  
}
