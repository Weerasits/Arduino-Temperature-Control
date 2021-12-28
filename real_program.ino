int ThermistorPin = 0; // กำหนดขาของ Thremistor เป็น Pin ที่ 0
int Vo; // สร้างตัวแปร VO
float R1 = 10000; // ประกาศตัวแปร R1 = 10000
float logR2, R2, T; // สร้างตัวแปร
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; // ประกาศตัวแปรเพื่อใช้คำนวณอุณหภูมิ
int buzzer = 9; // ประกาศตัวแปร buzzer ใน Digital Pin ที่ 9
int relay = 8; // ประกาศตัวปผร relay ใน Digital Pin ที่ 8
#include <Wire.h> // ใช้งาน Library Wire.h
#include <LiquidCrystal_I2C.h> // ใช้งาน Library LiquidCrystal_I2C.h
LiquidCrystal_I2C lcd(0x27,20,4);  // จอกว้าง 16 ตัวอักษร 2 บรรทัด รหัสประจำตัว 0x27
void setup() {
Serial.begin(9600); // ใช้งาน Serial monitor 
pinMode(relay,OUTPUT); // ประกาศ relay เป็น Output
pinMode(buzzer,OUTPUT); // ประกาศ buzzer เป็น Output
  lcd.init(); // เริ่มต้นใน lcd        
  lcd.backlight(); //
  lcd.setCursor(0,0);
  lcd.print("TempSensorProject");
  lcd.setCursor(0,1);
  lcd.print("Version 1.53.975");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Oil-Temperature");
  lcd.setCursor(2,1);
  lcd.print(T);
  lcd.setCursor(8,1);
  lcd.print("Celsius");  
}
void loop() {
  delay(500);
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  //T = (T * 9.0)/ 5.0 + 32.0; 
  
  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" C");
  lcd.setCursor(2,1);
  lcd.print(T);
  lcd.setCursor(8,1);
  lcd.print("Celsius"); 
  delay(500);
  if(T< อุณหภูมิที่ต้องการให้heaterทำงาน){ // ถ้าอุณหภุมิตํ่า
    shogunbuzzer(); // เปิด buzzer
    digitalWrite(relay,LOW); // เปิดheater
    Serial.println("LOW TEMP!");
    delay(500);
  }else{
    digitalWrite(relay,HIGH); // ปิด heater
  }

  // LCD PART
  if(T< อุณหภูมิที่ต้องการให้heaterทำงาน){
    lcd.setCursor(0,0);
    lcd.print("    ");
    lcd.setCursor(1,0);
    lcd.print("Oil-Temperature");
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Status : Heating!");
    delay(500);
  }else{
    lcd.setCursor(0,0);
    lcd.print("    ");
    lcd.setCursor(1,0);
    lcd.print("Oil-Temperature");
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(1,0);
    lcd.print("Status : Normal");
    delay(500);
  }
}
void shogunbuzzer(){
  tone(2,2000);
  delay(1000);
  noTone(2);
  delay(200);
}
