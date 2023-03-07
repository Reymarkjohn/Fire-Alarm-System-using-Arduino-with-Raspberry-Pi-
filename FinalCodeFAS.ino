#define MQ2pin 0
#define Threshold 110 //Threshold Value (adjust for any changes)
#include <SoftwareSerial.h>

SoftwareSerial SIM900A(10,11);
float sensorValue;
const int buzzer = 9;
const int water = 7;



void setup() {
  Serial.begin(9600);
  pinMode(water, OUTPUT);
  Serial.println("MQ2 warming up!");
  delay(2000);
  SIM900A.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println ("SIM900A Ready");
  delay(100);

}

void loop() {
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
  
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if(sensorValue > Threshold)
  {
    Serial.print(" | Smoke detected!");
    tone(buzzer, 500);
    digitalWrite(water, HIGH);
    Function1();
  }
  else{
    noTone(buzzer);
    digitalWrite(water, LOW);
  }

  delay(2000); // wait 2s for next reading
   if (SIM900A.available()>0)
   Serial.write(SIM900A.read());
}


void Function1(){

  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+639977628215\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("Alert Fire Detected!!!");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ->SMS FAS");

}

