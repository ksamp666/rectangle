//
// Created by Семен Копаниров on 2020-03-29.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include "FrameLogger.h"

static int frame = 1;

void FrameLogger::info(std::string log) {
    std::cout << createLogMessage(typeInfo, &log) << std::endl;
}

void FrameLogger::error(std::string log) {
    std::cout << createLogMessage(typeError, &log) << std::endl;
}

std::string FrameLogger::createLogMessage(LogType type, std::string *log) {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto mcs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000;
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    ss << std::setfill('0') << std::setw(3) << mcs.count();
    std::string formattedTime = ss.str();

    std::string logLevel;
    switch (type) {
        case typeError: {
            logLevel = "[ERROR]";
            break;
        }
        case typeInfo: {
            logLevel = "[INFO]";
            break;
        }
    }

    return std::to_string(frame) + ": " + formattedTime + " " + logLevel + " " + *log;
}

void FrameLogger::updateFrame() {
    frame++;
}
