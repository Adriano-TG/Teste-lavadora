//ligar no pino 5 do arduino

#include <FreqCount.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup() {
  Serial.begin(57600);
  lcd.begin();
  lcd.backlight();
  
  FreqCount.begin(1000);
}

void loop() {
  lcd.home();
  lcd.setCursor(1, 0);
  lcd.print("Frequencimetro");
  if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    lcd.setCursor(9, 1);
    lcd.print(count);
    lcd.print("Hz");
    if(count>=25900){
      
      lcd.setCursor(0, 1);
      lcd.print("Vazio    ");
    } 
    if(count<=19000){
      
      lcd.setCursor(0, 1);
      lcd.print("Alto     ");
    }
     if(count < 17000){
      
      lcd.setCursor(0, 1);
      lcd.print(" Desconectado   ");
    }
    
    }
 
  }
 
}