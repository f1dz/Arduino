#include <LiquidCrystal_I2C.h>
#include <Timer.h>
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#define BUS1 7

OneWire oneWire(BUS1);
DallasTemperature sensor(&oneWire);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Timer t;
word timerOn = 60;
word timerOff = 120;
byte TM = 4; // Pin timer

/* VARS */
double temp;
word xtime;
boolean isTimerOn = false;

void setup(){
  sensor.begin();
  lcd.begin(20,4);
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print(F("PENGATUR SUHU"));
  lcd.clear();
  
  // INITIALIZE
  pinMode(TM, OUTPUT);
  
  t.every(1000, printLCD);
  xtime = timerOff;
}

void loop(){
  t.update();
}

/* FUNCTIONS */
void printLCD(){
  
  /* Ambil suhu */
  sensor.requestTemperatures();
  temp = sensor.getTempCByIndex(0);
  
  /* Tampilkan Suhu */
    lcd.setCursor(0,0);
    lcd.print(F("S:"));
    lcd.print(temp);
    lcd.print(F("C "));
    
  /* Tampilkan Timer */
    lcd.setCursor(9,0);
    lcd.print("T:");
    lcd.print(printTimer());
    
  /* Tampilkan Switch */
    lcd.setCursor(0,1);
    lcd.print("A:");
    lcd.print(1);
    
    lcd.setCursor(4,1);
    lcd.print("B:");
    lcd.print(0);

    lcd.setCursor(8,1);
    lcd.print("C:");
    lcd.print(0);

    lcd.setCursor(12,1);
    lcd.print("T:");
    lcd.print(0);
                
}

String printTimer()
{
    String sMinute,sSecond;
    int minute = (xtime/60);
    int second = (xtime%60);

    if(minute > 0)
    {
        if(minute > 9)
        {
            sMinute = String(minute);
        }
        else
        {
            sMinute = "0" + String(minute);
        }
    }
    else
    {
        sMinute = "00";
    }
    if(second > 0)
    {
        if(second > 9)
        {
            sSecond = String(second);
        }
        else
        {
            sSecond = "0" + String(second);
        }
    }
    else
    {
        sSecond = "00";
    }
    xtime -= 1;

    if(xtime == 0)
    {
        if(isTimerOn)
        {
            xtime = timerOff;
        }
        else
        {
            xtime = timerOn;
        }
        isTimerOn = !isTimerOn;
    }

    /* SET PIN H-L */
    if(isTimerOn)
    {
        digitalWrite(TM, LOW);
    }
    else
    {
        digitalWrite(TM, HIGH);
    }
    
    return sMinute + ":" + sSecond;
}
