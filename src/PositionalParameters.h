/*
 * Arduino Positional Parameters
 * Description: It's parsing formatted plain text and generate data.
 *  PositionalParameters is for "0,1,2" position. You can getting data with position number
 * Version: 1.0.0 @ 2022.01.07
 * Author: Murat TAMCI
 * Web Site: www.themt.co
 * License: MIT License
 */

#ifndef _PositionalParameters_H_
#define _PositionalParameters_H_

class PositionalParameters {
    int _size = 6;
    String* items;
    int count = 0;

  public:

    PositionalParameters (int size = 6) {
      _size = size;
      items = new String[_size];
    }

    PositionalParameters (String text, int size = 6) {
      _size = size;
      items = new String[_size];
      parse (text);
    }

    void print () {
      Serial.println ("Positional Parameters");
      Serial.println ("---------------------");
      Serial.print ("count: "); Serial.println (count);
      Serial.print ("size: "); Serial.println (_size);

      Serial.println ("Items");
      Serial.println ("-----");

      for (int i = 0; i < count; i++) {
        Serial.print (i);
        Serial.print ("# \"");
        Serial.print (items[i]);
        Serial.println ("\"");
      }
    }

    void clear () {
      for (int i = 0; i < count; i++) {
        items[i] = "";
      }

      count = 0;
    }

    void valuePrint (int index) {
      if (index >= 0 && index < count) {
        Serial.print (index);
        Serial.print ("# found: \"");
        Serial.print (items[index]);
        Serial.println ("\"");
      } else {
        Serial.print (index);
        Serial.println ("# not found!");
      }
    }

    void parse (String text) {

      int pos = 0; int pos2 = 0;

      clear ();

      String column, name, value;

      while (pos < text.length()) {

        if (count >= _size) break; // if exceeded item count the size then break

        value = "";

        while (pos < text.length()) {
          value += text.charAt(pos); pos++;
          if (text.charAt(pos) == '|' && text.charAt(pos-1) != '\\') {
            pos++;
            break;
          }
        }

        items[count] = value;
        count++;
      }
    }

    int asInt (int index, int ifNotValue) {
      char* found = asCStr (index, NULL);

      if (found != NULL) {
        return atoi (found);
      }

      return ifNotValue;
    }

    float asFloat (int index, float ifNotValue) {
      char* found = asCStr (index, NULL);

      if (found != NULL) {
        return atof (found);
      }

      return ifNotValue;
    }

    bool asBool (int index, bool ifNotValue) {
      char* found = asCStr (index, NULL);

      if (found != NULL) {
        for (int i = 0, len = strlen(found); i < len; i++) {
          found[i] = tolower(found[i]);
        }

        if (strcmp (found, "true") == 0) return true;
        else if (strcmp (found, "false") == 0) return false;
      }

      return ifNotValue;
    }

    String asString (int index, const char* ifNotValue) {
      if (index >= 0 && index < count) {
        return items[index];
      }

      return ifNotValue;
    }

    const char* asCStr (int index, const char* ifNotValue) {
      if (index >= 0 && index < count) {
        return items[index].c_str();
      }

      return ifNotValue;
    }

    bool set (int index, const char* value) {
      if (index >= 0 && index < count) {
        items[index] = String (value);
        return true;
      } else if (_size - count > 0) {
        items[index] = String (value);
        count++;
        return true;
      }

      return false;
    }
};

#endif _PositionalParameters_H_
