# include <Servo.h>

#define ser 10

Servo servo;

void setup()
  {
    servo.attach(ser);
  }

void loop()
  { 
    int y = 1000;
    servo.write(0);
    delay(y);
    servo.write(180);
    delay(y);
  }


