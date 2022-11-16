//sketch created by Akshay Joseph
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
#include "pitches.h"

//Force sensor 1
#define FORCE_SENSOR_PIN A0  // the FSR and 10K pulldown are connected to A0

LiquidCrystal_I2C lcd(0x27, 16, 2);  //Speicherort meines

const int switchPinKipp = 6;  // Kippschalter
ezButton button(7);       // create ezButton object that attach to pin 7;

//Kippschalter
int switchStateKipp = 0;
int prevSwitchStateKipp = 0;

int melody[] = {
  0, 0, NOTE_B3, NOTE_D4, NOTE_E4, 0, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_B3, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_B3, NOTE_B3, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_D4, NOTE_E4, 0, NOTE_B3, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0, NOTE_FS4, 0, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_B4, NOTE_G4, NOTE_A4, NOTE_E4, NOTE_FS4, 0, NOTE_B3, NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_G4, 0, NOTE_FS4, NOTE_D4, NOTE_E4
};

double noteDurations[] = {
  4, 4, 4, 4, 2, 4, 4, 4, 8, 8, 4, 4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 2, 4, 8, 8, 4, 4, 4, 2, 4, 4, 4, 4, 4, 1, 4, 8, 8, 4, 4, 4, 1.5, 4, 4, 2, 4, 1, 4, 4, 4, 1, 4, 4, 4, 4, 2, 2, 8, 2, 8, 0.5
};

void setup() {
  lcd.begin();
  lcd.backlight();

  Serial.begin(9600);

  //Button und Kippschalterverbindung
  pinMode(switchPinKipp, INPUT);
  button.setDebounceTime(50);  // set debounce time to 50 milliseconds

  lcd.setCursor(0, 0);
  lcd.print("Hoch und runter");
  lcd.setCursor(0, 1);
  lcd.print("mach mich munter");

  lcd.setCursor(8, 0);
}

void loop() {

  button.loop();
  if (button.isPressed()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Show me:");
    lcd.setCursor(0, 1);
    lcd.print("'Freunde'");
    playVocabel();
  }

  //Kippschalter ab hier
  switchStateKipp = digitalRead(switchPinKipp);

  if (switchStateKipp != prevSwitchStateKipp) {
    if (switchStateKipp == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sehr gut,");
      lcd.setCursor(0, 1);
      lcd.print("kleiner Hobbit!");
      playHobbit();
    }
  }

  prevSwitchStateKipp = switchStateKipp;
}

void playHobbit() {
  for (int thisNote = 0; thisNote < 64; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);
  }
}

void playVocabel() {
  boolean loopMethod = true;

  while (loopMethod) {
    int analogReading = analogRead(FORCE_SENSOR_PIN);

    Serial.println(analogReading);

    if (analogReading > 900) {      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Good job");
      loopMethod = false;
    }    
  }
}