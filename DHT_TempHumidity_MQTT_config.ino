#include "DHT.h"

#define DHTPINA 2     // Digital pin connected to the DHT sensor
//#define DHTPINB 3     // Digital pin connected to the DHT sensor
//#define DHTPINC 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dhtA(DHTPINA, DHTTYPE);
//DHT dhtB(DHTPINB, DHTTYPE);
//DHT dhtC(DHTPINC, DHTTYPE);

int sensorPin0 = A0;
int sensorPin1 = A1;

// take a reading every 5 seconds then average it over the minute
int averageCounter = 0;
int averageCounterMax = 20;
int delay_ = 5000;
int do_ = 0;

String str;
void setup() {
  Serial.begin(115200);;
  dhtA.begin();
//  dhtB.begin();
//  dhtC.begin();
  Serial.println("Starting...");  
  delay(20000);
  Serial.println("CONFIGdevice_class:illuminance,name:Light_Outside,unit_of_measurement:°C,value_template:{{value_json.LightOutside|float*50/1024|int}}");
  delay(100);
  Serial.println("CONFIGdevice_class:None,name:Moisture_Outside,unit_of_measurement:Moisture,value_template:{{value_json.MoistureOutside}}");
  delay(100);
  Serial.println("CONFIGdevice_class:temperature,name:Temp_Outside,unit_of_measurement:°C,value_template:{{value_json.TempOutside}}");
  delay(100);
  Serial.println("CONFIGdevice_class:humidity,name:Humidity_Outside,unit_of_measurement:°C,value_template:{{value_json.HumidityOutside}}");

  delay(1000);
}

void loop()
{
  float hA = 0;
  float tA = 0;
  int readingA0 = 0;
  int readingA1 = 0;
  for (int i = 0; i < averageCounterMax; i++) {
    hA        += dhtA.readHumidity();
    tA        += dhtA.readTemperature();
    readingA0 += analogRead(sensorPin0);
    readingA1 += analogRead(sensorPin1);
    delay(delay_);
  }

  hA = hA/averageCounterMax;
  tA = tA/averageCounterMax;
  readingA0 = readingA0/averageCounterMax;
  readingA1 = readingA1/averageCounterMax;

  str = String("{ ");
  str += String(  "\"TempOutside\" : ") + String(tA);
  str += String(", \"HumidityOutside\" : ") + String(hA);
  str += String(", \"LightOutside\" : ") + String(readingA0);
  str += String(", \"MoistureOutside\" : ") + String(readingA1);
  str += String(" }");
  Serial.println(str);
}
