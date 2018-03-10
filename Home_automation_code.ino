#include<SoftwareSerial.h>
SoftwareSerial mySerial(8,9);
String voice;
int sensor=A1;
float temp_read,Temp_alert_val,Temp_shut_val,temp_ac;
int sms_count=0,Fire_Set;
int sensorPin=A0; //Select the input pin for the LDR
int sensorValue=0;//variable to store the input value
int trigPin=13; //Trigger Pin
int echoPin=12;
long duration;
int distance;
int led1=2; //Connect Led1 to Pin#2
int led2=3; //Connect Led2 to Pin#3
int led3=4; //Connect Led3 to Pin#4
int led4=5; //Connect Led4 to Pin#5
int led5=6; //Connect Led5 to Pin#6
int led6=7; //Connect Led6 to Pin#7
//---------------Call A Function---------------//

void allon(){ 
  //Switching all the led on upon voice command
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led5,HIGH);
  digitalWrite(led6,HIGH);
  delay(5000);
  
  }

float CheckTemp(){
    temp_read=analogRead(sensor); 
    //reads the sensor Output (Vout of LM35 sensor)
    temp_read=temp_read*0.2048;
    //Converting the sensor reading to temperature
    temp_read=temp_read*5;
    //Adds the decimal point
    temp_read=temp_read/10;
   
    }
void alloff(){
  //Switching all the led off upon voice command
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);
  digitalWrite(led6,LOW);
  delay(5000);
  
  }

//LDR Sensor Coding-----------//
void check_light() {
 sensorValue=analogRead(sensorPin);
 Serial.println(sensorValue);
 if(sensorValue>500){
  Serial.println("LED light off");
  digitalWrite(led4,LOW);
  delay(1000);
  digitalWrite(led5,LOW);
  delay(1000);
  
  }
  digitalWrite(led4,LOW);
  delay(sensorValue);
  if(voice.length()>0){
    Serial.println(voice);
    if(voice=="*all on"){
      //Call the all on function
      allon();
     
      }
      else if(voice=="*all of" || voice=="*all off"){
        //Switch off all the appliances
        alloff();
        }
        else if(voice=="*bedroom lights off"){
          digitalWrite(led4,LOW);
          }
         else if(voice=="*bedroom lights on"){
          digitalWrite(led4,HIGH);
          } 
          else if(voice=="*bathroom lights on"){
          digitalWrite(led5,HIGH);
          }
          else if(voice=="*bathroom lights off"){
          digitalWrite(led5,LOW);
          }     
    } }
    //-------Ultrasonic Sensor------//
    void automatic_bathroom_lights() {
      //Clears trig Pin
      if(voice.length()>0){
        Serial.println(voice);
        }
       if(voice=="*all on"){
        allon(); //Turn on all the Pins
        
        }
        else if(voice=="*all off"){
          alloff();} 
          else if(voice=="*bedroom lights on"){
            digitalWrite(led4,HIGH);
            }
            else if(voice=="*bedroom lights off"){
              digitalWrite(led4,LOW);
              }
      
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
 digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  if(distance<5){
    Serial.println("Distance");
    Serial.println(distance);
    digitalWrite(led5,HIGH);
    
    }
    if(distance>20){
      Serial.print("Distance:");
      Serial.println(distance);
      digitalWrite(led5,LOW);
      
      
      }
  
  }
//---------------Checking the FIRE------------//

void CheckFire(){
  Temp_alert_val=CheckTemp();
  Serial.print(Temp_alert_val);
  if(Temp_alert_val>45){
    Fire_Set=1;
    while(sms_count<3)//Number of SmS Alerts to be sent
    {
      SendTextMessage();//Function to send AT commands to GSM Module
      
      }
    }
  }
  void SendTextMessage(){
    
    mySerial.println("AT+CMGF=1");//To send SMS in text Mode
    delay(2000);
    mySerial.println("AT+CMGS=\"+Enter the number here\"r");//Enter the phone number that you 
    //using and enter the country code also
    delay(2000);
    mySerial.println("Fire in New Room");//the message content to be displayed for SMS
    delay(2000);
    mySerial.println((char)26);//the stopping character
    delay(5000);
    mySerial.println("AT+CMGS=\"+Enter the number here\"r");//Enter the phone number that you 
    //using and enter the country code also
    delay(2000);
    mySerial.println("Fire in New Room");//the message content to be displayed for SMS
    delay(2000);
    mySerial.println((char)26);//the stopping character
    {delay(5000);
    sms_count++;
    }}
    
    

void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
  delay(500);

}

void loop() {
  
while(Serial.available()){
  //Check if there is an available byte to read
  delay(10); //Delay added to stabalise
  char c=Serial.read();//Conduct a serial read
  if(c=="#"){ 
    //Exit the loop when # is detected after the word
    break;
    }
    voice+=c;//Shorthand for voice=voice +c
  }
if(voice.length()>0){
  
  Serial.println(voice);
  }
  //-----------------------------------//
  //------------Control Multiple Pins/LEDs-----------//
if(voice=="*all on "){
  allon();} //Turn on all the pins
  else if(voice=="*all off "){
  alloff();}//turn off all the pins

  
//-----------Turn On One By One ---------------//
else if(voice=="*TV on"||voice=="*tv on"){
  digitalWrite(led1,HIGH);
  
  }
else if(voice=="*fan on"){
  digitalWrite(led2,HIGH);
  
  }
  
else if(voice=="*computer on"){
  digitalWrite(led3,HIGH);
  }
  
else if(voice=="*bedroom light on"){
  digitalWrite(led4,HIGH);
  
  }

  
else if(voice=="*bathroom light on"){
  digitalWrite(led5,HIGH);
  
  }
  
else if(voice=="*ac on"){
  digitalWrite(led6,HIGH);
  
  }
  
//------------_Turn off one by one-------------//

else if(voice=="*TV  off"||voice=="*tv off"){
  digitalWrite(led1,LOW);
  
  }
else if(voice=="*fan off"){
  digitalWrite(led2,LOW);
  
  }
  
else if(voice=="*computer off"){
  digitalWrite(led3,LOW);
  }
  
else if(voice=="*bedroom light off"){
  digitalWrite(led4,LOW);
  
  }

  
else if(voice=="*bathroom light off"){
  digitalWrite(led5,LOW);
  
  }
  
else if(voice=="*ac off"){
  digitalWrite(led6,LOW);
  
  }
  //________________//
  voice="";
  delay(5000); 

if(voice !="all of"||voice!="*all off"){
  ACON();
  automatic_bathroom_lights();
  check_light();
  delay(5000);
  voice="";
}
}
  

    //----------Switching on AC----------
    void ACON()
    {
      temp_ac=CheckTemp();
      Serial.println("temperature");
      Serial.println(temp_ac);
      if((temp_ac>=18)&&(temp_ac<50)){
        Serial.println("Temperature:");
        digitalWrite(led6,HIGH);// switch on the Ac automatically
        digitalWrite(led2,HIGH);//switch on fan sutomatically
        }
      if(voice.length()>0){
        Serial.println(voice);
        }
      if(voice=="*all on"){
        
        allon();
        }
if(voice=="*all off"){
        
        alloff();
        }
else if(voice=="*ac on"){
        
        digitalWrite(led6,HIGH);
        }
        
else if(voice=="*ac off"){
        
        digitalWrite(led6,LOW);
        }
        
else if(voice=="*fan on"){
        
        digitalWrite(led2,HIGH);
        }
        
else if(voice=="*ac off"){
        
        digitalWrite(led2,LOW);
        }
        
      }
