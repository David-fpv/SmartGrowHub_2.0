#pragma once

class SensorInfo
{
private:
    int   sensor_id_;
    char  type_[20];
    char  unit_[8];
    float (*function_)();

public:
    SensorInfo();
    SensorInfo(int sensor_id, const char* type, const char* unit, float (*function)());

    int         GetSensorId() const;
    const char* GetType()     const;
    const char* GetUnit()     const;
    float       GetValue()    const;
};
