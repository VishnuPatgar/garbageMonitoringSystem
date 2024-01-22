#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
#define echoPin 2
#define trigPin 3 
long duration; 
int distance;
#include <HX711_ADC.h>
#include <Wire.h>
HX711_ADC LoadCell(6, 7); // dt pin, sck pin
int a = 0;
float b = 0;
int IRSensor = 4;
int ReedSwich = 5; 
int val;
int BUZZER = 1;
int LEDoutput = 0;

void setup() 
{
lcd.begin(16, 2);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
LoadCell.begin(); 
LoadCell.start(1000); // 1000ms of time to stabilize
LoadCell.setCalFactor(375); 
pinMode (IRSensor, INPUT); 
pinMode (ReedSwich, INPUT);
pinMode (BUZZER, OUTPUT);
pinMode (LEDoutput, OUTPUT);
lcd.setCursor(0,0);
lcd.print("SMART GARBAGE");
lcd.setCursor(0,1);
lcd.print("MONITORING S/M");
delay(5000);
lcd.clear();
}

void loop() 
{
digitalWrite (BUZZER, LOW);// LOW
digitalWrite (LEDoutput, LOW);// LOW 
LoadCell.update(); // Fetches data from the load cell
float i = LoadCell.getData(); // output 
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2; 
if(distance>=10.1 && distance<=12)
{
lcd.setCursor(0, 0);
lcd.print("STORAGE=00%");
lcd.setCursor(1, 1);
lcd.print(i, 1); 
lcd.print("g ");
delay(100); 
}
if(distance>=8.1 && distance<=10)
{
lcd.setCursor(0, 0);
lcd.print("STORAGE=05%");
lcd.setCursor(1, 1);
lcd.print(i, 1); 
lcd.print("g ");
delay(100);  
}
if(distance>=6.1 && distance<=8)
{
lcd.setCursor(0, 0);
lcd.print("STORAGE=20%");
lcd.setCursor(1, 1);
lcd.print(i, 1); 
lcd.print("g ");
delay(100);  
}
if(distance>=5.1 && distance<=6)
{
lcd.setCursor(0, 0);
lcd.print("STORAGE=40%");
lcd.setCursor(1, 1);
lcd.print(i, 1); 
lcd.print("g ");
delay(100);   
}
if(distance>=4.1 && distance<=5)
{
lcd.setCursor(0, 0);
lcd.print("STORAGE=60%");
lcd.setCursor(1, 1);
lcd.print(i, 1); 
lcd.print("g ");
delay(100);  
}
if(distance>=3.1 && distance<=4)
{
lcd.setCursor(0, 0);
lcd.print("STORAGE=80%");
lcd.setCursor(1, 1);
lcd.print(i, 1); 
lcd.print("g ");
delay(100);  
}
if(distance>=2.1 && distance<=3)
{
lcd.setCursor(0, 0);
lcd.print("STORAGE=90%");
lcd.setCursor(1, 1);
lcd.print(i, 1); 
lcd.print("g ");
delay(100);   
}
if (i>=100)
{
i=0;
lcd.setCursor(7, 1); 
lcd.print(" OVER L/D");
delay(1000);
lcd.clear(); 
}
int statusSensor = digitalRead (IRSensor);
if (statusSensor == LOW)
{
digitalWrite(BUZZER, HIGH); // HIGH
digitalWrite(LEDoutput, HIGH); // HIGH
delay(400);
}
else
{
digitalWrite(BUZZER, LOW); // LOW 
digitalWrite(LEDoutput, LOW); // LOW   
}
val = digitalRead (ReedSwich);
if (val == HIGH) 
{
digitalWrite (BUZZER, HIGH);// HIGH
delay(150);
digitalWrite (BUZZER, LOW);// LOW
delay(100);
digitalWrite (BUZZER, HIGH);// HIGH
delay(150);
}
else
{
digitalWrite (BUZZER, LOW);// LOW 
}
}
