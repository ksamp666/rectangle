//
// Created by Семен Копаниров on 2020-03-29.
//

#ifndef RECTANGLE_LOGGER_H
#define RECTANGLE_LOGGER_H


#include <string>
#include <vector>

class FrameLogger {
private:
    enum LogType { typeInfo, typeError };
    static std::string createLogMessage(LogType type, std::string* log);
public:
    static void info(std::string log);
    static void error(std::string log);
    static void updateFrame();
};


#endif //RECTANGLE_LOGGER_H
