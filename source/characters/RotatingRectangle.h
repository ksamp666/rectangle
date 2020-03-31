//
// Created by Семен Копаниров on 2020-03-27.
//

#ifndef RECTANGLE_ROTATINGRECTANGLE_H
#define RECTANGLE_ROTATINGRECTANGLE_H

#include <SFML/System.hpp>

class RotatingRectangle {
private:
    float rotationSpeed;
    sf::Clock clock;
    sf::RectangleShape shape;
    int rotationCounter = 0;

public:
    RotatingRectangle(sf::Vector2f size, sf::Vector2f position, int rotationSpeed);

    void rotate();

    sf::RectangleShape getShape();

    int getFullTurnsNumber();
};


#endif //RECTANGLE_ROTATINGRECTANGLE_H
