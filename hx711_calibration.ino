#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
double m;
double b;
double y0;
double y1;
double x0;
double x1;



HX711 scale;

void setup() {
  y0=0.0;
  y1=0.314;
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  delay(5000);
  if (scale.is_ready()) {
   long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }
  Serial.println("Remove Weight");
  delay(5000);
  x0=scale.get_units(10);
  Serial.println(x0);
  Serial.println("Place Weight");
  delay(5000);
  
  x1 = scale.get_units(10);
  Serial.println(x1);
  m=(y1-y0)/(x1-x0);
  b=((y0*x1)-(y1*x0))/(x1-x0);
  Serial.println("Scale Ready");
}

void loop() {

  if (scale.is_ready()) {
    double reading = scale.get_units(5);
    reading = (m*reading+b)*1000.0;
    
    
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(100);
  
}
