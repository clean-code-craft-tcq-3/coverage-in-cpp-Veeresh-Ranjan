#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "string.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(10, 10, 30) == NORMAL);
  REQUIRE(inferBreach(30, 10, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  strcpy(batteryChar.brand,"Ameron");
  checkAndAlert(TO_EMAIL, batteryChar, 46);
  BatteryCharacter batteryChar2;
  batteryChar2.coolingType = MED_ACTIVE_COOLING;
  strcpy(batteryChar2.brand,"Exide");
  checkAndAlert(TO_CONTROLLER, batteryChar2, 41);
  BatteryCharacter batteryChar3;
  batteryChar3.coolingType = MED_ACTIVE_COOLING;
  strcpy(batteryChar3.brand,"Luminous");
  checkAndAlert(TO_EMAIL, batteryChar3, 41);
  sendToEmail(TOO_HIGH);
  sendToEmail(NORMAL);
  sendToController(TOO_LOW);
}

