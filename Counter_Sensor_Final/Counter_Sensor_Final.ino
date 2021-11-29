#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte customChar1[] = {
  B00100,
  B11110,
  B10101,
  B11110,
  B10101,
  B11110,
  B00100,
  B00000
};
byte customChar2[] = {
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

int pinSensor1 = 2;
int pinSensor2 = 3;
int pinSensor3 = 4;
int pinSensor4 = 5;
int pinSensor5 = 6;
int pinSensor6 = 7;

int state_pinSensor1 = 0;
int state_pinSensor2 = 0;
int state_pinSensor3 = 0;
int state_pinSensor4 = 0;
int state_pinSensor5 = 0;
int state_pinSensor6 = 0;

int coin1 = 0;
int coin2 = 0;
int coin3 = 0;
int coin4 = 0;
int coin5 = 0;
int coin6 = 0;
float total = 0;

int oneClick_1 = 0; //ถ้าเซนเซอร์มีค่าเป็น 1 จะให้เซนเซอร์ทำการนับแค่ครั้งเดียว
int oneClick_2 = 0;
int oneClick_3 = 0;
int oneClick_4 = 0;
int oneClick_5 = 0;
int oneClick_6 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinSensor1,INPUT);
  pinMode(pinSensor2,INPUT);
  pinMode(pinSensor3,INPUT);
  pinMode(pinSensor4,INPUT);
  pinMode(pinSensor5,INPUT);
  pinMode(pinSensor6,INPUT);

  lcd.begin();
  lcd.setCursor(2,1);
  lcd.print("Hello to Project");
  lcd.setCursor(0,2);
  lcd.print("Coin Counter Machine");
  delay(2000);
  lcd.clear();
  
  lcd.createChar(0, customChar1);
  lcd.createChar(1, customChar2);
  lcd.home();
  
}

void loop(){
  state_pinSensor1 = digitalRead(pinSensor1);
  state_pinSensor2 = digitalRead(pinSensor2);
  state_pinSensor3 = digitalRead(pinSensor3);
  state_pinSensor4 = digitalRead(pinSensor4);
  state_pinSensor5 = digitalRead(pinSensor5);
  state_pinSensor6 = digitalRead(pinSensor6);
  
  if(state_pinSensor1 == 1){
    if(oneClick_1 == 0){
      oneClick_1 = 1;
      coin1++;
    }
  }
  else if(state_pinSensor1 == 0){
    oneClick_1 = 0;
  }

  if(state_pinSensor2 == 1){
    if(oneClick_2 == 0){
      oneClick_2 = 1;
      coin2++;
    }
  }
  else if(state_pinSensor2 == 0){
    oneClick_2 = 0;
  }

  if(state_pinSensor3 == 1){
    if(oneClick_3 == 0){
      oneClick_3 = 1;
      coin3++;
    }
  }
  else if(state_pinSensor3 == 0){
    oneClick_3 = 0;
  }

  if(state_pinSensor4 == 1){
    if(oneClick_4 == 0){
      oneClick_4 = 1;
      coin4++;
    }
  }
  else if(state_pinSensor4 == 0){
    oneClick_4 = 0;
  }

  if(state_pinSensor5 == 1){
    if(oneClick_5 == 0){
      oneClick_5 = 1;
      coin5++;
    }
  }
  else if(state_pinSensor5 == 0){
    oneClick_5 = 0;
  }

  if(state_pinSensor6 == 1){
    if(oneClick_6 == 0){
      oneClick_6 = 1;
      coin6++;
    }
  }
  else if(state_pinSensor6 == 0){
    oneClick_6 = 0;
  }
  total = (coin1*0.25)+(coin2*0.50)+(coin3*1)+(coin4*2)+(coin5*5)+(coin6*10);

  lcd.setCursor(0,0);
  lcd.print(".25");
  lcd.write(0);
  lcd.print(" :");
  lcd.print(coin1);

  lcd.setCursor(10,0);
  lcd.print(".50");
  lcd.write(0);
  lcd.print(" :");
  lcd.print(coin2);

  lcd.setCursor(9,0);
  lcd.write(1);
  
  lcd.setCursor(2,1);
  lcd.print("1");
  lcd.write(0);
  lcd.print(" :");
  lcd.print(coin3);

  lcd.setCursor(12,1);
  lcd.print("2");
  lcd.write(0);
  lcd.print(" :");
  lcd.print(coin4);

  lcd.setCursor(9,1);
  lcd.write(1);
  
  lcd.setCursor(2,2);
  lcd.print("5");
  lcd.write(0);
  lcd.print(" :");
  lcd.print(coin5);

  lcd.setCursor(11,2);
  lcd.print("10");
  lcd.write(0);
  lcd.print(" :");
  lcd.print(coin6);

  lcd.setCursor(9,2);
  lcd.write(1);

  lcd.setCursor(0,3);
  lcd.print("Total");
  lcd.print(" :");
  lcd.print(total);
  lcd.write(0);

}
