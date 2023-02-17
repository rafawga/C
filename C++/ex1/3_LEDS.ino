void setup() 
{
 pinMode(13,OUTPUT);
 pinMode(27,OUTPUT);
 pinMode(32,OUTPUT);
}

void pisca ()
{

int b [3] = {13,27,32};
int i;


  for (i=0;i<3;i++)
  {
  
  digitalWrite(b[i],HIGH);
  delay(100);
  digitalWrite(b[i],LOW);
  }

}

       
void loop() 
{
pisca();
}
