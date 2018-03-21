#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F);

int base_dist;
int ave_dist = 0;
unsigned long start_time = 0;

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
  lcd.begin(20, 4); // initialize the lcd
  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  lcd.print("Now initializing....");
  int i = 0;
  while(i<10){
  base_dist = analogRead(0);
  ave_dist += base_dist;
  lcd.setCursor(0, 0);
  lcd.print((6762/(base_dist-9))-4);
  lcd.print("cm");
  delay(100);
  i++;
  }
  ave_dist = ave_dist/10;
  lcd.setCursor(0, 1);
  lcd.print("Ave: ");
  lcd.print((6762/(ave_dist-9))-4);
  lcd.print("cm");

  delay(3000);
  
  lcd.clear();
  if(ave_dist <400){
    lcd.print("Too far. Press reset and try again.");
  }else{
  lcd.print("Ready to go!");
  }
}

void loop()
{
int value = analogRead(0);
  int distance = (6762/(value-9))-4;
  //50cm以下で反応
  //valueがave_distから100変化したら反応
  lcd.setCursor(0, 0);
  if(ave_dist - value >= 100){
    start_time = micros();
    lcd.print(start_time);
    //lcd.print(distance);
    lcd.print(" micro sec");
  lcd.setCursor(0, 4);
    lcd.print(value);
    lcd.print("V");
    delay(1000);
  }
  else{
  //  lcd.print("not found");
  }

delay(50);
}
