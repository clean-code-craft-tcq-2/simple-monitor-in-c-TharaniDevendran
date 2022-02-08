#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define Min_Temperature 0
#define Max_Temperature 45
#define Min_soc 20
#define Max_soc 80
#define Min_ChargeRate 0
#define Max_ChargeRate 0.8

void Display(char *DisplayText)
{
  if(DisplayText != NULL)
    printf("%s \n", DisplayText);
}

bool CheckValueOutOfRange (float input, float MinThreshold, float MaxThreshold)
{
  return (input < MinThreshold || input > MaxThreshold);
}

bool TemperatureRangeCheck (float temperature)
{
  bool TemperaturStatus = CheckValueOutOfRange (temperature, (float) Min_soc, (float) Max_soc);
  if(TemperaturStatus)
    Display("Temperature out of range!");
  return TemperaturStatus;
}

bool socRangeCheck (float soc)
{
  bool socStatus = CheckValueOutOfRange (soc, (float) Min_ChargeRate, (float) Max_ChargeRate);
  if(socStatus)
    Display("State of Charge out of range!");
  return socStatus;
}

bool chargeRateCheck (float chargeRate)
{
  bool chargeRateStatus = CheckValueOutOfRange (chargeRate, (float) Min_Temperature, (float) Max_Temperature);
  if(chargeRateStatus)
    Display("Charge Rate out of range!");
  return chargeRateStatus;
}

bool BatteryIsOk (float temperature, float soc, float ChargeRate)
{
  return (TemperatureRangeCheck(temperature) || socRangeCheck (soc) || chargeRateCheck(ChargeRate));
}

void TestCheckBatteryIsOk (float Temperature, float soc, float ChargeRate, bool expectedstatus)
{
  bool teststatus = BatteryIsOk(Temperature, soc, ChargeRate);
  assert(teststatus == expectedstatus);
}

void TestCheckValueOutOfRange (bool expectedstatus, float testInput, float testMinThreshold, float testMaxThreshold)
{
  bool teststatus = CheckValueOutOfRange(testInput, testMinThreshold, testMaxThreshold);
  assert(teststatus == expectedstatus);
}

int main() 
{
  TestCheckValueOutOfRange(0, 25, 20, 22);
  TestCheckValueOutOfRange(1, 21, 20, 22);
  
  TestCheckBatteryIsOk(0, 25, 70, 0.7);
  TestCheckBatteryIsOk(1, 50, 85, 0);
  
  return 0;
}
