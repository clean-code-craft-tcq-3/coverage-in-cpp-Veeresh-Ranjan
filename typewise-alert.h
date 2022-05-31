#pragma once
#include "type-defines.h"

class AlertTheTarget{
public:
    AlertTheTarget(){
    }
    void virtual sendAlert(BreachType breachType)=0;
};
class AlertEmail : public AlertTheTarget{
    bool isPrintMailForTooLow, isPrintMailForTooHigh;
public:
    void sendMailAlert(BreachType breachType);
    void sendAlert(BreachType breachType);
    bool getPrintMailForTooHigh(){
        return isPrintMailForTooHigh;
    }
    bool getPrintMailForTooLow(){
        return isPrintMailForTooLow;
    }
    ~AlertEmail(){
        isPrintMailForTooLow = isPrintMailForTooHigh = 0;
    }
};
class AlertController : public AlertTheTarget{
    bool isPrintController;
public:
    void sendAlert(BreachType breachType);
    bool getPrintController(){
        return isPrintController;
    }
    ~AlertController(){
        isPrintController = 0;
    }
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

void checkAndAlert(
  AlertTheTarget *alertTarget, BatteryCharacter batteryChar, double temperatureInC);

