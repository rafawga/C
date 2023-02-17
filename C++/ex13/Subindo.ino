#include <LiquidCrystal.h>
LiquidCrystal lcd(19,23,18,17,16,15);


void setup() {
  lcd.begin(16,2);
  lcd.clear();
} 

int i ;
void loop() {

for (i = 1; i>=0 ; i--){
  lcd.clear();
  lcd.setCursor(3,i);
  lcd.print("Subindo");
  delay(225);
}
lcd.clear();
delay(300);
}
