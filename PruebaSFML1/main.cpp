#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include "GraficoSFML.h"

#define WINDOW_H 800
#define WINDOW_V 600
#define TITLE "Mi practica"
#define MAX_TIME_SEC 180
#define DELAY_CLIENTES 5
#define CLIENTES 5


int main()
{
int estadoLlegada, estadoVaciado;
int pllegada[2]; //0=lectura / 1=escritura
int pvaciado[2];
estadoLlegada = pipe(pllegada);
estadoVaciado = pipe(pvaciado);
if (estadoLlegada<0){exit(0);}
else if(estadoVaciado<0){exit(0);}
else{}
pid_t hijoLlegada, hijoVaciado;
hijoLlegada = fork();

char* buffer[10];

    if(hijoLlegada==0){
    //proceso hijo1
        close(pllegada[0]);
        close(pvaciado[0]);
        close(pvaciado[1]);
        write(pllegada[1],"HOLAA Hola",10);
    }else{
    hijoVaciado=fork();
        if(hijoVaciado==0){
        //proceso hijo2
            close(pvaciado[0]);
            close(pllegada[0]);
            close(pllegada[1]);

        }else{
        //proceso padre
            close(pvaciado[1]);
            close(pllegada[1]);
            read(pllegada[0],buffer,10);
            std::cout<<buffer<<std::endl;

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
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            graficos.MueveJugador(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                    }
                }

                window.clear();


                for(size_t i = 0; i < graficos.aTextosADibujar.size(); i++) {
                    window.draw(graficos.aTextosADibujar[i]);
                }
                for(size_t i = 0; i < graficos.aObjetosADibujar.size(); i++) {
                    window.draw(graficos.aObjetosADibujar[i]);
                }
                for (size_t i =0 ; i< NUM_MESAS; i++) {
                    window.draw(graficos.aTaburetesADibujar[i]);
                    window.draw(graficos.aPedidosADibujar[i]);
                }
                window.draw(graficos.jugador);
                window.draw(graficos.manoIzquierda);
                window.draw(graficos.manoDerecha);

                window.display();
            }

        }

    }

    return 0;
}
