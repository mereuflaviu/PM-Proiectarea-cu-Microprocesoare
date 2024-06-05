#include <Servo.h>

#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_E 6
#define BUTTON_F 7
#define JOYSTICK_X A0 // Analog pin for joystick X-axis
#define JOYSTICK_Y A1 // Analog pin for joystick Y-axis
#define DELAY 100

Servo servo1; // Servo for left-right movement
Servo servo2; // Servo for up-down movement
Servo servo3; // Servo for trigger action

int servo1Pos = 90; // Initial position for servo1 (left-right)
int servo2Pos = 90; // Initial position for servo2 (up-down)
bool joystickControl = false; // State variable for joystick control

void setup() {
  Serial.begin(9600);
  // Initialize servos
  servo1.attach(9); // Pin D9 for servo1
  servo2.attach(10); // Pin D10 for servo2
  servo3.attach(11); // Pin D11 for servo3
  // Enable pull-up resistors for buttons
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_E, INPUT_PULLUP);
  pinMode(BUTTON_F, INPUT_PULLUP);
  // Initialize joystick pins
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
}

void loop() {
  // Read button states
  if (digitalRead(BUTTON_E) == LOW) {
    Serial.println("Button E is pressed - Toggling joystick control");
    joystickControl = !joystickControl;
    delay(DELAY);
  }

  // Trigger action is always enabled
  if (digitalRead(BUTTON_F) == LOW) {
    Serial.println("Button F is pressed");
    // Action the trigger servo3
    servo3.write(0); // Move servo3 to pressed position
    delay(1000); // Adjust delay according to trigger action duration
    servo3.write(90); // Move servo3 back to initial position
    delay(DELAY);
  }

  if (joystickControl) {
    // Joystick control for servos
    int joyX = analogRead(JOYSTICK_X);
    int joyY = analogRead(JOYSTICK_Y);
    // Define deadzone to avoid jitter around center position
    int deadzone = 50;

    if (joyX < (512 - deadzone)) {
      // Joystick is moved left
      servo1Pos = constrain(servo1Pos - 10, 0, 180); // Move left
    } else if (joyX > (512 + deadzone)) {
      // Joystick is moved right
      servo1Pos = constrain(servo1Pos + 10, 0, 180); // Move right
    }
    if (joyY < (512 - deadzone)) {
      // Joystick is moved up
      servo2Pos = constrain(servo2Pos - 10, 0, 180); // Move up
    } else if (joyY > (512 + deadzone)) {
      // Joystick is moved down
      servo2Pos = constrain(servo2Pos + 10, 0, 180); // Move down
    }
    
    // Write the positions to the servos
    servo1.write(servo1Pos);
    servo2.write(servo2Pos);
    delay(DELAY);
  } else {
    if (digitalRead(BUTTON_UP) == LOW) {
      Serial.println("Button A is pressed");
      // Code to move servo2 (up-down) up
      servo2Pos = constrain(servo2Pos + 15, 0, 180); // Increase increment value for faster movement
      servo2.write(servo2Pos);
      delay(DELAY);
    }

    if (digitalRead(BUTTON_RIGHT) == LOW) {
      Serial.println("Button B is pressed");
      // Code to move servo1 (left-right) right
      servo1Pos = constrain(servo1Pos + 15, 0, 180);
      servo1.write(servo1Pos);
      delay(DELAY);
    }

    if (digitalRead(BUTTON_DOWN) == LOW) {
      Serial.println("Button C is pressed");
      // Code to move servo2 (up-down) down
      servo2Pos = constrain(servo2Pos - 15, 0, 180); // Increase decrement value for faster movement
      servo2.write(servo2Pos);
      delay(DELAY);
    }

    if (digitalRead(BUTTON_LEFT) == LOW) {
      Serial.println("Button D is pressed");
      // Code to move servo1 (left-right) left
      servo1Pos = constrain(servo1Pos - 15, 0, 180);
      servo1.write(servo1Pos);
      delay(DELAY);
    }
  }
}
