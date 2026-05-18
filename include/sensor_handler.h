#pragma once

#include "sensor_reading.h"
#include "sensor_info.h"
#include "sensor_functions.h"

static constexpr uint8_t MAX_SENSORS = 8;

class SensorHandler
{
public:
    SensorHandler();

    void          addSensorInfo(const SensorInfo& sensor);
    SensorReading getReading(int sensor_id) const;
    uint8_t       getCount()               const { return count_; }
    const SensorInfo& getSensor(uint8_t i) const { return sensors_[i]; }

private:
    SensorInfo sensors_[MAX_SENSORS];
    uint8_t    count_;
};
