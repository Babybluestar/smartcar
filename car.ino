
//对应的四个电机驱动
int  IN1 = 13;  //右边轮子
int  IN2 = 12;  //右边轮子
int  IN3 = 11;  //左边轮子
int  IN4 = 10;  //左边轮子

int pwmleft  = 5; 
int pwmright = 6;

void set_speed(int speed_value)
{
     analogWrite(pwmleft, speed_value);
     analogWrite(pwmright, speed_value);
}

void int_car_pin() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
}

void leftMotorForward() //左边正转
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftMotorBack() //左边反转
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void rightMotorForward() //右边正转
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void rightMotorBack() //右边发转
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void car_forward()
{
     set_speed(120);
     leftMotorForward();
     rightMotorForward();
     delay(500);
}

void car_back()
{
      set_speed(120);
      leftMotorBack();
      rightMotorBack();
      delay(500);
}

void car_left()
{
      set_speed(150);
      leftMotorBack();
      rightMotorForward();
      delay(500);
      car_forward();
      delay(500);
}

void car_right()
{
      set_speed(150);
      leftMotorForward();
      rightMotorBack();
      delay(500);
      car_forward();
      delay(500);
}

void car_stop()
{
     set_speed(0);
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
     delay(500);
}

void controlCar(int cmd)
{
  switch (cmd) {
    case CMD_FORWARD:
      car_forward();  
      break;

    case CMD_BACK:
      car_back();
      break;

    case  CMD_LEFT:
      car_left();   
      break;

    case CMD_RIGHT:
      car_right();
      break;

    case CMD_STOP:
      car_stop();
      break;
  }
}



