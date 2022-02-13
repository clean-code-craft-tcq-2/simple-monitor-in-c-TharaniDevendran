#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define Min_Temperature 0
#define Max_Temperature 45
#define Min_soc 20
#define Max_soc 80
#define Min_ChargeRate 0
#define Max_ChargeRate 0.8

char TemperatureWarning[] = ""Temperature out of range!";
char socWarning[] = "State of Charge out of range!";
char chargeRateWarning[] = "Charge Rate out of range!" ;

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
  bool TemperaturStatus = CheckValueOutOfRange (temperature, (float) Min_Temperature, (float) Max_Temperature);
  return TemperaturStatus;
}

bool socRangeCheck (float soc)
{
  bool socStatus = CheckValueOutOfRange (soc, (float) Min_soc, (float) Max_soc);
  return socStatus;
}

bool chargeRateCheck (float chargeRate)
{
  bool chargeRateStatus = CheckValueOutOfRange (chargeRate, (float) Min_ChargeRate, (float) Max_ChargeRate);
  return chargeRateStatus;
}

bool BatteryValueIsNOk (float value, bool (*RangeCheck) (float), char *warning)
{
  bool val = RangeCheck(value);
  if (!val)
     Display(warning);
  return val;
}
                         
bool BatteryIsNOk (float temperature, float soc, float ChargeRate)
{
  bool val = BatteryValueIsNOk(temperature, TemperatureRangeCheck, TemperatureWarning);
  val = val || BatteryValueIsNOk(soc, socRangeCheck, socWarning);
  val = val || BatteryValueIsNOk(ChargeRate, chargeRateCheck, chargeRateWarning);
}

void TestCheckBatteryIsNOk (bool expectedstatus, float Temperature, float soc, float ChargeRate)
{
  bool teststatus = BatteryIsNOk(Temperature, soc, ChargeRate);
  assert(teststatus == expectedstatus);
}

void TestCheckValueOutOfRange (bool expectedstatus, float testInput, float testMinThreshold, float testMaxThreshold)
{
  bool teststatus = CheckValueOutOfRange(testInput, testMinThreshold, testMaxThreshold);
  assert(teststatus == expectedstatus);
}

int main() 
{
  TestCheckValueOutOfRange(1, 25, 20, 22);
  TestCheckValueOutOfRange(0, 21, 20, 22);
  
  TestCheckBatteryIsNOk(0, 25, 70, 0.7);
  TestCheckBatteryIsNOk(1, 50, 85, 0);
  
  return 0;
}
