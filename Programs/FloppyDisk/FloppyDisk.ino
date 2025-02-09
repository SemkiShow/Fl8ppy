// #include "ArduinoFDC.h"

#define PIN_DENSITY   13
#define PIN_INDEX      7
#define PIN_MOTORA     4 
#define PIN_SELECTB   A1
#define PIN_SELECTA    5 
#define PIN_MOTORB    A0
#define PIN_STEPDIR    3 
#define PIN_STEP       2 
#define PIN_WRITEDATA  9
#define PIN_WRITEGATE 10
#define PIN_TRACK0    11 
#define PIN_WRITEPROT 12
#define PIN_READDATA   8
#define PIN_SIDE       6 
#define PIN_DSKCHG    A2

/*void DebugInfo()
{
  Serial.print("Selected drive: ");
  Serial.println(ArduinoFDC.selectedDrive());
  Serial.print("Drive type: ");
  Serial.println(ArduinoFDC.getDriveType());
  Serial.print("Tracks: ");
  Serial.println(ArduinoFDC.numTracks());
  Serial.print("Sectors: ");
  Serial.println(ArduinoFDC.numSectors());
  Serial.print("Heads: ");
  Serial.println(ArduinoFDC.numHeads());
  Serial.print("Have disk: ");
  Serial.println(ArduinoFDC.haveDisk());
  Serial.print("Write protected: ");
  Serial.println(ArduinoFDC.isWriteProtected());
  Serial.print("Motor running: ");
  Serial.println(ArduinoFDC.motorRunning());
  Serial.println("----------");
}*/

void digitalWriteOC(byte pin, byte state) 
{ if( state==LOW ) pinMode(pin, OUTPUT); else pinMode(pin, INPUT); }

void PinInit()
{
  digitalWrite(PIN_STEP,      LOW);
  digitalWrite(PIN_STEPDIR,   LOW);
  digitalWrite(PIN_MOTORA,    LOW);
  digitalWrite(PIN_SELECTA,   LOW);
#if defined(PIN_MOTORB) && defined(PIN_SELECTB)
  digitalWrite(PIN_MOTORB,    LOW);
  digitalWrite(PIN_SELECTB,   LOW);
#endif
  digitalWrite(PIN_SIDE,      LOW);
  digitalWrite(PIN_WRITEGATE, LOW);
  digitalWrite(PIN_WRITEDATA, HIGH);

  // set pins to input/output mode
  pinMode(PIN_STEP,      INPUT);
  pinMode(PIN_STEPDIR,   INPUT);
  pinMode(PIN_SELECTA,   INPUT);
  pinMode(PIN_MOTORA,    INPUT);
#if defined(PIN_MOTORB) && defined(PIN_SELECTB)
  pinMode(PIN_SELECTB,   INPUT);
  pinMode(PIN_MOTORB,    INPUT);
#endif
  pinMode(PIN_SIDE,      INPUT);
  pinMode(PIN_WRITEGATE, INPUT);
  pinMode(PIN_WRITEDATA, OUTPUT);
  pinMode(PIN_READDATA,  INPUT_PULLUP);
  pinMode(PIN_INDEX,     INPUT_PULLUP);
  pinMode(PIN_TRACK0,    INPUT_PULLUP);
#if defined(PIN_WRITEPROT)
  pinMode(PIN_WRITEPROT, INPUT_PULLUP);
#endif
#if defined(PIN_DSKCHG)
  pinMode(PIN_DSKCHG,    INPUT_PULLUP);
#endif

#if defined(PIN_DENSITY)
  digitalWrite(PIN_DENSITY, LOW);
  pinMode(PIN_DENSITY, INPUT);
#endif
}

void PinControl()
{
  Serial.print("Enter pin(floppy pin/r): ");
  while (Serial.available() == 0) {}
  String input = Serial.readString();
  input.trim();
  Serial.print(input);
  Serial.println();

  String stateString = "custom";
  byte stateBool = LOW;
  if (input != "20" && input != "r")
  {
    Serial.print("Enter state(0/1): ");
    while (Serial.available() == 0) {}
    stateString = Serial.readString();
    stateString.trim();
    Serial.print(stateString);
    if (stateString == "0")
    {
      stateBool = LOW;
    }
    if (stateString == "1")
    {
      stateBool = HIGH;
    }
    Serial.println();
  }
  
  String pulsesString = "";
  int pulsesInt = 0;
  if (input == "20")
  {
    Serial.print("Enter pulses amount: ");
    while (Serial.available() == 0) {}
    pulsesString = Serial.readString();
    stateString.trim();
    Serial.print(pulsesString);
    pulsesInt = pulsesString.toInt();
  }
  
  if (input == "10")
  {
    // Serial.println("Starting up the motor...");
    digitalWriteOC(PIN_MOTORA, stateBool);
    // digitalWrite(PIN_MOTORA, LOW);
  }
  if (input == "12")
  {
    digitalWriteOC(PIN_SELECTB, stateBool);
  }
  if (input == "14")
  {
    digitalWriteOC(PIN_SELECTA, stateBool);
  }
  if (input == "16")
  {
    // Serial.println("Starting up the motor...");
    digitalWriteOC(PIN_MOTORB, stateBool);
    // digitalWrite(PIN_MOTORA, LOW);
  }
  if (input == "18")
  {
    digitalWriteOC(PIN_STEPDIR, stateBool);
  }
  if (input == "20")
  {
    for (int i = 0; i < pulsesInt; i++)
    {
      digitalWriteOC(PIN_STEP, !digitalRead(PIN_STEP));
      delay(50);
      digitalWriteOC(PIN_STEP, !digitalRead(PIN_STEP));
      delay(50);
    }
  }
  if (input == "24")
  {
    digitalWrite(PIN_WRITEGATE, stateBool);
  }
  if (input == "r")
  {
    digitalWriteOC(PIN_SELECTA, LOW);
    digitalWrite(PIN_WRITEGATE, LOW);
    digitalWriteOC(PIN_MOTORA, LOW);
  }
  Serial.print("Pin ");
  Serial.print(input);
  Serial.print(" is set to ");
  Serial.println(stateString);
}

void setup()
{
  // ArduinoFDC.begin();
  Serial.begin(115200);
  // pinMode(PIN_SELECTA, OUTPUT);
  PinInit();

  // digitalWriteOC(PIN_SELECTA, HIGH);
  // digitalWrite(PIN_WRITEGATE, LOW);
  // digitalWriteOC(PIN_MOTORA, LOW);

  // pinMode(4, OUTPUT);
  // digitalWrite(4, LOW);
  // ArduinoFDC.setDriveType(ArduinoFDCClass::DT_3_HD);
  // ArduinoFDC.setDensityPinMode(ArduinoFDCClass::DP_OUTPUT_LOW_FOR_HD);
  // ArduinoFDC.selectDrive(0);
  // DebugInfo();
  // ArduinoFDC.motorOn();
  

  // Serial.println(ArduinoFDC.motorRunning());
}

void loop()
{
  // Serial.println(ArduinoFDC.haveDisk());
  // DebugInfo();
  // if (Serial.available() > 0)
  // {
  //   PinControl();
  // }
  PinControl();

  // Serial.print("ReadData(30):");
  // Serial.print(digitalRead(PIN_READDATA));
  // Serial.print(",");
  // Serial.print("Track0(26):");
  // Serial.print(digitalRead(PIN_TRACK0));
  // Serial.print(";");
  // Serial.println();

  // delay(10);
  // digitalWrite(13, HIGH);
  // delay(500);
  // digitalWrite(13, LOW);
  // delay(500);
}
