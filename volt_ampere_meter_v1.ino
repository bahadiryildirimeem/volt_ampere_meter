/* SIMPLE AMPERE-VOLT METER 
 *  
 *  Written by Bahadir YILDIRIM
 *  
 *  This project is measuring voltage and ampere.
 *  Max input voltage: 0V - 10V
 *  Max input ampere : 0A - 20A
 *  
 */
 #define BUTTON  2
 #define RUN_LED  3
 #define CURRENT_MODE_LED  4
 #define CURRENT_SENSE  A0
 #define VOLTAGE_SENSE  A1
 #define SIGNAL  8

 unsigned long counter = 0;
 bool modeChanger = 0, modeShow = 0, measuringShow = 0, toggle = 0;
 uint16_t voltageRaw = 0, currentRaw = 0;
 float voltage = -1, current = -1, sameVal = 0;

void setup() {
  
  /* Defining INPUT and OUTPUTS */
  
  pinMode(BUTTON, INPUT);
  pinMode(RUN_LED, OUTPUT);
  pinMode(CURRENT_MODE_LED, OUTPUT);
  pinMode(SIGNAL, OUTPUT);
  Serial.begin(9600);
  Serial.println("Welcome!");
  delay(2000);
  Serial.println("Setting up...");
  delay(3000);
  
}

void loop() {

/* RUN LED is blinking */
  if((millis() - counter ) > 500)
  {
    counter = millis();
    if(toggle == 0)
    {
      digitalWrite(RUN_LED, HIGH);
      toggle = 1;
    }
    else
    {
      digitalWrite(RUN_LED, LOW);
      toggle = 0;
    }
  }
  
  /* Selecting MODES */
  if(digitalRead(BUTTON) == 0)
  {
    while(!digitalRead(BUTTON));
    modeShow = 0;
    if(modeChanger == 0)
      modeChanger = 1;
    else
      modeChanger = 0;
  }

  
  /* Voltage Measuring MODE */ 
  if(modeChanger == 0)
  {
    digitalWrite(CURRENT_MODE_LED, LOW);
    digitalWrite(SIGNAL, LOW);
    if(modeShow == 0)
    {
      Serial.println("Voltage Measuring MODE");
      modeShow = 1;
    }
    
    voltageRaw = analogRead(VOLTAGE_SENSE);
    voltage = voltageRaw * 0.0048828 * 3.12765;
    if(voltage != sameVal)
    {
      Serial.print("Voltage: ");
      Serial.print(voltage);
      Serial.println("V");
      sameVal = voltage;
    }
    
  }
  /* Current Measuring MODE */ 
  if(modeChanger == 1)
  {
    digitalWrite(CURRENT_MODE_LED, HIGH);
    digitalWrite(SIGNAL, HIGH);
    if(modeShow == 0)
    {
      Serial.println("Current Measuring MODE ");
      modeShow = 1;
      currentRaw = analogRead(CURRENT_SENSE);
      current = currentRaw * 0.024414;
      if(current != sameVal)
      {
        Serial.print("Current: ");
        Serial.print(current);
        Serial.println("A");
        sameVal = current;
      }
    }
  }

}
