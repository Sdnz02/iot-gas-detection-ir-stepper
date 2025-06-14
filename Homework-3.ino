#include <IRremote.hpp>
#include <Stepper.h>

#define GAS_SENSOR_PIN 26
#define IR_RECEIVER_PIN 2
#define MOTOR_LN1_PIN 3
#define MOTOR_LN2_PIN 4
#define MOTOR_LN3_PIN 5
#define MOTOR_LN4_PIN 6
#define RGB_RED_PIN 10
#define RGB_GREEN_PIN 11
#define RGB_BLUE_PIN 12

const int stepsPerRevolution = 100;
Stepper myStepper(stepsPerRevolution, MOTOR_LN1_PIN, MOTOR_LN2_PIN, MOTOR_LN3_PIN, MOTOR_LN4_PIN);

#define IR_REMOTE_SPEED_1 0xBA45FF00 // Adjust these values to match your remote
#define IR_REMOTE_SPEED_2 0xB946FF00
#define IR_REMOTE_SPEED_3 0xB847FF00

int gasValue = 0;

void setup() {
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);

  Serial.begin(9600);
  myStepper.setSpeed(50);
  IrReceiver.begin(IR_RECEIVER_PIN);
}

void loop() {
  // Gas sensor reading
  gasValue = analogRead(GAS_SENSOR_PIN);

  if (gasValue > 300) {
    // Print gas value to serial monitor
    Serial.print("Gas Value: ");
    Serial.println(gasValue);

    // Gas detected, speed up the motor and light up RGB LEDs
    myStepper.step(stepsPerRevolution);

    // Set RGB LEDs to red color
    digitalWrite(RGB_RED_PIN, HIGH);
    digitalWrite(RGB_GREEN_PIN, LOW);
    digitalWrite(RGB_BLUE_PIN, LOW);
  } else {
    // No gas detected, adjust motor speed using remote control or gas sensor and light up RGB LEDs based on motor speed
    if (IrReceiver.decode()) {
      unsigned long value = IrReceiver.decodedIRData.decodedRawData; // Get the decoded value {
      
      switch (value) {
        case IR_REMOTE_SPEED_1:
          Serial.println("clockwise");
          myStepper.step(stepsPerRevolution);
          delay(1000);

          digitalWrite(RGB_RED_PIN, LOW);
          digitalWrite(RGB_GREEN_PIN, LOW);
          digitalWrite(RGB_BLUE_PIN, HIGH);

          break;
        case IR_REMOTE_SPEED_2:
          Serial.println("clockwise");
          myStepper.step(stepsPerRevolution);
          delay(1000);

          digitalWrite(RGB_RED_PIN, LOW);
          digitalWrite(RGB_GREEN_PIN, HIGH);
          digitalWrite(RGB_BLUE_PIN, LOW);

          break;
        case IR_REMOTE_SPEED_3:
          Serial.println("clockwise");
          myStepper.step(stepsPerRevolution);
          delay(1000);

          digitalWrite(RGB_RED_PIN, HIGH);
          digitalWrite(RGB_GREEN_PIN, LOW);
          digitalWrite(RGB_BLUE_PIN, LOW);

          break;
        default:
          // Do nothing
          break;
      }
      Serial.println(value, HEX);
      IrReceiver.resume();
    }
  }
}
