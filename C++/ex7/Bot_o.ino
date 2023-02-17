int in;
int x = 0;
void setup() {
  pinMode(21,INPUT_PULLDOWN);
  pinMode(19,OUTPUT);
  Serial.begin(9600);

}

void loop() {

  
  
  in = digitalRead(21); 
                                                                                                                                                                    

  if ((in !=0)&& (x==0) ){
    digitalWrite(19, HIGH);
    delay(150);
    x =1;
    Serial.println(x);}
  else if ((in !=0)&& (x==1)){
    
      digitalWrite(19, LOW);
        delay(150);
        x =0;
        Serial.println(x);
      
       

}
}
