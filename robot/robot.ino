struct Direction
{
  Direction(const int pin):pin(pin)
  {
    pinMode(pin, OUTPUT);
    off();
  }

  void on()
  {
    digitalWrite(pin, 1);
  }

  void off()
  {
    digitalWrite(pin, 0);
  }
  
  private:
    const int pin;
};

constexpr int FORWARD = A3;
constexpr int LEFT = A2;
constexpr int RIGHT = A1;
constexpr int REVERSE = A0;

void setup() {
  // put your setup code here, to run once:
  reverse.on();
  delay(1000);
  reverse.off();
}


void loop() {
  // put your main code here, to run repeatedly:

}
