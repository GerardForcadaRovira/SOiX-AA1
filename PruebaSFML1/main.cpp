#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include "GraficoSFML.h"

#define WINDOW_H 800
#define WINDOW_V 600
#define TITLE "Mi super practica 1.1"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_H,WINDOW_V), TITLE);

    GraficoSFML graficos;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    graficos.MueveJugador(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                }
            }
        }

        window.clear();


        for(size_t i = 0; i < graficos.aTextosADibujar.size(); i++)
        {
            window.draw(graficos.aTextosADibujar[i]);
        }
        for(size_t i = 0; i < graficos.aObjetosADibujar.size(); i++)
        {
            window.draw(graficos.aObjetosADibujar[i]);
        }

        for (size_t i =0 ; i< NUM_MESAS; i++)
        {
            window.draw(graficos.aTaburetesADibujar[i]);
            window.draw(graficos.aPedidosADibujar[i]);
        }
        window.draw(graficos.jugador);
        window.draw(graficos.manoIzquierda);
        window.draw(graficos.manoDerecha);

        window.display();
    }

    return 0;
}
