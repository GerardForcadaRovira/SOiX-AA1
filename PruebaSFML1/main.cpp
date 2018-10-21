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

    bool click = false;
    int interactingObject = -1;
    time_t starting;
    time(&starting);


    int clientesRestantes = 5;
    float duracionLlegada = 5.0;
    float duracionSalida = 5.0;

    int pid1, pid2, status;

    /*if(pid1 = fork() == 0){
        std::cout << "Hijo 1 creado" << std::endl;
        exit(0);
    }

    if(pid2 = fork() == 0){
        std::cout << "Hijo 2 creado" << std::endl;
        exit(0);
    }*/


    sf::RenderWindow window(sf::VideoMode(WINDOW_H,WINDOW_V), TITLE);

    GraficoSFML graficos;

    while(window.isOpen() && graficos.tiempoRestante > 0)
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
                    click = true;
                }
            }
        }

        graficos.Timer(starting);

        interactingObject = graficos.Colisionando(graficos.posicionJugador,graficos.aOrigenMesas,graficos.aOrigenDispensadores,graficos.sizeMesa);

        if(click == true){
        switch(interactingObject){

                case -1:
                //mantener

                break;

                case 0:
                //depostiar
                graficos.DejaComida(COMIDA_VERDE);
                graficos.PonPedido(0,COMIDA_VERDE);
                break;

                case 1:
                //depositar
                graficos.DejaComida(COMIDA_VERDE);
                break;

                case 2:
                //depositar
                graficos.DejaComida(COMIDA_VERDE);
                break;

                case 3:
                //tomar
                graficos.CogeComida(COMIDA_VERDE);
                break;

                case 4:
                //tomar
                graficos.CogeComida(COMIDA_AMARILLA);
                break;

                case 5:
                //tomar
                graficos.CogeComida(COMIDA_ROJA);
                break;
                }

                click = false;

        }

       /* if(pid1 == 0){
            std::cout << "Hijo 1 accion" << std::endl;

        } else {

        if(pid2 == 0){
            std::cout << "Hijo 2 accion" << std::endl;

        }

        }*/

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
