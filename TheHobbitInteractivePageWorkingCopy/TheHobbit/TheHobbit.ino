//sketch created by Akshay Joseph
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
#include "pitches.h"

//Force sensor 1
#define FORCE_SENSOR_PIN A0  // the FSR and 10K pulldown are connected to A0

LiquidCrystal_I2C lcd(0x27, 16, 2);  //Speicherort meines

const int switchPinKipp = 6;  // Kippschalter
ezButton button(7);           // create ezButton object that attach to pin 7;

//Kippschalter
int switchStateKipp = 0;
int prevSwitchStateKipp = 0;

//PixelArt

byte dwarfOne[8] = {
  0b01100,
  0b01100,
  0b00000,
  0b01110,
  0b11100,
  0b01100,
  0b11010,
  0b10011,
};

byte dwarfTwo[8] = {
  0b01100,
  0b01100,
  0b00000,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01110,
};

byte hobbitOne[8] = {
  0b00000,
  0b01100,
  0b01100,
  0b00010,
  0b11100,
  0b01100,
  0b11100,
  0b10011
};

byte hobbitTwo[8] = {
  0b00000,
  0b01100,
  0b01100,
  0b00000,
  0b01100,
  0b01100,
  0b01100,
  0b01110
};

byte gandalfTopOne[8] = {
  0b00000,
  0b01100,
  0b01100,
  0b01100,
  0b00000,
  0b01100,
  0b01100,
  0b01110
};

byte gandalfBottomOne[8] = {
  0b11100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01110
};

byte gandalfTopTwo[8] = {
  0b00000,
  0b01100,
  0b01100,
  0b01101,
  0b00001,
  0b01110,
  0b01100,
  0b01100
};

byte gandalfBottomTwo[8] = { 0b11100, 0b11100, 0b11100, 0b01100, 0b01100, 0b01010, 0b10001, 0b10001 };

int melody[] = { 0, 0, NOTE_B3, NOTE_D4, NOTE_E4, 0, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_B3, NOTE_E4, NOTE_FS4, NOTE_FS4, 0, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_B3, NOTE_B3, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_D4, NOTE_E4, 0, NOTE_B3, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_FS4, 0, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_FS4, 0, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_B4, NOTE_G4, NOTE_A4, NOTE_E4, NOTE_FS4, 0, NOTE_B3, NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_G4, 0, NOTE_FS4, NOTE_D4, NOTE_E4 };

double noteDurations[] = {
  4, 4, 4, 4, 2, 4, 4, 4, 8, 8,
  4, 4, 1, 4, 4, 4, 4, 0.875, 4, 4,
  4, 8, 8, 2, 4, 4, 4, 4, 2, 1.5,
  8, 8, 4, 4, 4, 2, 4, 4, 4, 4,
  4, 1, 4, 8, 8, 4, 4, 4, 1.5, 4,
  4, 2, 4, 1, 4, 4, 4, 1, 4, 4,
  4, 4, 2, 2, 8, 2, 8, 0.5
};



void setup() {

  lcd.begin();  // set up number of columns and rows

  // lcd.createChar(0, customChar);  // create a new custom character
  lcd.createChar(1, dwarfOne);
  lcd.createChar(2, dwarfTwo);
  lcd.createChar(3, hobbitOne);
  lcd.createChar(4, hobbitTwo);
  lcd.createChar(5, gandalfTopOne);
  lcd.createChar(6, gandalfBottomOne);
  lcd.createChar(7, gandalfTopTwo);
  lcd.createChar(8, gandalfBottomTwo);

  // lcd.setCursor(2, 0);  // move cursor to (2, 0)
  // lcd.write((byte)0);   // print the custom char at (2, 0)

  // lcd.setCursor(5, 0);
  // lcd.write((byte)2);

  // lcd.begin();
  // lcd.backlight();

  // Serial.begin(9600);

  // //Button und Kippschalterverbindung
  // pinMode(switchPinKipp, INPUT);
  // button.setDebounceTime(50);  // set debounce time to 50 milliseconds



  //  lcd.setCursor(2, 0);

  // lcd.print((byte)0);

  // lcd.print("Hoch und runter");
  // lcd.setCursor(0, 1);
  // lcd.print("mach mich munter");

  // lcd.setCursor(8, 0);
  // riddleShake();
}

void loop() {

  for (int i = 0; i < 15; i++) {
    lcd.setCursor(i, 1);
    if (i == 0) {  // hobbit
      lcd.write((byte)3);
    } else if (i == 14) {
      lcd.setCursor(i, 0);
      lcd.write((byte)5);
      lcd.setCursor(i, 1);
      lcd.write((byte)6);
    } else {
      lcd.write((byte)1);
    }
  }
  delay(750);
  lcd.clear();

  for (int i = 0; i < 15; i++) {
    lcd.setCursor(i, 1);
    if (i == 0) {  // hobbit
      lcd.write((byte)4);
    } else if (i == 14) {
      lcd.setCursor(i, 0);
      lcd.write((byte)7);
      lcd.setCursor(i, 1);
      lcd.write((byte)8);
    } else {
      lcd.write((byte)2);
    }
  }

  delay(750);
  lcd.clear();
}

void pressFriend() {
  // while (true) {
  //   button.loop();

  //   if (button.isPressed()) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Show me:");
  lcd.setCursor(0, 1);
  lcd.print("'Freunde'");
  playVocabel();
  //   }
  // }
}

void riddleShake() {
  //Kippschalter ab hier

  while (true) {
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
}

void playHobbit() {
  for (int thisNote = 0; thisNote < 68; thisNote++) {

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
  pressFriend();
}

void playVocabel() {
  boolean loopMethod = true;

  while (loopMethod) {
    int analogReading = analogRead(FORCE_SENSOR_PIN);

    if (analogReading > 900) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Good job");
      loopMethod = false;
    }
  }
}