// Universum | Universum Projects > TerminalToSD

// Andrei Florian 27/MAR/2018

#include <FileIO.h>
#include <Bridge.h>
#include <BlynkSimpleYun.h>

char auth[] = "57d1e17f667e4952a4e68632229b98c3"; // insert project token
String values;
String preValues;

BLYNK_WRITE(V0) 
{
  values = param[0].asString();
}


void getAndPut()
{
  if(values == preValues)
  {
    delay(1000);
  }
  else
  {
    preValues = values;
    delay(500);
    Serial.println("Received Values");
    Serial.print("  Value   ");
    Serial.println(values);

    Serial.println("Formatting String");
    String dataString;
    dataString += values;
    Serial.println("  Success");

    Serial.println("Opening File");
    File dataFile = FileSystem.open("/mnt/sd/datalog.txt", FILE_APPEND);
  
    if(dataFile) 
    {
      Serial.println("  Success");
      Serial.println("Burning data to SD Card");
      dataFile.println(dataString);
      dataFile.close();
      Serial.println("  Success");
      Serial.print("  Printed   ");
      Serial.println(dataString);
      Serial.println("Restarting in 5 seconds");
      Serial.println("  The SD Card may be removed in this period");
    }
    else 
    {
      Serial.println("  Error - Bridge Responded with Error");
      Serial.println("Restarting in 5 seconds");
      Serial.println("  The SD Card may be removed in this period");
    }

    delay(4000);
    Serial.println("  Warning - Restarting DO NOT REMOVE SD CARD");
    Serial.println("");
    delay(1000);
  }
}


void setup()
{
  Bridge.begin();
  Serial.begin(9600);
  Blynk.begin(auth); // initialise Blynk
  while(!Serial) {};
  
  delay(500);
  Serial.println("Universum");
  delay(500);
  Serial.println("  TerminalToSD");
  delay(500);
  Serial.println("    Andrei Florian");
  delay(500);
  Serial.println("");
  Serial.println("");
  Serial.println("Loading Bridge");
  Serial.println("  This may take a while!");
  
  FileSystem.begin();
  delay(5000); // delay essential - DO NOT REMOVE
  Serial.println("  Success");
}

void loop()
{
  Blynk.run();
  getAndPut();
}

