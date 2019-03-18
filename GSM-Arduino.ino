#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
String textMessage_1;
const int led1 = 5; 
const int led2 = 6;
int pre1, pre2, pres2;
int pres1 = pre1 = pre2 = pres2 = LOW;
void func(String textMessage)
{
  if (textMessage.indexOf("8277795414") > 0) {
    if (textMessage.indexOf("ON1") > 0)
    {
      Serial.println("Works");
      analogWrite(led1, 255);

    }
    if (textMessage.indexOf("OFF1") > 0)
    {
      Serial.println("Works");
      digitalWrite(led1, LOW);
    }

    if (textMessage.indexOf("ON2") > 0)
    {
      Serial.println("Works");
      analogWrite(led2, 255);
    }
    if (textMessage.indexOf("OFF2") > 0)
    {
      Serial.println("Works");
      digitalWrite(led2, LOW);
    }
    delay(10);
  }
}





void setup() {


  Serial.begin(9600);
  mySerial.begin(2400);
  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT"); 
  updateSerial();
  mySerial.println(" AT+CMEE=2");
  updateSerial();

  
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0"); 
  updateSerial();
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW); 
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

}

void loop() {
  updateSerial();
  pres1 = digitalRead(7);
  pres2 = digitalRead(8);
  if (pre1 != pres1)
  {
    if (pres1 == HIGH)
    {

      Serial.println("Led1 is HIGH");



      mySerial.println("AT+CMGF=1");    

      delay(50);  

      mySerial.println("AT+CMGS=\"+918277795414\"\r"); 

      delay(50);

      mySerial.println("Fan is ON");

      delay(50);

      mySerial.println((char)26);

      delay(50);


    }
    else if (pres1 == LOW)
    {

      Serial.println("Led1 is LOW");



      mySerial.println("AT+CMGF=1");    
      delay(50);  
      mySerial.println("AT+CMGS=\"+918277795414\"\r"); 

      delay(50);

      mySerial.println("Fan is OFF");

      delay(50);

      mySerial.println((char)26);
      
      delay(50);

    }
    pre1 = pres1;
  }
  if (pre2 != pres2)
  {
    if (pres2 == HIGH)
    {
      //digitalWrite(led2,HIGH);
      Serial.println("Led2 is HIGH");



      mySerial.println("AT+CMGF=1");   
      delay(50);  

      mySerial.println("AT+CMGS=\"+918277795414\"\r"); 

      delay(50);

      mySerial.println("Light is ON");

      delay(50);

      mySerial.println((char)26);

      delay(50);

    }
    else if (pres2 == LOW)
    {

      Serial.println("Led2 is LOW");




      mySerial.println("AT+CMGF=1");    

      delay(5000);  

      mySerial.println("AT+CMGS=\"+918277795414\"\r"); 

      delay(50);

      mySerial.println("Light is OFF");

      delay(50);

      mySerial.println((char)26);

      delay(50);


    }
    pre2 = pres2;
  }
}

void updateSerial()
{
  delay(50);
  while (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
    textMessage_1 = mySerial.readString();
    Serial.print(textMessage_1);
    func(textMessage_1);
    delay(50);

  }
}
/*void updateSerial()
  {
   delay(500);
  while (Serial.available())
  {
    GPRS.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(GPRS.available())
  {
    Serial.write(GPRS.read());//Forward what Software Serial received to Serial Port
    textMessage_1 = GPRS.readString();
    Serial.print(textMessage_1);
    func(textMessage_1);
    delay(50);
  }
  /*  if(GPRS.available()>0){
    textMessage_1 = GPRS.readString();
    Serial.print(textMessage_1);
    func(textMessage_1);
    delay(50);
  }*/
