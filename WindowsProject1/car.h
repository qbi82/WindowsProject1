#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const int mapWidth = 2000;
const int mapHeight = 2000;

class Car
{
public:
    Sprite sprite;
    Texture texture;
    double spriteScaleX, spriteScaleY;

    Car(double startX, double startY, std::string texturePath, double scale)
    {
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
        sprite.setOrigin(22, 22);
        sprite.setScale(scale, scale);
        spriteScaleX = texture.getSize().x * scale;
        spriteScaleY = texture.getSize().y * scale;
    }

    bool isOnTrack() {
        Vector2f carPosition = sprite.getPosition();
        Vector2u textureSize = texture.getSize();
        double spriteScaleX = spriteScaleX;
        double spriteScaleY = spriteScaleY;

        if (carPosition.x >= 0 && carPosition.x <= textureSize.x * spriteScaleX
            && carPosition.y >= 0 && carPosition.y <= textureSize.y * spriteScaleY)
        {
            int x = carPosition.x / spriteScaleX;
            int y = carPosition.y / spriteScaleY;
            Color pixelColor = texture.copyToImage().getPixel(x, y);
            if (pixelColor.a == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
};

