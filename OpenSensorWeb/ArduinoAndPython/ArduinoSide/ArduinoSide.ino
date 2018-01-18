#include <dht.h>

dht DHT;

#define DHT11_PIN 7
#define SOUND_PIN 6
#define SOUND_LED 13

//Temperature & humidity
int temperature = -999;
int humidity = -999;
int sound = -1;

//Sound
int soundDetectedVal = HIGH;
boolean soundStillRunning = false;
unsigned long soundRunningTime = 1000; // in milliseconds
int cpt = 0;
int isNoisy = 0;

void setup(){
  Serial.begin(9600);
  pinMode(SOUND_PIN, INPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOUND_LED, OUTPUT);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN); //Needed to dht function normally
  humidity = DHT.humidity;
  temperature = DHT.temperature;
  sound = digitalRead(SOUND_PIN);

  if(sound == 0){
    isNoisy = 1;
   // Serial.println("NOISYYYYY: " + cpt);
  }
  
  if(isNoisy && cpt < 5){
    sound = 0;
      //  Serial.println("STILL NOISYYYYY");
  }else{
    sound = digitalRead(SOUND_PIN);
  }

  if(humidity != -999 && temperature != -999){
      Serial.print("Temperature=");
      Serial.print(temperature);
      Serial.print(":::Humidity=");
      Serial.print(humidity);
      Serial.print(":::");
      Serial.print("Sound=");
      Serial.print(sound);
      Serial.println("");

      if(sound == 0){
        digitalWrite(SOUND_LED , HIGH);
      }else{
        digitalWrite(SOUND_LED , LOW);
      }

      cpt++;
  }
  

  

//  soundDetectedVal = digitalRead(SOUND_PIN);
//  if(soundDetectedVal == LOW) //If we hear something
//  {
//    Serial.print("Loud");
//  }else{
//    Serial.print("Quiet");
//  }

  

  //delay(1250);

  if(isNoisy && cpt >= 5){
    isNoisy = 0;
    cpt=0;
  }
  
}

