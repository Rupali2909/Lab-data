
#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
 
//#define WIFI_SSID       "Infinix NOTE 4"
//#define WIFI_PASS       "nygg7485"

//#define WIFI_SSID       "OPPO A9 2020"
//#define WIFI_PASS       "tripti0123"

#define WIFI_SSID       "Sourav's Pixel"
#define WIFI_PASS       "87654321"

#define IO_USERNAME    "Rupali29"
#define IO_KEY         "aio_kokG50K5W7wpsQgjQ537uY40m2z3"

// Connect to Wi-Fi and Adafruit IO handel 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
float sensorValue;
 
// Create a feed object that allows us to send data to
AdafruitIO_Feed *feed = io.feed("Labdata");
 
 void setup() {
  // put your setup code here, to run once:
 // Enable the serial port so we can see updates
  Serial.begin(115200);
  while(! Serial);
  // Connect to Adafruit IO
  io.connect();
 Serial.print("Connecting to Adafruit IO");
  // wait for a connection
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
}

long duration,distance;


 
void loop() 
{ // Always keep this at the top of your main loop
  // While not confirmed, this implies that the Adafruit IO library is not event-driven
  // This means you should refrain from using infinite loops
  io.run();
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = (sensorValue-328)*(5.0 / 1023.0);
  //float rate = ((voltage-2.541)/0.032);
  // print out the value you read:
  Serial.print(" Present Voltage at the station is: ");
  Serial.println( voltage, 4 );
  if (voltage>=2.541 && voltage<=2.5615){
    Serial.println(" Vaccant ");
    float rate=0;
    feed->save(rate);
    delay(5000);
  }
  else if (voltage < 2.541) {
    Serial.println("Discharging rate");
    float rate = ((voltage-2.541)/0.032);
    Serial.println(rate);
    feed->save(rate);
     delay(5000);
  }else if (voltage > 2.5615){
    Serial.println("Charging rate");
    float rate = ((voltage-2.5615)/0.032);
    Serial.println(rate);
    feed->save(rate);
    delay(5000);
  }
 
  // This is so we can see some response on the computer
//  Serial.println( rate, 4 );
  // Send 10 to our Workshop Voltage Feed
 // feed->save(rate);
 
  // DONT SEND A BILLION DATA POINTS! This slows down the program so that it sends readings once every 10 seconds
 // delay(10000);
}
\
