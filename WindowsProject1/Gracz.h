#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
const int mapWidth = 2000;
const int mapHeight = 2000;
using namespace sf;
class Gracz
{
public:
    double x, y, speed, angle, maxSpeed, acc, dec, turnSpeed;
    bool Up, TurningLeft;
    Sprite car;
    Texture texture;

    Gracz(double startX, double startY, std::string texturePath)
    {
        x = startX;
        y = startY;
        speed = 0;
        angle = 3.14 / 2;
        maxSpeed = 13;
        acc = 0.1;
        dec = 0.4;
        turnSpeed = 0.09;
        Up = true;
        TurningLeft = false;
        texture.loadFromFile(texturePath);
        car.setTexture(texture);
        car.setPosition(startX, startY);
        car.setOrigin(22, 22);
    }

    void update(bool start) {
        if (Up && speed < maxSpeed && (x > 0 && x < mapWidth) && (y > 0 && y < mapHeight))
        {
            if (speed < 0) {
                speed += dec;
                angle += 0.01;
            }
            else {
                speed += acc;
            }
        }

        if (TurningLeft && speed != 0) {
            if (speed > maxSpeed / 2.0) {
                speed -= dec;
            }
            angle -= turnSpeed * speed / maxSpeed;
        }

        x += sin(angle) * speed;
        y -= cos(angle) * speed;

        car.setPosition(x, y);
    }
};


