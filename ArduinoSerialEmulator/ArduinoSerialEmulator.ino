/*
 *  ArduinoSerialEmulator.ino
 *  2020 Copyright (c) Nathan Sales. All rights reserved.
 *
 *  Author: Nate Sales (@nwsnate)
 *
 *  ENDEC serial device emulation, used for testing and development without access to a real ENDEC.
 *  Makes on-the-go testing a lot more convenient, since you don't need to carry around a 2U rackmount device.
 *
 *  Usage:
 *  Hook up a button to any digital pin and ground, and specify the digital pin in the BUTTON constant below.
 *  Then, connect the board to your computer, and configure OpenENDEC to use the board's serial port.
 *  Pressing the button will trigger an alert.
 *
*/

const int BUTTON = 8; // Digital button pin
const model MODEL = SAGE_1822; // ENDEC Model
const int BAUD = 9600;

enum model {
  SAGE_1822
};

void setup() {
  Serial.begin(BAUD);

  pinMode(BUTTON, INPUT_PULLUP);
}


void loop() {
  int state = digitalRead(BUTTON_PIN);
  if (state == 0) {
    String output = "";

    if (model == model.SAGE_1822) {
      output = "<ENDECSTART>"
      "Local Alert sent at 00/00/00 00:00:00"
      "A ENDEC Emulator has issued a test alert for development and"
      "testing of the OpenENDEC system. This alert has no real meaning"
      "and can be safely ignored. (OPENENDEC)"
      "ZCZC-EAS-RWT-041000-053000+0100-0821713-OPENENDEC-"
      "<ENDECEND>";
    } else {
      output = "ENDECEmulator error: Invalid model definition.";
    }

    Serial.writeln(output);
  }
  delay(500); // Button debounce, and give the serial lines time to empty.
}
