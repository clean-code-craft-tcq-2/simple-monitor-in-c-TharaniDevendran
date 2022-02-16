#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define Min_Temperature 0
#define Max_Temperature 45
#define Min_soc 20
#define Max_soc 80
#define Min_ChargeRate 0
#define Max_ChargeRate 0.8

#define TEMP_WARNING_TOLERANCE  4
#define SOC_WARNING_TOLERANCE   4
#define CHARGERATE_WARNING_TOLERANCE  (float)0.2

#define LANGUAGE ENGLISH

#if(LANGUAGE == ENGLISH)
const char *Notify[] ={"TEMPERATURE ALERT",
                     "SOC ALERT",
                     "CHARGE ALERT"
                    };
const char *Warning[] ={"TEMPERATURE OUT OF RANGE",
                     "SOC OUT OF RANGE ",
                     "CHARGE RATE TOO LOW"
                    };
#elif(LANGUAGE == GERMAN)
const char *Notify[] ={"TEMPERATURALARM",
                     "SOC-ALARM",
                     "LADEZAHLALARM"
                    };
const char *Warning[] ={"TEMPERATUR AUSSERHALB DES BEREICHS",
                     "SOC AUSSERHALB DER REICHWEITE",
                     "LADESTUFE ZU NIEDRIG"
                    };
#endif

void Display(char *DisplayText)
{
  if(DisplayText != NULL)
    printf("%s \n", DisplayText);
}

bool TemperatureAlarmCheck(float temperature)
{
	if((Min_Temperature + TEMP_WARNING_TOLERANCE ) > temperature || (Max_Temperature - TEMP_WARNING_TOLERANCE ) < temperature)
	{
		Display (Warning[0]);
		return true;
	}
	else
	{
		return false;
	}	
}

bool TemperatureWarningCheck(float temperature)
{
	if((Min_Temperature > temperature) || (Max_Temperature < temperature))
	{
		Display (Notify[0]);
		return true;
	}
	else
	{
		return false;
	}	
}

bool socAlarmCheck(float soc)
{
	if((Min_soc + SOC_WARNING_TOLERANCE ) > soc || (Max_soc  - SOC_WARNING_TOLERANCE ) < soc)
	{
		Display (Warning[1]);
		return true;
	}
	else
	{
		return false;
	}	
}

bool socWarningCheck(float soc)
{
	if((Min_soc  > soc) || (Max_soc < soc))
	{
		Display (Notify[1]);
		return true;
	}
	else
	{
		return false;
	}	
}

bool chargeRateAlarmCheck(float chargerate)
{
	if((Min_ChargeRate + CHARGERATE_WARNING_TOLERANCE ) > temperature || (Max_ChargeRate  - CHARGERATE_WARNING_TOLERANCE ) < temperature)
	{
		Display (Warning[2]);
		return true;
	}
	else
	{
		return false;
	}	
}

bool chargeRateWarningCheck(float chargerate)
{
	if((Min_ChargeRate > chargerate) || (Max_ChargeRate < chargerate))
	{
		Display (Notify[2]);
		return true;
	}
	else
	{
		return false;
	}	
}
bool TemperatureCheck (float temperature, bool (*PrintTemperatureWarning)(float), bool (*PrintTemperatureAlarm)(float))
{
  if (PrintTemperatureWarning (temperature))
	{
		return true;
	}
   else
	{
		return (PrintTemperatureAlarm(temperature));
	}

}

bool socCheck (float soc, bool (*PrintSocWarning)(float), bool (*PrintSocAlarm)(float))
{
  if (PrintSocWarning (soc))
	{
		return true;
	}
   else
	{
		return (PrintSocAlarm(soc));
	}

}

bool chargeRateCheck (float chargeRate, bool (*PrintChargeRateWarning)(float), bool (*PrintChargeRateAlarm)(float))
{
  if (PrintChargeRateWarning (soc))
	{
		return true;
	}
   else
	{
		return (PrintChargeRateAlarm(soc));
	}

}

bool 
                    
bool BatteryIsNOk (float temperature, float soc, float ChargeRate)
{
  bool val = TemperatureCheck (temperature, TemperatureWarningCheck, TemperatureAlarmCheck);
  val = val || socCheck (soc, socWarningCheck, socAlarmCheck);
  val = val || chargeRateCheck (ChargeRate, chargeRateWarningCheck, chargeRateAlarmCheck);
}

void TestCheckBatteryIsNOk (bool expectedstatus, float Temperature, float soc, float ChargeRate)
{
  bool teststatus = BatteryIsNOk(Temperature, soc, ChargeRate);
  assert(teststatus == expectedstatus);
}

int main() 
{
 
  TestCheckBatteryIsNOk(0, 25, 70, 0.7);
  TestCheckBatteryIsNOk(1, 50, 85, 0);
  
  return 0;
}
