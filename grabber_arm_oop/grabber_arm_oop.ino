#include <Servo.h>

class ServoControl {
  public:
    int read();
    void move();
    void init(
      int potPin,
      int servoPin,
      int servoMin,
      int servoMax,
      Servo servo);
  private:
    int _potPin;
    int _potPrevValue;
    int _servoMin;
    int _servoMax;
    Servo _servo;
};

void ServoControl::init(
  int potPin,
  int servoPin,
  int servoMin,
  int servoMax,
  Servo servo) {
  _potPin = potPin;
  _servoMin = servoMin;
  _servoMax = servoMax;
  pinMode(_potPin, INPUT);
  servo.attach(servoPin);
  _servo = servo;
}

int ServoControl::read() {
  int potValue = analogRead(_potPin);
  if (abs(potValue - _potPrevValue) > 0) {
    _potPrevValue = potValue;
    return potValue;
  }
  return _potPrevValue;
}

void ServoControl::move() {
  int pos = read();
  int servoPos = map(pos, 0, 1023, _servoMin, _servoMax);
  _servo.write(servoPos);
}

// Define pins
const int basePotPin = A0;
const int tiltPotPin = A1;
const int tilt2PotPin = A2;
const int grabPotPin = A3;
const int baseServoPin = 3;
const int tiltServoPin = 5;
const int tilt2ServoPin = 9;
const int grabServoPin = 10;

// Define servos
Servo baseServo;
Servo tiltServo;
Servo tilt2Servo;
Servo grabServo;

// Define servo controls
ServoControl baseControl;
ServoControl tiltControl;
ServoControl tilt2Control;
ServoControl grabControl;


void setup() {
  Serial.begin(9600);
  baseControl.init(basePotPin, baseServoPin, 0, 180, baseServo);
  tiltControl.init(tiltPotPin, tiltServoPin, 0, 180, tiltServo);
  tilt2Control.init(tilt2PotPin, tilt2ServoPin, 0, 180, tilt2Servo);
  grabControl.init(grabPotPin, grabServoPin, 0, 180, grabServo);
}

void loop() {
  tiltControl.move();
  baseControl.move();
  tilt2Control.move();
  grabControl.move();
}