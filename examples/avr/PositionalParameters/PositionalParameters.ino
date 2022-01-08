/*
 * Arduino Positional Parameters Example Code
 * Date: 2022.01.08
 * Author: Murat TAMCI
 * Web Site: www.themt.co
 * License: MIT License
 */

#include "PositionalParameters.h"

PositionalParameters positionalParameters;

void positionalParametersTest () {
  
  String samplePositionalText = "1|true|3.14|hello word";

  Serial.println (samplePositionalText);                     // print text content

  positionalParameters.parse(samplePositionalText);          // parse text and convert all
  positionalParameters.print();                              // print result

  // result: 1 | return value typed int with index "0"
  Serial.println (positionalParameters.asInt(0, 0));
  
  // result: true | return value typed bool with index "1"
  Serial.println (positionalParameters.asBool(1, false) ? "true" : "false");

  // result: 3.14 | return value typed float with index "2"
  Serial.println (positionalParameters.asFloat(2, 0.5));

  // result: -5   | because index "4" not exists
  Serial.println (positionalParameters.asInt(4, -5));

  // result: setted | set value "5" onto index "4" | if count >= size then return false
  Serial.println (positionalParameters.set(4, "5") ? "index 4 setted" : "index 4 can't set");

  // result: 4# found: 5
  positionalParameters.valuePrint(4);

  // result: 5# not found!
  positionalParameters.valuePrint(5);
}

void setup() {
  Serial.begin(9600);

  // ---
  
  Serial.println ("\npositionalParametersTest");

  positionalParametersTest ();
}

void loop() {
  // put your main code here, to run repeatedly:
}
