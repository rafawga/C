#include <LiquidCrystal.h>
LiquidCrystal lcd(19,23,18,17,16,15);
void setup() {
  pinMode(32,INPUT);
  lcd.begin(16,2);
  lcd.clear();
}
int a;
int n = 0;

void loop() {
a = digitalRead(32);
Serial.println(a);
if (a==1){
  lcd.clear();
  lcd.setCursor(8,0);
  lcd.print(n);
  
   if (n<10){
  n++;
   }
   else if (n==10){
    n = 0;
    
    }
   delay(225); 
  }
}
