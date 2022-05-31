#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "string.h"

TEST_CASE("infers the breach according to limits") {
  cout<<"Infer breach"<<endl;
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(10, 10, 30) == NORMAL);
  REQUIRE(inferBreach(30, 10, 30) == NORMAL);

  cout<<"classifyTemperatureBreach"<<endl;
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -3) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 48) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45) == NORMAL);

  cout<<"checkAndAlert"<<endl;
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  strcpy(batteryChar.brand,"Ameron");
  AlertEmail alertEmailObj;
  checkAndAlert(&alertEmailObj, batteryChar, 46);
  REQUIRE(alertEmailObj.getPrintMailForTooHigh() == true);

  BatteryCharacter batteryChar2;
  batteryChar2.coolingType = MED_ACTIVE_COOLING;
  strcpy(batteryChar2.brand,"Exide");
  AlertController alertCtrlObj1;
  checkAndAlert(&alertCtrlObj1, batteryChar2, 41);
  REQUIRE(alertCtrlObj1.getPrintController() == true);

  BatteryCharacter batteryChar3;
  batteryChar3.coolingType = PASSIVE_COOLING;
  strcpy(batteryChar3.brand,"Luminous");
  AlertEmail alertEmailObj2;
  checkAndAlert(&alertEmailObj2, batteryChar3, -1);
  REQUIRE(alertEmailObj2.getPrintMailForTooLow() == true);

  cout<<"sendToEmail"<<endl;
  AlertEmail alertEmailObj3;
  alertEmailObj3.sendAlert(NORMAL);
  REQUIRE(alertEmailObj3.getPrintMailForTooHigh() == false);
  REQUIRE(alertEmailObj3.getPrintMailForTooLow() == false);
  alertEmailObj3.sendAlert(TOO_HIGH);
  REQUIRE(alertEmailObj3.getPrintMailForTooHigh() == true);
  alertEmailObj3.sendAlert(TOO_LOW);
  REQUIRE(alertEmailObj3.getPrintMailForTooLow() == true);

  cout<<"sendToController"<<endl;
  AlertController alertCtrlObj2;
  alertCtrlObj2.sendAlert(TOO_LOW);
  REQUIRE(alertCtrlObj2.getPrintController() == true);
}

