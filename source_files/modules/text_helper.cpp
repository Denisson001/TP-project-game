#include <text_helper.h>

std::string TextHelper::convertIntToString(int value){
    return std::to_string(value);
}

std::string TextHelper::convertVectorToString(Vector value){
    return "(" + convertIntToString((int)value.x) + ", " + convertIntToString((int)value.y) + ")";
}

std::string TextHelper::applyTimeFormat(int value){
    std::string result = convertIntToString(value);
    if (result.size() == 1){
        result = "0" + result;
    }
    return result;
}

std::string TextHelper::convertTimeToString(double value){
    std::string result;
    result += '[';
    result += applyTimeFormat(int(value) / 60);
    result += ':';
    result += applyTimeFormat(int(value) % 60);
    result += ']';
    return result;
}
