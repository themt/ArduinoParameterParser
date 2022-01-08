/*
 * Arduino Argument Parameters Example Code
 * Date: 2022.01.08
 * Author: Murat TAMCI
 * Web Site: www.themt.co
 * License: MIT License
 */

#include "ArgumentParameters.h"

ArgumentParameters argumentParameters;

void argumentParametersTest () {
  
  String sampleArgumentText = "-a 5 -b true -c 1.5 -d hello word";

  Serial.println (sampleArgumentText);                // print text content

  argumentParameters.parse(sampleArgumentText);       // parse text and convert all
  argumentParameters.print();                         // print result

  // alternative using for parsing
  ArgumentParameters argumentParametersAlternative = ArgumentParameters("-a 10 -b true");

  // result: 5    | return value typed int with name "a"
  Serial.println (argumentParameters.asInt("a", -5));

  // result: true | return value typed bool with name "b"
  Serial.println (argumentParameters.asBool("b", false) ? "true" : "false");

  // result: 3.14 | return value typed float with name "c"
  Serial.println (argumentParameters.asFloat("c", 0.5));

  // result: -15  | because name "e" not exists
  Serial.println (argumentParameters.asInt("e", -15));

  // result: setted | set value "5" | if count >= size then return false
  Serial.println (argumentParameters.set("e", "5") ? "e setted" : "e can't set");

  // result: e found: 5
  argumentParameters.valuePrint("e");

  // result: nop not found!
  argumentParameters.valuePrint("nop");
}

void setup() {
  Serial.begin(9600);

  // ---

  Serial.println ("argumentParametersTest");

  argumentParametersTest ();
}

void loop() {
  // put your main code here, to run repeatedly:
}
