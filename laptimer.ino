#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);


int base_dist;
int ave_dist = 0;
int lap = 0;
float start_time = 0;
char s[16];
void setup()
{
  int error;
  Serial.begin(115200);
  Serial.println("LCD...");
  while (! Serial);
  Serial.println("Dose: check for LCD");

  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
  } else {
    Serial.println(": LCD not found. Hello LCD");
  }
  lcd.begin(20, 4);
  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  lcd.print("Now initializing....");
  
  int i = 0;
  while(i<10){
  base_dist = analogRead(0);
  ave_dist += base_dist;
  lcd.setCursor(0, 2);
  lcd.print((6762/(base_dist-9))-4);
  lcd.print("cm");
  delay(100);
  i++;
  }
  ave_dist = ave_dist/10;
  lcd.setCursor(0, 3);
  lcd.print("Ave: ");
  lcd.print((6762/(ave_dist-9))-4);
  lcd.print("cm");


  
  lcd.home();
  if(ave_dist <400){
    lcd.print("Failed to init. Please reset.");
  }else{
    lcd.print("Ready to go!       ");
  }
delay(3000);
lcd.clear();
}

float last_time = 0.0;
void loop()
{
float value = analogRead(0);
  lcd.setCursor(10, 1);
  start_time = millis()/1000.0;
  lcd.print("L");
  lcd.print(lap);
  lcd.print("> ");
  lcd.print(start_time);
  if(ave_dist - value >= 50){
    start_time = millis()/1000.0;
    lcd.setCursor(10, 2);
    lcd.print("L");
    lcd.print(lap);
    lcd.print("> ");
    lcd.print(start_time - last_time);
    lap ++;
    last_time = start_time;
    delay(1000);
  }
  else{
  //  lcd.print("not found");
  }
  lcd.setCursor(0, 4);
//  lcd.print(dtostrf(value*5/1024, 5, 2, s));
  lcd.print(value);
  lcd.print("V");
delay(50);
}
