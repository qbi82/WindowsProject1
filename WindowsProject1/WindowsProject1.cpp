#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "MainMenu.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow menu(VideoMode(1280, 1024), "Menu", Style::Default);
    menu.setMouseCursorVisible(true);
    MainMenu mainMenu(menu.getSize().x, menu.getSize().y);
    //tlo menu
    RectangleShape bbackground;
    bbackground.setSize(Vector2f(1280, 1024));
    Texture GlownaText;
    GlownaText.loadFromFile("Roblox1.png");
    bbackground.setTexture(&GlownaText);
    
    while (menu.isOpen())
    {
        Event event{};
        while (menu.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                menu.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Escape)
                {
                    menu.close();
                }
                if (event.key.code == Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }
                if (event.key.code == Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }
                if (event.key.code == Keyboard::Return)
                {
                    RenderWindow Graj(VideoMode(1280, 1024), "Kreski");
                    RenderWindow OPCJE(VideoMode(1280, 1024), "Opcje");
                    RenderWindow INFORMACJE(VideoMode(1280, 1024), "Informacje");

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0)
                    {
                        while (Graj.isOpen())
                        {
                            
                            Event aevent{};
                            while (Graj.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed)
                                {
                                    Graj.close();
                                }
                                double k = 300, l = 300;
                                RenderWindow app(VideoMode(1280, 1024), "KRESKI!!");
                                app.setFramerateLimit(60);
                                const double mapWidth = 1280;
                                const double mapHeight = 1024;

                                bool przekroczyl_linie = false;
                                bool pokaz_tekst = true;
                                int okrazenia_ilosc = 0;
                                bool pierwsza_iteracja = true;
                                double limit_okrazen = 5;

                                if (k < 0) k = 0;
                                if (l < 0) l = 0;
                                if (k > mapWidth) k = mapWidth;
                                if (l > mapHeight) l = mapHeight;

                                Texture t1, t2, t3, t4,t2_1;
                                t1.loadFromFile("es3-GTŻ.mask.png");
                                t2.loadFromFile("Car5.png");
                                t3.loadFromFile("Car2.png");
                                t4.loadFromFile("es3-GTŻ.stad.png");
                                if(!t2_1.loadFromFile("wybuch.png"))
                                {
                                }
                                t2_1.loadFromFile("wybuch.png");


                                Sprite sBackground(t1), sCar, sCar2(t3), overlay(t4);
                                sCar2.setPosition(630, 740);
                                sCar2.setOrigin(22, 22);
                                sCar2.setColor(Color::Black);
                                sCar.setTexture(t2);
                                sCar.setPosition(630, 640);
                                sCar.setOrigin(22, 22);
                                overlay.setPosition(0, 0);

                                overlay.setTexture(t4);
                                overlay.setScale(float(mapWidth) / float(t1.getSize().x), float(mapHeight) / float(t1.getSize().y));
                                sBackground.setTexture(t1);
                                sBackground.setScale(float(mapWidth) / float(t1.getSize().x), float(mapHeight) / float(t1.getSize().y));


                                //predkosc gracza 1
                                double x_1 = 635, y_1 = 640;
                                double speed_1 = 0, angle_1 = 3.14 / 2;
                                double maxSpeed_1 = 13;
                                double acc_1 = 0.1, dec_1 = 0.4;
                                double turnSpeed_1 = 0.09;

                                //predkosc gracza 2
                                double x_2 = 635, y_2 = 740;
                                double speed_2 = 0, angle_2 = 3.14 / 2;
                                double maxSpeed_2 = 13;
                                double acc_2 = 0.1, dec_2 = 0.4;
                                double turnSpeed_2 = 0.09;
                                

                                
                                Font font;
                                if (!font.loadFromFile("ChunkFive-Regular.otf")) {
                                    // obsługa błędu z załadowaniem czcionki
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
                                    Event e{};
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


                                    //////////////////////////////////////////////////////////
                                    //GRACZ 1 
                                    bool Up_1 = true, TurningLeft_1 = false;

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
                                        if (Up_1 && speed_1 < maxSpeed_1 && (x_1 > 0 && x_1 < mapWidth) && (y_1 > 0 &&
	                                        y_1 < mapHeight))
                                        {
                                            if (speed_1 < 0) {
                                                speed_1 += dec_1;
                                                angle_1 += 0.01;
                                            }
                                            else {
                                                speed_1 += acc_1;
                                            }
                                        }
                                    }
                                    if (TurningLeft_1 && speed_1 != 0) {
                                        if (speed_1 > maxSpeed_1 / 2.0) {
                                            speed_1 -= dec_1;
                                        }
                                        angle_1 -= turnSpeed_1 * speed_1 / maxSpeed_1;
                                    }


                                    // Aktualizacja pozycji pojazdu
                                    x_1 += sin(angle_1) * speed_1;
                                    y_1 -= cos(angle_1) * speed_1;



                                    ////////////////////////////////////////////////////////////////////
                                    //GRACZ 2
                                    bool Up_2 = true, Left_2 = false;

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


                                    ////////////////////////////////////////////////////
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
                                            if (okrazenia_ilosc > 1)
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

                                    bool czydotknal = false;
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
                                            czydotknal = true;
                                           
                                                
                                         
                                            speed_1 = 0;
                                            acc_1 = 0;
                                            
                                            
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

                                //rysowanie
                                    
                                        app.clear(Color::White);
                                        app.draw(sBackground);
                                        app.draw(overlay);
                                        sCar.setPosition(x_1, y_1);
                                        sCar.setRotation(angle_1 * 180 / 3.1415);
                                        if (czydotknal) {
                                            sCar.setTexture(t2_1);
                                        }else{ sCar.setColor(Color::Red); }
                                        
                                        
                                        sCar2.setPosition(x_2, y_2);
                                        sCar2.setRotation(angle_2 * 180 / 3.1415);
                                        if (okrazenia_ilosc < limit_okrazen) {
                                            app.draw(sCar);

                                        }
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
                                        if (okrazenia_ilosc > 3) {
                                            app.draw(Czas_najszybszy_Gracza1);
                                        }
                                        app.display();
                                    
                                }

                                
                            
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
                                        Graj.close();
                                    }
                                }
                            }
                            OPCJE.close();
                            INFORMACJE.close();
                            Graj.clear();
                            Graj.display();
                            break;
                        }
                    }
                    if (x == 1)
                    {
                        while (OPCJE.isOpen()) {
                            Event aevent{};
                            if (aevent.type == Event::Closed) {
                                OPCJE.close();
                            }
                            if (aevent.type == Event::KeyPressed) {
                                if (aevent.key.code == Keyboard::Escape) {
                                    OPCJE.close();
                                }
                            }

                            Graj.close();
                            OPCJE.clear();
                            INFORMACJE.close();
                            OPCJE.display();
                        }
                    }
                    if (x == 2) {
                        while (INFORMACJE.isOpen()) {
                            Event aevent{};
                            if (aevent.type == Event::Closed) {
                                INFORMACJE.close();
                            }
                            if (aevent.type == Event::KeyPressed) {
                                if (aevent.key.code == Keyboard::Escape) {
                                    INFORMACJE.close();
                                }
                            }

                            Graj.close();
                            OPCJE.close();
                            INFORMACJE.clear();
                            INFORMACJE.display();
                        }
                    }
                    if (x == 3) {
                        menu.close();
                        break;
                    }
                }
            }
            menu.clear();
            menu.draw(bbackground);
            mainMenu.draw(menu);
            menu.display();
        }
    }
    }
   
