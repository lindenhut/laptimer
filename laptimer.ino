#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);


int base_dist;
int ave_dist = 0;
int lap = 0;
float start_time = 0;
float lap_now=0, lap_1=0, lap_2=0 ;
float avetime = 0.0;
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
  lcd.print("Now initializing...");
  
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
  if(ave_dist <200){
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
int value = analogRead(0);
  lcd.setCursor(0, 0);
  start_time = millis()/1000.0;
  lcd.print("LAP:");
  lcd.print(lap);
  lcd.print("> ");
  lcd.print(start_time - last_time);
  if(value - ave_dist >= 50){
    start_time = millis()/1000.0;
    lap_2 = lap_1;
    lap_1 = lap_now;
    lap_now = start_time - last_time;
    lcd.setCursor(10, 1);
    lcd.print("L1> ");
    lcd.print(lap_now);
    lcd.setCursor(10, 2);
    lcd.print("L2> ");
    lcd.print(lap_1);
    lcd.setCursor(10, 3);
    lcd.print("L3> ");
    lcd.print(lap_2);
    last_time = start_time;

    lcd.setCursor(0, 2);
    lcd.print("ave/time");
    lcd.setCursor(0, 3);
    iF(lap > 1){
      avetime = (avetime* (lap -1 ) + lap_now )/ lap;
      lcd.print(avetime);
    }
    lap ++;
    delay(1000);
  }
  else{
  //  lcd.print("not found");
  }
//  lcd.setCursor(4, 3);
//  lcd.print(dtostrf(value/5*1024, 5, 2, s));
//  lcd.print(value);
delay(10);
}
