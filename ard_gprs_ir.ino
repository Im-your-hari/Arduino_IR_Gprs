#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2,3);
 
#include <String.h>
//#include <DHT.h> 

float meter =0;

float kilometers=0;
#define DHTPIN A0
 
//DHT dht(DHTPIN, DHT11);
 
void setup()
{
  pinMode (9,INPUT);
  pinMode (12,OUTPUT);
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  //dht.begin();
 
  delay(500);
}
 
void loop()
{
      float meter =0;
      float kilometers=0.00;
      //float h = dht.readHumidity();
      //float t = dht.readTemperature(); 
      //delay(100);
       if (digitalRead(9) == LOW)
       {
        digitalWrite(12,HIGH);
        meter=meter +2.5;
        if (meter == 100)
        {
          kilometers =kilometers +0.1 ;
          meter=0;
        }
       }   
         
      //Serial.print("Temperature = ");
      //Serial.print(t);
      //Serial.println(" °C");
      //Serial.print("Humidity = ");
      //Serial.print(h);
      //Serial.println(" %");    
      Serial.print(meter);
      Serial.println("    MTRS");
      Serial.println(kilometers);
      Serial.println("    KMS");
      digitalWrite(12,LOW);
      delay(100);

      
   
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT");
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");
  delay(1000);
 
  gprsSerial.println("AT+CREG?");
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");
  delay(1000);
 
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);
 
  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=O13AOCHYYNU2LQ19&field1=" + String(meter) +"&field2="+String(kilometers);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
}
