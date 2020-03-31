//
// Created by Семен Копаниров on 2020-03-27.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "RotatingRectangle.h"
#include "../utils/Random.h"
#include "../Config.h"
#include "../utils/FrameLogger.h"

RotatingRectangle::RotatingRectangle(sf::Vector2f size, sf::Vector2f position, int rotationSpeed) {
    FrameLogger::info("Creating rotating rectangle with size " + std::to_string(size.x) + "x" + std::to_string(size.y) +
                      " at position (" + std::to_string(position.y) + "," + std::to_string(position.y) + ").");
    this->rotationSpeed = rotationSpeed;
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setOrigin(size.x / 2, size.y / 2);
    shape.setOutlineColor(sf::Color::Blue);
    shape.setOutlineThickness(5);
    shape.setPosition(position.x, position.y);
}

void RotatingRectangle::rotate() {
    float rotationAngel = rotationSpeed * clock.getElapsedTime().asSeconds();
    if (shape.getRotation() + rotationAngel > 360) {
        if (Random::getRandomNumber(1, 100) <= CRASH_CHANCE) {
            auto crashType = Random::getRandomNumber(1, 3);
            switch (crashType) {
                case 1: {
                    std::string str = nullptr;
                    str.substr(1, 2);
                    break;
                }

                case 2: {
                    int a = 5;
                    int b = 10 / (a - a);
                    break;
                }

                case 3: {
                    abort();
                }

                default:
                    break;
            }
        }

        rotationCounter++;
        FrameLogger::info("Rectangle rotated a full turn. Completed turns number: " + std::to_string(rotationCounter));
    }
    shape.rotate(rotationAngel);
    FrameLogger::info("Rectangle is rotated. Current angel: " + std::to_string(shape.getRotation()));
    clock.restart();
}

sf::RectangleShape RotatingRectangle::getShape() {
    return shape;
}

int RotatingRectangle::getFullTurnsNumber() {
    return rotationCounter;
}
