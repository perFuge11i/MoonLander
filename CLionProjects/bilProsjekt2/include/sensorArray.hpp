#ifndef BILPROSJEKT2_SENSORARRAY_HPP
#define BILPROSJEKT2_SENSORARRAY_HPP

#include "QTRSensors.h"

class sensorArray {
private:
    uint8_t numSensors;
    QTRSensors qtr;
public:
    sensorArray(uint8_t numSensors_);
    void read();
};
#endif //BILPROSJEKT2_SENSORARRAY_HPP
