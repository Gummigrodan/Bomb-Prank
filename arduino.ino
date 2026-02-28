#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long countdownTime = 0;
bool timerRunning = false;
unsigned long previousMillis = 0;

const int buzzer = 9;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("START BOMB TIMER");

  pinMode(buzzer, OUTPUT);
}

void loop() {

  // Läs HEL rad från Python
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();  // ta bort mellanslag

    if (input.length() > 0) {
      countdownTime = input.toInt();

      if (countdownTime > 0) {
        timerRunning = true;
        previousMillis = millis();   // resetta tid
        lcd.clear();
      }
    }
  }

  // Nedräkning
  if (timerRunning) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      countdownTime--;

      displayTime(countdownTime);

      if (countdownTime <= 0) {
        timerRunning = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("JK LOSER!");
      }
    }
  }
}

void displayTime(long seconds) {
  int minutes = seconds / 60;
  int secs = seconds % 60;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACTIVATES IN:");

  lcd.setCursor(0, 1);

  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");

  if (secs < 10) lcd.print("0");
  lcd.print(secs);

  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(100);         // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);
}