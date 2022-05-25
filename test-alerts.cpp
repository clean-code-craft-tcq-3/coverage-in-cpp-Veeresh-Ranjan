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
  checkAndAlert(TO_EMAIL, batteryChar, 46);
  REQUIRE(isPrintMailForTooHigh == true);

  BatteryCharacter batteryChar2;
  batteryChar2.coolingType = MED_ACTIVE_COOLING;
  strcpy(batteryChar2.brand,"Exide");
  checkAndAlert(TO_CONTROLLER, batteryChar2, 41);
  REQUIRE(isPrintController == true);

  BatteryCharacter batteryChar3;
  batteryChar3.coolingType = PASSIVE_COOLING;
  strcpy(batteryChar3.brand,"Luminous");
  checkAndAlert(TO_EMAIL, batteryChar3, -1);
  REQUIRE(isPrintMailForTooLow == true);

  clearflags();
  REQUIRE(isPrintMailForTooHigh == false);
  REQUIRE(isPrintController == false);
  REQUIRE(isPrintMailForTooLow == false);

  cout<<"sendToEmail"<<endl;
  sendToEmail(NORMAL);
  REQUIRE(isPrintMailForTooHigh == false);
  REQUIRE(isPrintMailForTooLow == false);
  sendToEmail(TOO_HIGH);
  REQUIRE(isPrintMailForTooHigh == true);
  sendToEmail(TOO_LOW);
  REQUIRE(isPrintMailForTooLow == true);

  cout<<"sendToController"<<endl;
  sendToController(TOO_LOW);
  REQUIRE(isPrintController == true);
  clearflags();
}

