#define ON 1
#define OFF 0

#define Left_Speed 255
#define Right_Speed 255

#define Left_motor_A 4
#define Left_motor_B 5

#define Right_motor_A 1 
#define Right_motor_B 2

#define Left_motor_Speed  6
#define Right_motor_Speed 3

#define IR_1 A0
#define IR_2 A1
#define IR_3 A2
#define IR_4 A3

#define UltraSonic_Forward_Trig 7
#define UltraSonic_Forward_Echo 8

#define UltraSonic_Backward_Trig 11
#define UltraSonic_Backward_Echo 12

#define UltraSonic_Left_Trig A4
#define UltraSonic_Left_Echo A5

#define UltraSonic_Right_Trig 9
#define UltraSonic_Right_Echo 10


#define Search_speed  127
#define Attack_speed  255
int state = 1;
float Forward_Distance = 0; 
float Backward_Distance = 0;
float Left_Distance = 0;
float Right_Distance = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Left_motor_A,OUTPUT);
  pinMode(Left_motor_B,OUTPUT);
  pinMode(Right_motor_A,OUTPUT);
  pinMode(Right_motor_B,OUTPUT);
  
  analogWrite(Left_motor_Speed,Left_Speed);
  analogWrite(Right_motor_Speed,Right_Speed);

  pinMode(IR_1,INPUT);
  pinMode(IR_2,INPUT);
  pinMode(IR_3,INPUT);
  pinMode(IR_4,INPUT);

  pinMode(UltraSonic_Forward_Trig,OUTPUT);
  pinMode(UltraSonic_Forward_Echo,INPUT);
  
  pinMode(UltraSonic_Backward_Trig,OUTPUT);
  pinMode(UltraSonic_Backward_Echo,INPUT);
  
  pinMode(UltraSonic_Left_Trig,OUTPUT);
  pinMode(UltraSonic_Left_Echo,INPUT);
  
  pinMode(UltraSonic_Right_Trig,OUTPUT);
  pinMode(UltraSonic_Right_Echo,INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  Forward();
}
void Forward() {
  digitalWrite(Left_motor_A,ON);
  digitalWrite(Left_motor_B,OFF);
  digitalWrite(Right_motor_A,ON);
  digitalWrite(Right_motor_B,OFF);
}
void Backward() {
  digitalWrite(Left_motor_A,OFF);
  digitalWrite(Left_motor_B,ON);
  digitalWrite(Right_motor_A,OFF);
  digitalWrite(Right_motor_B,ON);
}
void Left() {
  digitalWrite(Left_motor_A,OFF);
  digitalWrite(Left_motor_B,ON);
  digitalWrite(Right_motor_A,ON);
  digitalWrite(Right_motor_B,OFF);
}
void Right() {
  digitalWrite(Left_motor_A,ON);
  digitalWrite(Left_motor_B,OFF);
  digitalWrite(Right_motor_A,OFF);
  digitalWrite(Right_motor_B,ON);
}
void Stop() {
  digitalWrite(Left_motor_A,OFF);
  digitalWrite(Left_motor_B,OFF);
  digitalWrite(Right_motor_A,OFF);
  digitalWrite(Right_motor_B,OFF);
}


void UltraSonic_Forward() {
  digitalWrite(UltraSonic_Forward_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonic_Forward_Trig, LOW);
  float Time = pulseIn(UltraSonic_Forward_Echo, HIGH);
  Forward_Distance = 0.034 * (Time) / 2;  
}
void UltraSonic_Backward() {
  digitalWrite(UltraSonic_Backward_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonic_Backward_Trig, LOW);
  float Time = pulseIn(UltraSonic_Backward_Echo, HIGH);
  Backward_Distance = 0.034 * (Time) / 2;  
}
void UltraSonic_Left() {
  digitalWrite(UltraSonic_Left_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonic_Left_Trig, LOW);
  float Time = pulseIn(UltraSonic_Left_Echo, HIGH);
  Left_Distance = 0.034 * (Time) / 2;  
}
void UltraSonic_Right() {
  digitalWrite(UltraSonic_Right_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonic_Right_Trig, LOW);
  float Time = pulseIn(UltraSonic_Right_Echo, HIGH);
  Right_Distance = 0.034 * (Time) / 2;  
}
void set_speed(int Speed){
    analogWrite(Left_motor_Speed,Speed);
    analogWrite(Right_motor_Speed,Speed);
}
void Sumo_Robot() {
  bool IR_1_Read=!digitalRead(IR_1);
  bool IR_2_Read=!digitalRead(IR_2);
  bool IR_3_Read=!digitalRead(IR_3);
  bool IR_4_Read=!digitalRead(IR_4);

  //1
  if ( !IR_1_Read && IR_2_Read && IR_3_Read && IR_4_Read )
  {
    set_speed(Attack_speed);
    Backward();
    //state = 2;
  }
  //2
  else if ( IR_1_Read && !IR_2_Read && IR_3_Read && IR_4_Read )
  {
    set_speed(Attack_speed);
    Backward();
    //state = 2;
  }
  //3
  else if ( IR_1_Read && IR_2_Read && !IR_3_Read && IR_4_Read )
  {
    set_speed(Attack_speed);
    Forward();
    //state = 1;
  }
  //4
  else if ( IR_1_Read && IR_2_Read && IR_3_Read && !IR_4_Read )
  {
    set_speed(Attack_speed);
    Forward();
    //state = 1;
  }
  //1,2
  else if ( !IR_1_Read && !IR_2_Read && IR_3_Read && IR_4_Read )
  {
    set_speed(Attack_speed);
    Backward();
    //state = 2;
  }
  //3,4
  else if ( IR_1_Read && IR_2_Read && !IR_3_Read && !IR_4_Read )
  {
    set_speed(Attack_speed);
    Forward();
    //state = 1;
  }
  //2,3 ULTRA Sonic
  else if ( IR_1_Read && !IR_2_Read && !IR_3_Read && IR_4_Read ) 
  {
    UltraSonic_Left();
    UltraSonic_Right();
    set_speed(Attack_speed);
    if(Left_Distance>=Right_Distance)
    {
      Left();
      Forward();
      //state = 1;
    }
    else
    {
      Right();
      Backward();
      //state = 2;
    }
  }
  //1,4 ULTRA Sonic
  else if ( !IR_1_Read && IR_2_Read && IR_3_Read && !IR_4_Read )
  {
    UltraSonic_Left();
    UltraSonic_Right();
    set_speed(Attack_speed);
    if(Right_Distance>=Left_Distance)
    {
      Right();
      Forward();
      //state = 1;
    }
    else
    {
      Left();
      Backward();
      state = 2;
    }
  }
  //1,2,3
  else if ( !IR_1_Read && !IR_2_Read && !IR_3_Read && IR_4_Read )
  {
    set_speed(Attack_speed);
    Left();
    Backward();
    //state = 2;
  }
  //1,2,4
  else if ( !IR_1_Read && !IR_2_Read && IR_3_Read && !IR_4_Read )
  {
    set_speed(Attack_speed);
    Right();
    Backward();
    //state = 2;
  }
  //1,4,3
  else if ( !IR_1_Read && IR_2_Read && !IR_3_Read && !IR_4_Read )
  {
    set_speed(Attack_speed);
    Right();
    Forward();
    //state = 1;
  }
  //2,4,3
  else if ( IR_1_Read && !IR_2_Read && !IR_3_Read && !IR_4_Read )
  {
    set_speed(Attack_speed);
    Left();
    Forward();
    //state = 1;
  }
  //OUTSIDE RING
  else if( !IR_1_Read && !IR_2_Read && !IR_3_Read && !IR_4_Read)
  {
    Stop();
  }
  //INSIDE RING ULTRA Sonic
  else if(IR_1_Read && IR_2_Read && IR_3_Read && IR_4_Read)
  {
    //if ( state = 1 ){
     // Forward();
    //}
    //else if( state = 2 ){
      //Backward();
    //}
    set_speed(Search_speed);
    UltraSonic_Forward();
    UltraSonic_Backward();
    UltraSonic_Left();
    UltraSonic_Right();
    if(Forward_Distance<=Backward_Distance && Forward_Distance<=Left_Distance && Forward_Distance<=Right_Distance)
    {
      set_speed(Attack_speed);
      Forward();
    }
    else if(Backward_Distance<=Forward_Distance && Backward_Distance<=Left_Distance && Backward_Distance<=Right_Distance)
    {
      set_speed(Attack_speed);
      Backward();
      
    }
    else if(Left_Distance<=Forward_Distance&&Left_Distance<=Backward_Distance&&Left_Distance<=Right_Distance)
    {
      set_speed(Attack_speed);
      Left();
      Forward();
      
    }
    else if(Right_Distance<=Forward_Distance&&Right_Distance<=Backward_Distance&&Right_Distance<=Left_Distance)
    {
      set_speed(Attack_speed);
      Right();
      Forward();
      
    }
    else
    {
      set_speed(Search_speed);
      Forward();
    }
    
  }
    
  
}