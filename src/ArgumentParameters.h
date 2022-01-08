/*
 * Arduino Argument Parameters
 * Description: It's parsing formatted plain text and generate data.
 *  ArgumentParameters is for "-name value" pair. You can getting data with name
 * Version: 1.0.0 @ 2022.01.07
 * Author: Murat TAMCI
 * Web Site: www.themt.co
 * License: MIT License
 */

#ifndef _ArgumentParameters_H_
#define _ArgumentParameters_H_

class ArgumentParametersPair {
  public:
    String name, value;

};

class ArgumentParameters {
    int _size = 6;
    ArgumentParametersPair* items;
    int count = 0;

  public:

    ArgumentParameters (int size = 6) {
      _size = size;
      items = new ArgumentParametersPair[_size];
    }

    ArgumentParameters (String text, int size = 6) {
      _size = size;
      items = new ArgumentParametersPair[_size];
      parse (text);
    }

    void print () {
      Serial.println ("Argument Parameters");
      Serial.println ("-------------------");
      Serial.print ("count: "); Serial.println (count);
      Serial.print ("size: "); Serial.println (_size);

      Serial.println ("Items");
      Serial.println ("-----");

      for (int i = 0; i < count; i++) {
        Serial.print (i);
        Serial.print (") \"");
        Serial.print (items[i].name);
        Serial.print ("\": \"");
        Serial.print (items[i].value);
        Serial.println ("\"");
      }
    }

    void clear () {
      for (int i = 0; i < count; i++) {
        items[i].name = "";
        items[i].value = "";
      }

      count = 0;
    }

    void valuePrint (const char* name) {
      char* found = asCStr (name, NULL);

      if (found != NULL) {
        Serial.print ("\"");
        Serial.print (name);
        Serial.print ("\" found: \"");
        Serial.print (found);
        Serial.println ("\"");
      } else {
        Serial.print ("\"");
        Serial.print (name);
        Serial.println ("\" not found!");
      }
    }

    void parse (String text) {

      int pos = 0; int pos2 = 0;

      clear ();

      String column, name, value;

      while (pos < text.length()) {

        if (count >= _size) break; // if exceeded item count the size then break

        column = ""; name = ""; value = "";

        while (pos < text.length()) {
          if (text.charAt(pos) == '-'  && text.charAt(pos-1) != '\\') {
            pos++;
            break;
          }
          if (text.charAt(pos+1) == '-'  && text.charAt(pos) != '\\' && (text.charAt(pos) == ' ' || text.charAt(pos) == '\t')) {
            pos++;
            break;
          }
          column += text.charAt(pos); pos++;
        }

        pos2 = 0;

        while (pos2 < column.length()) {
          if (column.charAt(pos2) == ' ' || column.charAt(pos2) == '\t') {
            pos2++;
            break;
          }
          name += column.charAt(pos2); pos2++;
        }

        name.trim();

        if (name == "") continue;

        while (pos2 < column.length()) {
          value += column.charAt(pos2); pos2++;
        }

        items[count].name = name;
        items[count].value = value;
        count++;
      }
    }

    int asInt (const char* name, int ifNotValue) {
      char* found = asCStr (name, NULL);

      if (found != NULL) {
        return atoi (found);
      }

      return ifNotValue;
    }

    float asFloat (const char* name, float ifNotValue) {
      char* found = asCStr (name, NULL);

      if (found != NULL) {
        return atof (found);
      }

      return ifNotValue;
    }

    bool asBool (const char* name, bool ifNotValue) {
      char* found = asCStr (name, NULL);

      if (found != NULL) {
        for (int i = 0, len = strlen(found); i < len; i++) {
          found[i] = tolower(found[i]);
        }

        if (strcmp (found, "true") == 0) return true;
        else if (strcmp (found, "false") == 0) return false;
      }

      return ifNotValue;
    }

    String asString (const char* name, const char* ifNotValue) {
      for (int i = 0; i < count; i++) {
        if (items[i].name == name) {
          return items[i].value;
        }
      }

      return ifNotValue;
    }

    const char* asCStr (const char* name, const char* ifNotValue) {
      for (int i = 0; i < count; i++) {
        if (items[i].name == name) {
          return items[i].value.c_str();
        }
      }

      return ifNotValue;
    }

    bool set (const char* name, const char* value) {
      int index = _findIndex (name);
      if (index > -1) {
        items[index].value = String (value);
        return true;
      } else if (_size - count > 0) {
        items[count].name = String (name);
        items[count].value = String (value);
        count++;
        return true;
      }

      return false;
    }

  private:
    int _findIndex (const char* name) {
      for (int i = 0; i < count; i++) {
        if (items[i].name == name) {
          return i;
        }
      }

      return -1;
    }
};

#endif _ArgumentParameters_H_
