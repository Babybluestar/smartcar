#include <SoftwareSerial.h>

SoftwareSerial  mySerial(8,9);  //定义软串口对象

void init_bluetooh() {
  // put your setup code here, to run once:
  mySerial.begin(115200);  //蓝牙接收串口
}
//前进--0xa
//后退--0xb
//前进--0xc
//后退--0xd
//停止--0x10
int get_bluetooh_data() {
  // put your main code here, to run repeatedly:
  int ch = -1;
 
  mySerial.listen(); //表示监听我们的蓝牙软串口数据
  if(mySerial.available() > 0)
  {
       Serial.println("Recv data : ");
      ch = mySerial.read(); //软串口读出，写到arduino开发板上
  }
  return ch;
}
