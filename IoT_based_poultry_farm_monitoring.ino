#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleDHT.h>

char auth[] = "249b882a076c4e7e9cbb35dd12b56b9c"; // Your Auth token
char ssid[] = "Jontrotantrik";
char pass[] = "jtl.robotics";

//float phValue;

const int pinDHT11 = 2; // D4 on nodemcu
//const int ph_sensor=A0;
const int pump1 = 4; //D2
const int light1 = 5; //D1
const int light2 = 12; //D6
const int fan = 14; //D5
const int flame = 13; //D7 on nodemcu

SimpleDHT11 dht11;
BlynkTimer timer;
int flame_value;

void sendSensor()
{

  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  //byte phValue=0;
  byte flame_value = 0;
  //byte phValue;
  flame_value = analogRead(flame);
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }
  // for debug purposes.
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");
  // DHT11 sampling rate is 1HZ.
  //Serial.print((int)phValue); Serial.println(" PH");
  Serial.print((int)flame_value); Serial.println(" Flame");
  delay(1000);
  Blynk.virtualWrite(V5, temperature);

  Blynk.virtualWrite(V7, humidity);
  // Blynk.virtualWrite(V6, phValue);
  Blynk.virtualWrite(V6, flame_value);


}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode (pump1, OUTPUT);
  pinMode (light1, OUTPUT);
  pinMode (light2, OUTPUT);
  pinMode (fan, OUTPUT);

  // Sending authentication token to blynk. Getting access to your WiFi with SSID and password
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  fire_control();
  
}
void fire_control()
{
  flame_value = digitalRead(flame);

  Serial.print("Flame value= ");
  Serial.print(flame_value);
  if (flame_value ==0)
  {
    digitalWrite(pump1, LOW);

    //   delay(5000);
  }
  else
  {
    digitalWrite(pump1, HIGH);
  }
}



