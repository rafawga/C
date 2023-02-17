void setup() {
  pinMode(23,INPUT);
  Serial.begin(9600);

}

 bool in = digitalRead(23);
void loop() {
  Serial.println(in);

}
