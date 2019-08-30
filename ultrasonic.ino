int TrigPin = 4;
int EchoPin = 7;  //接收输入的脉冲宽度，

//测试距离，通过串口输出到屏幕上
void init_ultrasonic()
{
    pinMode(TrigPin,OUTPUT);
    pinMode(EchoPin,INPUT); //需要接收回来的时钟宽度，设置为输入状态
}

float get_distance()
{
     float  distance;
     //1.由于需要高脉冲来出发TrigPIN，刚开始我么并不知到TrigPin脚的电平
     //  先拉低，然后拉高。
     digitalWrite(TrigPin,LOW);
     delayMicroseconds(2); //延时2us，给我们的arduino开发板反应时间
     digitalWrite(TrigPin,HIGH); //准备发送
     delayMicroseconds(10);  //发送方波
     digitalWrite(TrigPin,LOW); //拉低电平，准备计算

     distance = float(pulseIn(EchoPin,HIGH)/58.00);
     return distance;
}

void sortData(float *p,int n)
{
    int i,j;
    float temp;

    for(i = 0;i < n - 1;i ++){
       for(j = 0;j < n - i - 1;j ++){
          if(p[j] > p[j + 1]){
               temp = p[j];
               p[j] = p[j + 1];
               p[j+1] = temp;
           }
        }  
    }

    return;
}

float ultrasoni_probe(void)
{
  int i;
  float sum = 0;
  float distances[20];

  for(i = 0;i < 20;i ++){
      distances[i] = get_distance();
     // delay(10);
  }
  
  sortData(distances,20);

  for(i = 1;i < 20 - 1;i ++){
     sum += distances[i];
  }

  return  sum / 18;
}

