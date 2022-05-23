#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "string.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  strcpy(batteryChar.brand,"Ameron");
  checkAndAlert(TO_EMAIL, batteryChar, 46);
  BatteryCharacter batteryChar2;
  batteryChar2.coolingType = MED_ACTIVE_COOLING;
  strcpy(batteryChar2.brand,"Exide");
  checkAndAlert(TO_CONTROLLER, batteryChar2, 41);
  sendToEmail(TOO_HIGH);
  sendToController(TOO_LOW);
}

