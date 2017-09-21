/*
 * Owner:   Hazmei Bin Abdul Rahman
 * Module:  CG3002 (Embedded Systems Project)
 * Date:    18 SEPTEMBER 2017
 * 
 * Code is referenced from:
 * Voltage - https://startingelectronics.org/articles/arduino/measuring-voltage-with-arduino/
 * Current - https://learn.sparkfun.com/tutorials/ina169-breakout-board-hookup-guide
 */

#define VOLT_REF 5
#define NUM_SAMPLES 10

// Constants
const int INA169_OUT = A0;    // Input pin for measuring Vout
const int VOLT_PIN = A1;      // Input pin for measuring Vin
const float RS = 0.09;        // Shunt resistor value (in ohms, calibrated)
const int RL = 10;            // Load resistor value (in ohms)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sumCount = 0;
  int voltSumVal;     // Variable to store value from analog read
  int ina169SumVal;   // Variable to store value from analog read
  
  float voltAvgVal;
  float ina169AvgVal;
  float current;     // Calculated current value
  float voltage;     // Calculated voltage value
  float power;        // Calculated power value

  pinMode(VOLT_PIN,INPUT);
  pinMode(INA169_OUT,INPUT);
  
  // take a number of analog samples and add them up
  while(sumCount < NUM_SAMPLES){
    ina169SumVal += analogRead(INA169_OUT);
    voltSumVal += analogRead(VOLT_PIN);
    sumCount++;
    delay(10);
  }
  
  // Remap the ADC value into a voltage number (5V reference)
  ina169AvgVal = (((float)ina169SumVal / NUM_SAMPLES) * VOLT_REF) / 1023.0;
  voltAvgVal = (((float)voltSumVal / NUM_SAMPLES) * VOLT_REF) / 1023.0;
  
  // Follow the equation given by the INA169 datasheet to
  // determine the current flowing through RS.
  // Is = (Vout x 1k) / (RS x RL)
  current = ina169AvgVal / (RS * RL);

  // voltage multiplied by 1.44 when using voltage divider that 
  // divides by 1.44. 1.4706 is the calibrated value
  voltage = voltAvgVal * 1.4706;

  power = voltage * current;
  
  Serial.print("Current: ");
  Serial.print(current, 3);
  Serial.print(" A, Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V, Power: ");
  Serial.print(power, 3);
  Serial.println(" W");  
  delay(500);
}
