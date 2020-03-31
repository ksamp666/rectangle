#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "source/utils/Random.h"
#include "source/characters/RotatingRectangle.h"
#include "source/Config.h"
#include "source/utils/FrameLogger.h"
#include <time.h>
#include <zconf.h>
#include <execinfo.h>
#include <filesystem>

void SignalHandler(int signal) {
    void *array[10];
    auto size = backtrace(array, 10);
    char **backtrace = backtrace_symbols(array, size);
    fprintf(stderr, "Application crashed! Error code: %d:\n", signal);
    for (int i = 0; i < size; i++) {
        fprintf(stderr, "Line %s:\n", backtrace[i]);
    }
    exit(signal);
}

void initSignalsHandler() {
    for (int i = 1; i <= 31; i++) {
        signal(i, SignalHandler);
    }
}

int main(int argc, char **argv) {
    //Init signal handlers
    initSignalsHandler();

    //Change application default directory to current dirrectory of executable file
    auto exePath = std::string(argv[0]);
    std::filesystem::current_path(exePath.substr(0, exePath.find_last_of('/')));

    //Read arguments
    int timeout = 0;
    if (argc >= 2) {
        timeout = atoi(argv[1]);
        FrameLogger::info("Starting application with timeout set to " + std::to_string(timeout));
    }

    //Define timer
    sf::Clock longTimer, shortTimer;

    //Randomize generator
    srand(static_cast<unsigned int>(time(nullptr)));

    //Create window
    sf::Vector2u windowSize = sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), WINDOW_TITLE);

    //Create rectangle
    int rotationSpeed = Random::getRandomNumber(ROTATION_SPEED_MIN, ROTATION_SPEED_MAX);
    sf::Vector2f rectangleSize = sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
    sf::Vector2f rectanglePosition = sf::Vector2f(RECTANGLE_POSITION_X, RECTANGLE_POSITION_Y);
    auto *rectangle = new RotatingRectangle(rectangleSize, rectanglePosition, rotationSpeed);

    //Create text label for rotations count
    sf::Text rotationsText;
    rotationsText.setString(TEXT_STRING + std::string("0"));
    sf::Font font;
    font.loadFromFile(TEXT_FONT_FILE);
    rotationsText.setFont(font);
    rotationsText.setCharacterSize(TEXT_SIZE);
    rotationsText.setFillColor(sf::Color::White);
    rotationsText.setPosition(TEXT_POSITION_X, TEXT_POSITION_Y);

    //Start main loop
    while (window.isOpen()) {
        //Exit application if timeout is reached
        if (timeout > 0 && longTimer.getElapsedTime().asSeconds() > timeout) {
            return 0;
        }

        //Handle Closed event
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Recalculate rectangle rotation
        rectangle->rotate();

        //Recalculate rotations number text
        rotationsText.setString(TEXT_STRING + std::to_string(rectangle->getFullTurnsNumber()));

        //Render
        window.clear(sf::Color::Black);
        window.draw(rotationsText);
        window.draw(rectangle->getShape());
        window.display();

        //Fake FPS
        if (shortTimer.getElapsedTime().asMilliseconds() < FAKED_RENDER_TIME_MIN) {
            int approvedNumber = 0;
            if (Random::getRandomNumber(1, 2) == 1) {
                approvedNumber = Random::getRandomNumber(FAKED_RENDER_TIME_MIN, FAKED_RENDER_TIME_MEDIAN);
            } else {
                approvedNumber = Random::getRandomNumber(FAKED_RENDER_TIME_MEDIAN, FAKED_RENDER_TIME_MAX);
            }
            unsigned int sleepTime = ((uint) approvedNumber - shortTimer.getElapsedTime().asMilliseconds()) * 1000;
            usleep(sleepTime);
        }

        FrameLogger::info(
                "Frame rendered. Render time: " + std::to_string(shortTimer.getElapsedTime().asMicroseconds()) +
                " microseconds.");
        shortTimer.restart();

        FrameLogger::updateFrame();
    }

    return 0;
}

