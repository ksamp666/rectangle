//
// Created by Семен Копаниров on 2020-03-27.
//

#include "Random.h"
#include "FrameLogger.h"
#include <iostream>
#include <random>
#include <time.h>


int Random::getRandomNumber(int a, int b) {
    int rand = a + (std::rand() % (b - a + 1));
    FrameLogger::info("Generated Random number between " + std::to_string(a) + " and " + std::to_string(b) + ": " +
                 std::to_string(rand));
    return rand;
}
