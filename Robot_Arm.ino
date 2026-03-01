#include <ESP32Servo.h>
#include "BluetoothSerial.h" 

// Function Declarations
int moveYawRight();
int moveYawLeft();
int moveShoulderUp();
int moveShoulderDown();
int moveElbowUp();
int moveElbowDown();
int clawClose();
int clawOpen();
void handleInput(char userInp);
void printStatus(String label, int value);


//Bluetooth and servo declaration

BluetoothSerial SerialBT;
Servo servo1, servo2, servo3, servo4;

int yawAngle, shoulderAngle, elbowAngle, clawAngle;




//postion change per tap
int posStep = 1;




//main setup

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Robot_Arm"); 
  
  Serial.println("Robot Arm Controller Initialized.");
  
  /* 
  Instructions:
                        "Controls:\n"
                        "- Yaw (Base):   'a' (Right), 'd' (Left)\n"
                        "- Shoulder:     'w' (Up), 's' (Down)\n"
                        "- Elbow:        'r' (Up), 'f' (Down)\n"
                        "- Claw:         'c' (Close), 'o' (Open)\n";
  **/


//servo default angles
  yawAngle = 90;
  shoulderAngle = 0;
  elbowAngle = 180;
  clawAngle = 90;

//servo ports
  servo1.attach(2);
  servo2.attach(4);
  servo3.attach(16);
  servo4.attach(17);


  servo1.write(yawAngle);
  servo2.write(shoulderAngle);
  servo3.write(elbowAngle);
  servo4.write(clawAngle);
}

//main loop
void loop() {
  if (Serial.available() > 0) {
    char userInp = Serial.read();
    Serial.print("Received from USB: ");
    Serial.println(userInp);
    handleInput(userInp);
  }

  if (SerialBT.available() > 0) {
    char userInp = SerialBT.read();
    Serial.print("Received from BT: ");
    Serial.println(userInp);
    handleInput(userInp);
  }

  delay(20);
}


// function to print status to USB Serial ONLY
void printStatus(String label, int value) {
  // We send feedback to the USB monitor
  Serial.print(label);
  Serial.println(value);
}

// Handles the character input from either source
void handleInput(char userInp) {
  switch (userInp) {
    case 'a': 
      yawAngle = moveYawRight();
      printStatus("Yaw: ", yawAngle);
      break;
    case 'd': 
      yawAngle = moveYawLeft();
      printStatus("Yaw: ", yawAngle);
      break;
    case 's': 
      shoulderAngle = moveShoulderUp();
      printStatus("Shoulder: ", shoulderAngle);
      break;
    case 'w': 
      shoulderAngle = moveShoulderDown();
      printStatus("Shoulder: ", shoulderAngle);
      break;
    case 'f': 
      elbowAngle = moveElbowUp();
      printStatus("Elbow: ", elbowAngle);
      break;
    case 'r': 
      elbowAngle = moveElbowDown();
      printStatus("Elbow: ", elbowAngle);
      break;
    case 'c': 
      clawAngle = clawClose();
      printStatus("Claw: ", clawAngle);
      break;
    case 'o': 
      clawAngle = clawOpen();
      printStatus("Claw: ", clawAngle);
      break;
    default:
      break;
  }
}

//      Servo Movement Functions 
int moveYawRight() {
  yawAngle -= posStep;
  if (yawAngle < 0) yawAngle = 0;
  servo1.write(yawAngle);
  return yawAngle;
}

int moveYawLeft() {
  yawAngle += posStep;
  if (yawAngle > 180) yawAngle = 180;
  servo1.write(yawAngle);
  return yawAngle;
}

int moveShoulderUp() {
  shoulderAngle += posStep;
  if (shoulderAngle > 180) shoulderAngle = 180;
  servo2.write(shoulderAngle);
  return shoulderAngle;
}

int moveShoulderDown() {
  shoulderAngle -= posStep;
  if (shoulderAngle < 0) shoulderAngle = 0;
  servo2.write(shoulderAngle);
  return shoulderAngle;
}

int moveElbowUp() {
  elbowAngle -= posStep;
  if (elbowAngle < 0) elbowAngle = 0;
  servo3.write(elbowAngle);
  return elbowAngle;
}

int moveElbowDown() {
  elbowAngle += posStep;
  if (elbowAngle > 180) elbowAngle = 180;
  servo3.write(elbowAngle);
  return elbowAngle;
}

int clawClose() {
  clawAngle += posStep;
  if (clawAngle > 90) clawAngle = 90;
  servo4.write(clawAngle);
  return clawAngle;
}

int clawOpen() {
  clawAngle -= posStep;
  if (clawAngle < 0) clawAngle = 0;
  servo4.write(clawAngle);
  return clawAngle;
}
