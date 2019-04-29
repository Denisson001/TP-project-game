#pragma once

#include <string>

#include <geometry.h>

class TextHelper{
public:
    static std::string convertIntToString(int value);
    static std::string convertVectorToString(Vector value);
    static std::string applyTimeFormat(int value);
    static std::string convertTimeToString(double value);
};
