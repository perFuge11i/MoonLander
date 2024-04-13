#ifndef BILPROSJEKT2_PRINTER_HPP
#define BILPROSJEKT2_PRINTER_HPP

#include "Arduino.h"
#include "ArduinoJson.h"

class printer{
    JsonDocument doc;
public:
    void setPoints(uint16_t values[15]);
    void print();
    void printSerial();
};
#endif //BILPROSJEKT2_PRINTER_HPP
