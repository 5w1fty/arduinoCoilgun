//Libaries
#include <LiquidCrystal_I2C.h>

//Pinouts
//INPUTS
//Poientimeter for setting the wanted Voltage
#define potVoltagePin A0
//Voltage meassured on capacitor
#define mesVoltagePin A1
//Trigger and arming
#define trigger 6
#define safety 5
bool armed = false;
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
#define armedLED 8
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


void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initialising");
  pinMode(safety, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  charge();
}


void arm(){
  if(digitalRead(safety) == LOW){
    Serial.println("safety is: ON");
    armed = false;
    digitalWrite(armedLED, LOW);
  }else{
    Serial.println("safety is: OFF");
    armed = false;
    digitalWrite(armedLED, HIGH);
    lcd.setCursor(4,0);
    lcd.print("armed="+ armed);
  }
  delay(50);
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
  delay(50);
  }

void charge(){
  arm();
  if(armed == true){

      //initialising the wanted voltage
    setVoltage = analogRead(potVoltagePin);
    int mapPotVoltage = map(setVoltage, 0, 1023,0,400);

    //Initialising the meassured Voltage (to do this in real life use two resistors as a Voltage divider and meassure between 0-5V MAX!)
    //You can calculate the necessary resistances online 
    mesVoltage = analogRead(mesVoltagePin);
    int mapMesVoltage = map(mesVoltage, 0, 1023,0,400);

    //charging the coilgun capasitors as long as the meassured voltage of the capacitors is lower than the wanted voltage
    while(mapPotVoltage >= mapMesVoltage){
      digitalWrite(chargePin, HIGH);
      //Switching LED-States from "Charged" to "Charging"
      digitalWrite(chargingLED, HIGH);
      digitalWrite(chargedLED,LOW);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Charging");
      lcd.setCursor(3,1);
      lcd.print(mapPotVoltage);
      //adjusting the wanted voltage
      setVoltage = analogRead(potVoltagePin);
      mapPotVoltage = map(setVoltage, 0, 1023,0,400);
    
      //adjusting the meassurement
      mesVoltage = analogRead(mesVoltagePin);
      mapMesVoltage = map(mesVoltage, 0, 1023,0,400);
      lcd.setCursor(11,1);
      lcd.print(mapMesVoltage);
      delay(100);
    }

    digitalWrite(chargedLED, HIGH);
    digitalWrite(chargingLED, LOW);
  }
}
