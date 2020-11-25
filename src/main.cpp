//ligar no pino 5 do arduino

#include <FreqCount.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

const byte LINHAS = 4;
const byte COLUNAS = 4;

char teclas[LINHAS][COLUNAS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte PinsFilas[LINHAS] = {0,1,2,3}; 
byte PinsColumnas[COLUNAS] = {4,5,6,7};

int i2caddress = 0x20;

Keypad_I2C kpd = Keypad_I2C( makeKeymap(teclas), PinsFilas, PinsColumnas, LINHAS, COLUNAS, i2caddress );

int val1=7, val2=10, bom=11, mho=12, mah=8,ta=500, it=200;
byte atiu[8] = { B01110,
                 B00000,
                 B01110,
                 B00001,
                 B01111,
                 B10001,
                 B01111,
                 B00000,

               };
byte dilha[8] = {B00000, //
                 B00000,
                 B01110,
                 B10000,
                 B10000,
                 B10001,
                 B01110,
                 B00100,
                };

void testeteclado()
{
  char tecla = kpd.getKey();  
  if (tecla)
  {
    lcd.print(tecla);
  }
  if(tecla =='A'){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Menu Principal");
  
  }
   if(tecla =='#'){
  lcd.clear();
   }
}

void frequcimetro(){
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print(" Frequencimetro ");
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
void auto_teste(){
  lcd.home();
  lcd.setCursor(1, 0);
  lcd.print("  Auto Teste  ");
  delay(5000);
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("   Val. Sab");
  lcd.write((byte)1);
  lcd.print("o");

 digitalWrite(val1,0);
 delay(20000);
 digitalWrite(val1,1);
 lcd.home();
  lcd.setCursor(0, 0);
  lcd.print(" Val. Amaciante");
 digitalWrite(val2,0);
 delay(20000);
 digitalWrite(val2,1);
 //Agitacao
 lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("    Agita");
  lcd.write((byte)2);
  lcd.write((byte)1);
  lcd.print("o    ");
 for (int i =0; i<20; i++){
   digitalWrite(mah,0);
   delay(ta);
   digitalWrite(mah,1);
   delay(it);
   digitalWrite(mho,0);
   delay(ta);
   digitalWrite(mho,1);
   delay(it);
 }
 delay(5000);
 //Centrifugacao
 lcd.home();
  lcd.setCursor(0, 0);
  lcd.print(" Centrifuga");
  lcd.write((byte)2);
  lcd.write((byte)1);
  lcd.print("o");
 digitalWrite(bom,0);
 delay(20000);
 digitalWrite(mho,0);
 delay(5000);
 digitalWrite(mho,1);
 delay(5000);
 digitalWrite(mho,0);
 delay(10000);
 digitalWrite(mho,1);
 delay(10000);
 digitalWrite(bom,1);
 lcd.setCursor(0, 0);
 lcd.print("Teste Finalizado");
 delay(5000);

}

void setup() {
  Serial.begin(57600);
  lcd.begin();
  kpd.begin();
  lcd.backlight();
  pinMode(val1,OUTPUT);
  pinMode(val2,OUTPUT);
  pinMode(bom,OUTPUT);
  pinMode(mho,OUTPUT);
  pinMode(mah,OUTPUT);
  digitalWrite(val1,1);
  digitalWrite(val2,1);
  digitalWrite(bom,1);
  digitalWrite(mho,1);
  digitalWrite(mah,1);
  lcd.createChar(1, atiu);
  lcd.createChar(2, dilha);
  
  FreqCount.begin(1000);
}

void loop() {
testeteclado();
/*for (int i =0; i<1000; i++){
frequcimetro();
}
lcd.setCursor(0, 1);
lcd.print("                ");
for (int i =0; i<1; i++)
auto_teste(); */

}

