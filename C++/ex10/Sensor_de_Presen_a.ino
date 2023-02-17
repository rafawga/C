

void setup() {
 pinMode(4,INPUT);
 pinMode(2,OUTPUT);

}

void loop() {
  bool in;
  in = digitalRead(4);
  digitalWrite(2,in);

}
