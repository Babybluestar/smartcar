#define CMD_FORWARD 0xa
#define CMD_BACK    0xb
#define CMD_LEFT    0xc
#define CMD_RIGHT   0xd
#define CMD_FUN     0xf
#define CMD_STOP    0x10
#define CMD_FOLLOW  0xe

#define  FUN_MODE      2
#define  FOLLOW_MODE   3 

int carMode = -1;

int  change_mode(int cmd)
{
      switch (cmd) {
        case CMD_FUN:
          beep_start();
          carMode =  FUN_MODE;  //娱乐模式
          break;
        case CMD_FOLLOW:
          beep_start();
          carMode =  FOLLOW_MODE; //自动跟随模式
          break;
    
        default:
          return 0;
  }

  return 1;
  
}

void choiceMode()
{
     int i;
     int cmd = -1;
again:
     cmd = -1;
     do{
        for(i = 0;i < 1000 && cmd == -1;i++){
            cmd = get_bluetooh_data();
        } 
     }while(cmd == -1);
 
    //判断用户输出的模式是否正确，若是错误。则重新输入
     if(change_mode(cmd) == 0){   
      beep_start();
      beep_start();
      delay(10);
      goto  again;
     }
     return ;
}

void setup()
{
    Serial.begin(115200);
    init_bluetooh();//初始化蓝牙设备
    init_ultrasonic(); //初始化超声波
    int_car_pin(); //初始化小车引脚
    beep_init();
    choiceMode();
    
}

void carFunMode(){
      int cmd = -1;
   // Serial.println("enter funmode");
      cmd = get_bluetooh_data();
      if(cmd == -1)
      { 
          //  Serial.println("input is error!");
            return ; 
      }

      if(change_mode(cmd) == 0) //表示用户没有改变模式，输入的是上下左右指令
      {
           controlCar(cmd);
       }else{
           cmd = CMD_STOP;
           controlCar(cmd);
       }
       return ;
}

void carFollowMode(){
    int cmd;
    float distance;

    cmd = get_bluetooh_data();
    if(cmd != -1 && change_mode(cmd) != 0) //说明用户想要切换到其他模式下，结束当前模式。
    {
        cmd = CMD_STOP;
        controlCar(cmd);
        return ;  
    }

    distance = ultrasoni_probe();
//     Serial.print(distance);
//     Serial.print("cm");
//     Serial.println();
    if (distance < 25 && distance > 15) {
      controlCar(CMD_STOP);
    } else if (distance >= 25) {
      controlCar(CMD_FORWARD);
    } else {
      controlCar(CMD_BACK);
    }
    delay(500);

    return ;
}

void loop(){
     switch(carMode){
      case  FUN_MODE:
          carFunMode();
          break;
      case  FOLLOW_MODE:
          carFollowMode();
          break;
      default:
          return 0;
     }
  
}

