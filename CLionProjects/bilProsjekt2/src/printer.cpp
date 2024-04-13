#include "printer.hpp"

void printer::setPoints(uint16_t values[15]) {
    doc["0"] = values[0];
    doc["1"] = values[1];
    doc["2"] = values[2];
    doc["3"] = values[3];
    doc["4"] = values[4];
    doc["5"] = values[5];
    doc["6"] = values[6];
    doc["7"] = values[7];
    doc["8"] = values[8];
    doc["9"] = values[9];
    doc["10"] = values[10];
    doc["11"] = values[11];
    doc["12"] = values[12];
    doc["13"] = values[13];
    doc["14"] = values[14];
}

void printer::print() {
    serializeJson(doc, Serial);
    Serial.println();
    delay(10);
}

void printer::printSerial() {
    Serial.print(int(doc["0"]));
    Serial.print(" | ");
    Serial.print(int(doc["5"]));
    Serial.print(" | ");
    Serial.print(int(doc["6"]));
    Serial.print(" | ");
    Serial.print(int(doc["7"]));
    Serial.print(" | ");
    Serial.print(int(doc["8"]));
    Serial.print(" | ");
    Serial.print(int(doc["9"]));
    Serial.print(" | ");
    Serial.print(int(doc["10"]));
    Serial.print(" | ");
    Serial.print(int(doc["11"]));
    Serial.print(" | ");
    Serial.print(int(doc["12"]));
    Serial.print(" | ");
    Serial.print(int(doc["13"]));
    Serial.print(" | ");
    Serial.print(int(doc["14"]));
    Serial.println();
    delay(10);
}
