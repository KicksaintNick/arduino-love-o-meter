// Temperature settings
int temperaturePin = A0; // We connect the temperature sensor to Analog 0
float ambientTemperature = 25.68; // This is the temperature value for the environment. This needs to be defined by the user
int lowTemp = 1;
int midTemp = 2;
int highTemp = 3;

// LED pins are defined here in accordance with the breadboard setup
int LED1 = 11;
int LED2 = 12;
int LED3 = 13;

void setup() {
  Serial.begin(9600); // We need to listen to the Arduino using the Serial monitor to see measurements from the temperature sensor

  // LED setup
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, LOW);
}

/*
* I've left the loop functionality here the same as whats provided in the Arduino Starter Kit, 
* the only thing to note here that might differ for other users is that the temperature sensor 
* I'm using as a 500 mV offset and that needs to be accounted for in the equation
*/
void loop() {
   // read the value on the temperature AnalogIn pin
  // and store it in a variable
  int sensorVal = analogRead(temperaturePin);

  // send the 10-bit sensor value out the serial port
  Serial.print("sensor Value: ");
  Serial.print(sensorVal);

  // convert the ADC reading to voltage
  float voltage = (sensorVal / 1024.0) * 5.0;

  // Send the voltage level out the Serial port
  Serial.print(", Volts: ");
  Serial.print(voltage);

  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((voltage - 500mV) times 100)
  Serial.print(", degrees C: ");
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);

  // if the current temperature is lower than the ambient temperature
  // turn off all LEDs
  if (temperature < ambientTemperature + lowTemp) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } // if the temperature rises between low and mid temp, turn an LED on
  else if (temperature >= ambientTemperature + lowTemp && temperature < ambientTemperature + midTemp) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } // if the temperature rises mid and high temp, turn a second LED on
  else if (temperature >= ambientTemperature + midTemp && temperature < ambientTemperature + highTemp) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  } // if the temperature rises more than high temp, turn all LEDs on
  else if (temperature >= ambientTemperature + highTemp) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  }
  delay(1);
}
