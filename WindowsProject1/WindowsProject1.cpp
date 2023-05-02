﻿#include <SFML/Graphics.hpp>
#include<iostream>
#include <sstream> // do std::ostringstream
#include <string>
#include <cmath>

using namespace sf;
using namespace std;

int main()
{   
    float k = 300, l = 300;
    RenderWindow app(VideoMode(1280, 1024), "KRESKI!!");
    app.setFramerateLimit(60);
    const float mapWidth = 1280 ;
    const float mapHeight = 1024;
    
    bool przekroczyl_linie = false;
    bool pokaz_tekst = true;
    int okrazenia_ilosc = 0;
    bool pierwsza_iteracja = true;


    if (k < 0) k = 0;
    if (l < 0) l = 0;
    if (k > mapWidth) k = mapWidth;
    if (l > mapHeight) l = mapHeight;

    Texture t1, t2,t3,t4;
    t1.loadFromFile("es3-GTŻ.mask.png");
    t2.loadFromFile("Car5.png");
    t3.loadFromFile("Car2.png");
    t4.loadFromFile("es3-GTŻ.stad.png");

    

    Sprite sBackground(t1), sCar(t2), sCar2(t3),overlay(t4);
    sCar2.setPosition(630, 740);
    sCar2.setOrigin(22, 22);
    sCar2.setColor(Color::Black);
    sCar.setPosition(630, 640);
    sCar.setOrigin(22, 22);
    overlay.setPosition(0, 0);

    overlay.setTexture(t4);
    overlay.setScale(float(mapWidth) / float(t1.getSize().x), float(mapHeight) / float(t1.getSize().y));
    sBackground.setTexture(t1);
    sBackground.setScale(float(mapWidth) / float(t1.getSize().x), float(mapHeight) / float(t1.getSize().y));
    
    
    //predkosc gracza 1
    float x_1 = 635, y_1 = 640;
    float speed_1 = 0, angle_1 = 3.14/2;
    float maxSpeed_1 = 13;
    float acc_1 = 0.1, dec_1 = 0.4;
    float turnSpeed_1 = 0.09;
    const float odbicie_1 = 80;

    //predkosc gracza 2
    float x_2 = 635, y_2 = 740;
    float speed_2 = 0, angle_2 = 3.14/2;
    float maxSpeed_2 = 13;
    float acc_2 = 0.1, dec_2 = 0.4;
    float turnSpeed_2 = 0.09;
    const float odbicie_2 = 80;
    
    //wyswietlenie wartosci predkosc
    Font font;
    if (!font.loadFromFile("ChunkFive-Regular.otf")) {
        // obsługa błędu w razie problemów z załadowaniem czcionki
    }
    

    sf::Text wskaznik_okrazen;
    wskaznik_okrazen.setFont(font);
    wskaznik_okrazen.setCharacterSize(40);
    wskaznik_okrazen.setFillColor(Color::Black);
    wskaznik_okrazen.setPosition(20, 0);
    wskaznik_okrazen.setString("Okrazenia: " + std::to_string(okrazenia_ilosc));

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Black);
    text.setPosition(20, 40);

    sf::Text controls_text;
    controls_text.setFont(font);
    controls_text.setCharacterSize(40);
    controls_text.setFillColor(sf::Color::Black);
    controls_text.setPosition(20, 150);
    controls_text.setString("LEWO - SKRET W LEWO\nSPACJA - HAMULEC\nESC - WYJSCIE");

	sf::Text CZAS_OKRAZENIA_1;
    CZAS_OKRAZENIA_1.setFont(font);
    CZAS_OKRAZENIA_1.setCharacterSize(40);
    CZAS_OKRAZENIA_1.setFillColor(Color::Black);
    CZAS_OKRAZENIA_1.setPosition(20, 80);
    

    sf::Text zegar;

    zegar.setFont(font);
    zegar.setCharacterSize(100);
    zegar.setFillColor(Color::Black);
    zegar.setPosition(600, 360);
    Clock clock2;
    Time granice;
    Clock clock1;
    Time time;
    Clock clock;
    Time startowanie;

    startowanie = clock.getElapsedTime();

    
    

    Clock czas_okrazenia_gr1;
    
    float odliczanie = 3;
    bool start = false;
    bool start_odliczania = false;

    RectangleShape Okrazenia(Vector2f(661, 20));
    Okrazenia.setFillColor(Color::Black);
    Okrazenia.setOutlineThickness(2);
    Okrazenia.setOutlineColor(Color::Black);

    Text Czas_najszybszy_Gracza1;
    Czas_najszybszy_Gracza1.setFont(font);
    Czas_najszybszy_Gracza1.setCharacterSize(40);
    Czas_najszybszy_Gracza1.setFillColor(Color::Black);
    Czas_najszybszy_Gracza1.setPosition(700, 20);
    Time czas_koncowy_poprzedniego_okrazenia = czas_okrazenia_gr1.getElapsedTime();
    Time czas_startowy_biezacego_okrazenia;
    float czas_najszybszy_gr1;
    


    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Space) {
                    pokaz_tekst = !pokaz_tekst;
                }
                if (e.key.code == Keyboard::Space) {
                    start_odliczania = !start_odliczania;
            }
            }
        }
        
        //zegar odliczanie
        if (start_odliczania) {
            float opoznienie = clock.restart().asSeconds();
            odliczanie -= opoznienie;
            if (odliczanie <= 0) {
                start = true;
                odliczanie = 0;
            }
        }



        string message;
        if (start) {
            message = "START!";
        }
        else {
            message = to_string((int)ceil(odliczanie));
        }
        zegar.setString(message);



        




        //GRACZ 1 
        bool Up_1 = true, Left_1 = false, TurningLeft_1 = false;

        if (Keyboard::isKeyPressed(Keyboard::LShift)) {
            Up_1 = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            TurningLeft_1 = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            app.close();
        }
        // Kontroler samochodu
        if (start) {
            if (Up_1 && speed_1 < maxSpeed_1 && (x_1 > 0 && x_1 < mapWidth) && (y_1 > 0 && y_1 < mapHeight)) {
                if (speed_1 < 0) {
                    speed_1 += dec_1;
                    angle_1 += 0.01;
                }
                else {
                    speed_1 += acc_1;
                }
            }
        }
        if (TurningLeft_1 && speed_1 != 0 ) {
            if (speed_1 > maxSpeed_1 / 2.0) {
                speed_1 -= dec_1;
            }
            angle_1 -= turnSpeed_1 * speed_1 / maxSpeed_1;
        }


        // Aktualizacja pozycji pojazdu
        x_1 += sin(angle_1) * speed_1;
        y_1 -= cos(angle_1) * speed_1;




    //GRACZ 2
    bool Up_2 = true,Left_2 = false;


    if (Keyboard::isKeyPressed(Keyboard::A)) {
        Left_2 = true;
    }
    // Kontroler samochodu
    if (start) {
        if (Up_2 && speed_2 < maxSpeed_2 && (x_2 > 0 && x_2 < mapWidth) && (y_2 > 0 && y_2 < mapHeight)) {
            if (speed_2 < 0) {
                speed_2 += dec_2;
                angle_2 += 0.01;
            }
            else {
                speed_2 += acc_2;
            }
        }
    }
    if (Left_2 && speed_2 != 0) {
        if (speed_2 > maxSpeed_2 / 2.0) {
            speed_2 -= dec_1;
        }
        angle_2 -= turnSpeed_2 * speed_2 / maxSpeed_2;
    }

    // Aktualizacja pozycji pojazdu 2
    x_2 += sin(angle_2) * speed_2;
    y_2 -= cos(angle_2) * speed_2;

    		time = clock1.getElapsedTime();
            //rysowanie lini mety
            sf::RectangleShape finishLine(sf::Vector2f(1.0f, 280.0f));
            finishLine.setPosition(661.0f, 600.0f);
            finishLine.setFillColor(sf::Color::Green);
            
            
            //zliczanie ilosci okrazen dla gracza 1
            if (time.asSeconds() >= 1) {
                if (sCar.getGlobalBounds().intersects(finishLine.getGlobalBounds()) && !przekroczyl_linie) {
                    okrazenia_ilosc++;
                    przekroczyl_linie = true;
                    wskaznik_okrazen.setString("Okrazenie: " + to_string(okrazenia_ilosc));
                    clock1.restart();

                    czas_startowy_biezacego_okrazenia = czas_okrazenia_gr1.getElapsedTime();

                    sf::Time czas_trwania_okrazenia = czas_startowy_biezacego_okrazenia - czas_koncowy_poprzedniego_okrazenia;
                    if (okrazenia_ilosc>1)
                    {
                        if (pierwsza_iteracja) {
                            czas_najszybszy_gr1 = czas_trwania_okrazenia.asSeconds();
                            pierwsza_iteracja = false;
                        }
                        Czas_najszybszy_Gracza1.setString("Najszybsze okrazenie: " + to_string(czas_najszybszy_gr1));
                    }
                    if (okrazenia_ilosc != 1) {
                        CZAS_OKRAZENIA_1.setString("Czas okrazenia " + to_string(okrazenia_ilosc) + ": " + to_string(czas_trwania_okrazenia.asSeconds()));
                        if (okrazenia_ilosc > 1 && czas_najszybszy_gr1 > czas_trwania_okrazenia.asSeconds())
                        {
                            czas_najszybszy_gr1 = czas_trwania_okrazenia.asSeconds();
                    }
                    czas_koncowy_poprzedniego_okrazenia = czas_startowy_biezacego_okrazenia;
                    
                    }
                    
                }
            }
                else if (sCar.getGlobalBounds().intersects(finishLine.getGlobalBounds()) && przekroczyl_linie) {
                    przekroczyl_linie = false;
                }

           

        
            //wartosci granic
            Vector2f carPosition = sCar.getPosition();
            Vector2f carPosition2 = sCar2.getPosition();
            Vector2u textureSize = t1.getSize();
            Vector2f spriteScale = sBackground.getScale();
            granice = clock2.getElapsedTime();
            
            
            // sprawdzenie, czy samochód znajduje się w granicach toru
    		if (carPosition.x >= 0 && carPosition.x <= textureSize.x * spriteScale.x
                && carPosition.y >= 0 && carPosition.y <= textureSize.y * spriteScale.y)
            {
                // sprawdzenie przezroczystości piksela pod samochodem
                
                int x = carPosition.x / spriteScale.x;
                int y = carPosition.y / spriteScale.y;
                Color pixelColor = t1.copyToImage().getPixel(x, y);
                if (pixelColor.a == 0)
                {
                    t2.loadFromFile("wybuch.png");
                }
                else
                {
                    if (start) {
                        if (speed_1 < maxSpeed_1)
                        {
                            speed_1 += acc_1;
                        }
                    }
                }
            }
            else
            {
                // samochód znajduje się poza granicami toru, to stop
                speed_1 = 0;
            }

            //if (carPosition2.x >= 0 && carPosition2.x <= textureSize.x * spriteScale.x && carPosition2.y >= 0 && carPosition2.y <= textureSize.y * spriteScale.y)
            //{
            //    int x = carPosition2.x / spriteScale.x;
            //    int y = carPosition2.y / spriteScale.y;
            //    Color pixelColor = t1.copyToImage().getPixel(x, y);
            //    if (pixelColor.a == 0)
            //    {
            //        if (granice.asSeconds() >= 0.75) {
            //            // jeśli piksel jest przezroczysty, samochód opóźnia
            //            x_2 -= sin(angle_2) * odbicie_2;
            //            y_2 += cos(angle_2) * odbicie_2;
            //            speed_2 = -speed_2 / 1.2; // zmiana kierunku i zmniejszenie prędkości

            //            clock2.restart();
            //        }
            //    }
            //    else
            //    {
            //        if (start) {
            //            if (speed_2 < maxSpeed_2)
            //            {
            //                speed_2 += acc_2;
            //            }
            //        }
            //    }
            //}
            //else
            //{
            //    speed_2 = 0;
            //}



    	//rysowanie 
        app.clear(Color::White);
        app.draw(sBackground);
        app.draw(overlay);
        sCar.setPosition(x_1, y_1);
        sCar.setRotation(angle_1 * 180 / 3.1415);
        sCar.setColor(Color::Red);
        sCar2.setPosition(x_2, y_2);
        sCar2.setRotation(angle_2 * 180 / 3.1415);
        app.draw(sCar);
        
        //app.draw(sCar2);

        text.setString("Predkosc: " + std::to_string(speed_1));
        app.draw(text);
        
        app.draw(CZAS_OKRAZENIA_1);
        app.draw(finishLine);
        if (okrazenia_ilosc <= 1) {
            app.draw(zegar);
        }
        app.draw(wskaznik_okrazen);
        if (pokaz_tekst) {
            app.draw(controls_text);
        }
        if (okrazenia_ilosc >3 ) {
            app.draw(Czas_najszybszy_Gracza1);
            
        }
        app.display();
    
    }

    return 0;
}
