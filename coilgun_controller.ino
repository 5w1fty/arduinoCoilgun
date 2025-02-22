//Libaries
#include <LiquidCrystal_I2C.h>

//Pinouts
//INPUTS
//Poientimeter for setting the wanted Voltage
#define potVoltagePin A0
//Voltage meassured on capacitor
#define mesVoltagePin A1
//Triggerpin
#define trigger 6
//meassuring
//Lightgate for meassuring muzzle velocity
#define muzzleGate0 25
#define muzzleGate1 26

const float gateLength = 0.1f;
unsigned long entryTime = 0;
unsigned long leftTime = 0;
//OUTPUTS
//Fire
#define firePin 7
//LEDS
#define onLED 8
#define chargingLED 9
#define chargedLED 10
#define fireLED 11
#define chargePin 1

//LCD
#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

//Variables
float setVoltage = 24.0f;
float mesVoltage = 0.0f;

bool charging = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Initialising");
  digitalWrite(onLED, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}

//Function for meassuring muzzle Velocity of the projectile
float mesVel(){
  while(digitalRead(25)==HIGH){
    unsigned long entryTime = millis();
    if(digitalRead(25) == LOW){
      return;
    }
  }

  while(digitalRead(26) == HIGH){
    unsigned long leftTime = millis();
    if(digitalRead(26) == LOW){
      return;
    }
  }
  //Calculating the time spent between both gates by the projectile-tip
  unsigned long travelTime = leftTime - entryTime;
  float deltaT = travelTime;
  float vel = gateLength/deltaT;
  return vel;
}

void fire(){
  digitalWrite(firePin,HIGH);
  }

void charge(){
  while(setVoltage > mesVoltage){
    digitalWrite(chargePin, HIGH);
    lcd.setCursor(1,0);
    lcd.print("Charging");
    
    digitalWrite(chargingLED, HIGH);
    digitalWrite(chargedLED,LOW);
    delay(100);
  }
}