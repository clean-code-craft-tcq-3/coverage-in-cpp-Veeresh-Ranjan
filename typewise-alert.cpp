#include "typewise-alert.h"
#include <stdio.h>
bool isPrintMailForTooLow = false, isPrintMailForTooHigh = false, isPrintController = false;

void clearflags(){
    isPrintMailForTooLow = false, isPrintMailForTooHigh = false, isPrintController = false;
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void getThresholdsActive(CoolingType coolingType, int &lowerLimit, int &upperLimit){
    if (coolingType == HI_ACTIVE_COOLING){
        lowerLimit = 0;
        upperLimit = 45;
    }
    else //if MED_ACTIVE_COOLING
    {
        lowerLimit = 0;
        upperLimit = 40;
    }
}

void getThresholds(CoolingType coolingType, int &lowerLimit, int &upperLimit){
    if (coolingType == PASSIVE_COOLING){
        lowerLimit = 0;
        upperLimit = 35;
    }
    else (getThresholdsActive(coolingType,lowerLimit,upperLimit));
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;

  getThresholds(coolingType,lowerLimit,upperLimit);
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void sendAlert(AlertTarget alertTarget,BreachType breachType){
  if (alertTarget == TO_CONTROLLER){
        sendToController(breachType);
  }
  else
  {
      sendToEmail(breachType);
  }
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );
  sendAlert(alertTarget,breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  isPrintController = true;
}

void sendMailAlert(BreachType breachType){
    const char* recepient = "a.b@c.com";
    if (breachType == TOO_LOW){
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too low\n");
        isPrintMailForTooLow = true;
    }
    else
    {
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too high\n");
        isPrintMailForTooHigh = true;
    }
}

void sendToEmail(BreachType breachType) {
  if (!breachType == NORMAL){
    sendMailAlert(breachType);
  }
}

