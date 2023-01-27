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
    forward.on();
    delay_sec(sec);
    forward.off();
    delay(DELAY_CROSSOVER);
  }

  void down(const unsigned sec) {
    reverse.on();
    delay_sec(sec);
    reverse.off();
    delay(DELAY_CROSSOVER);
  }

  void turnLeft(const unsigned sec) {
    left.on();
    delay_sec(sec);
    left.off();
    delay(DELAY_CROSSOVER);
  }

  void turnRight(const unsigned sec) {
    right.on();
    delay_sec(sec);
    right.off();
    delay(DELAY_CROSSOVER);
  }

private:
  Direction forward;
  Direction left;
  Direction right;
  Direction reverse;

  static constexpr unsigned DELAY_CROSSOVER = 200;
  
  void delay_sec(unsigned sec) {
    constexpr unsigned ONE_SEC = 1000;
    delay(sec * ONE_SEC);
  }
};

Ctrl ctrl{ FORWARD, LEFT, RIGHT, REVERSE };

void setup() {
  // put your setup code here, to run once:
  ctrl.turnRight(1);
}


void loop() {
  // put your main code here, to run repeatedly:
}
