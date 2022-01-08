/*
 * Arduino Named Parameters Example Code
 * Date: 2022.01.08
 * Author: Murat TAMCI
 * Web Site: www.themt.co
 * License: MIT License
 */

#include "NamedParameters.h"

NamedParameters namedParameters;

void namedParametersTest () {
  
  String sampleNamedText = "int:1|bool:true|float:3.14|string:hello word";

  Serial.println (sampleNamedText);                // print text content

  namedParameters.parse(sampleNamedText);          // parse text and convert all to key:pair
  namedParameters.print();                         // print result

  // alternative using for parsing
  NamedParameters namedParametersAlternative = NamedParameters("name:value|name2:value2");

  // result: true | return value typed bool with name "bool"
  Serial.println (namedParameters.asBool("bool", false) ? "true" : "false");

  // result: 3.14 | return value typed float with name "float"
  Serial.println (namedParameters.asFloat("float", 0.5));

  // result: -5   | because name "imInt" not exists
  Serial.println (namedParameters.asInt("imInt", -5));

  // result: setted | set value "5" | if count >= size then return false
  Serial.println (namedParameters.set("imInt", "5") ? "imInt setted" : "imInt can't set");

  // result: imInt found: 5
  namedParameters.valuePrint("imInt");

  // result: nop not found!
  namedParameters.valuePrint("nop");
}

void setup() {
  Serial.begin(9600);

  // ---

  Serial.println ("namedParametersTest");

  namedParametersTest ();
}

void loop() {
  // put your main code here, to run repeatedly:
}
