struct Direction {
  Direction(const int pin)
    : pin(pin) {
    pinMode(pin, OUTPUT);
    off();
  }

  void on() {
    digitalWrite(pin, 1);
  }

  void off() {
    digitalWrite(pin, 0);
  }

private:
  const int pin;

  Direction& operator=(Direction&) = delete;
  // Direction(Direction&) = delete;
};

constexpr int FORWARD = A3;
constexpr int LEFT = A2;
constexpr int RIGHT = A1;
constexpr int REVERSE = A0;

struct Ctrl {
  Ctrl(const int pinForward, const int pinLeft, const int pinRight, const int pinReverse)
    : forward(Direction{ pinForward }), left(Direction{ pinLeft }), right(Direction{ pinRight }), reverse(Direction{ pinReverse }) {
  }

  void up(const unsigned sec) {
    move(forward, sec);
  }

  void down(const unsigned sec) {
    move(reverse, sec);
    revDown(reverse, 9, 7);
  }

  void turnLeft(const unsigned sec) {
    move(left, sec);
  }

  void turnRight(const unsigned sec) {
    move(right, sec);
  }

  void test() {
    down(2);
  }

private:
  Direction forward;
  Direction left;
  Direction right;
  Direction reverse;

  static constexpr unsigned MAX_PWM = 10;

  void move(const Direction& dir, const unsigned sec) {
    dir.on();
    delay_sec(sec);
    dir.off();
  }

  void revDown(const Direction& dir, const unsigned start, const unsigned stop) {

    if (start < stop) return;
    if (start > MAX_PWM) return;

    for (int i = start; i >= stop; i--) {
      pwm(dir, i);
      pwm(dir, i);
      pwm(dir, i);
    }
  }

  void pwm(const Direction& dir, const unsigned val) {
    const unsigned onVal = (val > MAX_PWM) ? MAX_PWM : val;
    const unsigned offVal = MAX_PWM - onVal;
    for (unsigned i = 0; i < MAX_PWM; i++) {
      dir.on();
      delay(onVal);
      dir.off();
      delay(offVal);
    }
  }

  void delay_sec(unsigned sec) {
    constexpr unsigned ONE_SEC = 1000;
    delay(sec * ONE_SEC);
  }
};

Ctrl ctrl{ FORWARD, LEFT, RIGHT, REVERSE };

void setup() {
  // put your setup code here, to run once:
  ctrl.test();
}


void loop() {
  // put your main code here, to run repeatedly:
}
