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
  }

  void turnLeft(const unsigned sec) {
    move(left, sec);
  }

  void turnRight(const unsigned sec) {
    move(right, sec);
  }

private:
  Direction forward;
  Direction left;
  Direction right;
  Direction reverse;

  static constexpr unsigned DELAY_CROSSOVER = 200;

  void move(const Direction& dir, const unsigned sec) {
    dir.on();
    delay_sec(sec);
    dir.off();
    delay(DELAY_CROSSOVER);
  }

  void delay_sec(unsigned sec) {
    constexpr unsigned ONE_SEC = 1000;
    delay(sec * ONE_SEC);
  }
};

Ctrl ctrl{ FORWARD, LEFT, RIGHT, REVERSE };

void setup() {
  // put your setup code here, to run once:
  ctrl.up(1);
}


void loop() {
  // put your main code here, to run repeatedly:
}
