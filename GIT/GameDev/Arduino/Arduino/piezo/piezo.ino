

#define pot A0

int p = 12;
int herz;

void setup() 
{
  pinMode(p, OUTPUT);
  pinMode(pot, INPUT); // потенциометр
}

void loop() 
{
  //int herz = analogRead(pot) / 2;
  herz = 261;
  tone(p, herz);
  delay(1000);
  herz = 293;
  tone(p, herz);
  delay(1000);
  herz = 329;
  tone(p, herz);
  delay(1000);
  herz = 349;
  tone(p, herz);
  delay(1000);
  herz = 391;
  tone(p, herz);
  delay(1000);
  herz = 440;
  tone(p, herz);
  delay(1000);
  herz = 493;
  tone(p, herz);
  delay(1000);
  herz = 523;
  tone(p, herz);
  delay(1000);
  noTone(p);
  delay(10000);
}
