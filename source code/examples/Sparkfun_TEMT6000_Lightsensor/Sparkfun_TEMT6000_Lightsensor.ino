// Example Sketch for Sparkfun TEMT6000 Module (Light Dependent Photo Transistor).
// It reads the voltage at the OUT Pin and displays it on the console. The value should
// range from 0 to 1024. The lower the value the lower the light. The higher 
// the value means more light being received by the LDR.
// Written by cactus.io. For more details and how to hookup the Sparkfun TEMT6000 module to
// the Arduino then visit this link.
// http://cactus.io/hookups/sensors/light/temt6000/hookup-arduino-to-sparkfun-temt6000-light-sensor-module

int OUT_Pin = A1;
 
void setup() {
    Serial.begin(9600);
    Serial.println("Sparkfun TEMT6000 Module Example Sketch | cactus.io");
}
 
void loop() {
   Serial.println(analogRead(OUT_Pin));
   delay(500);
}
