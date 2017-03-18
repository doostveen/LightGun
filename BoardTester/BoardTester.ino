/* Lightgun board tester 
 *  Tests the LEDS (Err, TX, RX)
 *  Beep/sound
 *  LCD
 *  Button 1, Button 2
*/

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

#define PIN_BUZZER 2 // D2 Either use buzzer or MP3 player
#define PIN_LED_ERR 4 // D4 Red
#define PIN_LED_RX 5 // D5 Orange/yellow
#define PIN_LED_TX 6 // D6 Green
#define PIN_IR_RCV1 7
#define PIN_IR_RCV2 8

#define PIN_BTN1 A1 // A1=15 input (fix wiring error on board v1.0)
#define PIN_BTN2 A0 // A0=14 input (fix wiring error on board v1.0)
#define PIN_LASER A3 // output
#define PIN_SHIELD A2 // output

// D9-D13: used by NRF24L01
// A4, A5 used by I2C for LCD

int counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Board tester");

  lcd.begin(16,2);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.printstr("Lightgun tester");

  pinMode(PIN_LED_ERR, OUTPUT);
  pinMode(PIN_LED_RX, OUTPUT);
  pinMode(PIN_LED_TX, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  pinMode(PIN_LASER, OUTPUT);
  pinMode(PIN_SHIELD, OUTPUT);

  pinMode(PIN_BTN1, INPUT);
  pinMode(PIN_BTN2, INPUT);
}

void loop() {
  counter++;
  Serial.print(counter);
  Serial.print(" ");

  blinkLed(PIN_LED_ERR);
  blinkLed(PIN_LED_RX);
  blinkLed(PIN_LED_TX);

  blinkLed(PIN_LASER);
  blinkLed(PIN_SHIELD);

  //tone(PIN_BUZZER, 880);
  delay(150);
  noTone(PIN_BUZZER);
  readButtons();

  Serial.println();
}

void blinkLed(int pin)
{
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second
}

void readButtons()
{
  int val1 = digitalRead(PIN_BTN1);
  int val2 = digitalRead(PIN_BTN2);
  Serial.print("Btn1:");
  Serial.print(val1);
  Serial.print("  Btn2:");
  Serial.print(val2);
  lcd.setCursor(0,1);
  lcd.printstr("b1:");
  lcd.print(val1);
  lcd.printstr(" b2:");
  lcd.print(val2);

  if(val1==HIGH) beep(440);
  if(val2==HIGH) beep(600);
}

void beep(int frequency)
{
  tone(PIN_BUZZER, frequency);
  delay(150);
  noTone(PIN_BUZZER);
  readButtons();
}

