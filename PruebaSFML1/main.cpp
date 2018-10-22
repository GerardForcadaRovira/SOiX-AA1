#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include "GraficoSFML.h"


#define WINDOW_H 800
#define WINDOW_V 600
#define TITLE "Mi super practica 1.1"
bool go1 = false;
GraficoSFML graficos;
int times = 0;
int timeStamp;


void arrivePeople(){

go1 = true;


}


void handler1 (int sign){
    //timerLess = true;
    graficos.Timer();
    alarm(1);
    times++;
    //putPerson = true;

}



int main()
{




    bool click = false;
    int interactingObject = -1;
    time_t starting;
    time(&starting);



    float duracionLlegada = 5.0;
    float duracionSalida = 5.0;

    pid_t pid1, pid2;

    int status;

    int sig;
    int tabuAOcupar;

    int estado;
    int estado2;

    size_t length = 2;

    char buf[2];
    char buf2[2];
    char buf3[2];
    char buf4[2];

    int fd[2];
    int fd2[2];
    int fd3[2];
    int fd4[2];

    char arrived[2];
    char arrived2[2];
    char arrived3[2];
    char arrived4[2];

    bool secGone = false;

    estado = pipe(fd);
    if (estado < 0){
        abort();
    } //Error

    estado2 = pipe(fd2);
    if(estado2 < 0){
        abort();
    }

    signal (SIGALRM,handler1);


    alarm(1);

    sf::RenderWindow window(sf::VideoMode(WINDOW_H,WINDOW_V), TITLE);

    pid1 = fork();

    if(pid1 == 0){
    timeStamp = times;
        std::cout << "Hijo 1 creado" << std::endl;

    } else if (pid1 > 0){

        pid2 = fork();

        if( pid2 == 0){
        std::cout << "Hijo 2 creado" << std::endl;

        }

    }








    while(window.isOpen() && graficos.tiempoRestante > 0 && graficos.clientesRestantes > 0)
    {




     if(pid1 == 0){//proceso espera hijo 1 llegada mesa



        if(graficos.TabureteVacio(0)||graficos.TabureteVacio(1)||graficos.TabureteVacio(2)){



        read(fd[0],buf,length);


        //std::cout<<timeStamp<<std::endl;
        //std::cout<<graficos.tiempoRestante<<std::endl;
        //std::cout << "Hijo 1 func" << std::endl;
        //signal(SIGALRM, handler1);

        write(fd2[1], buf2, length);
        std::cout<<"YA"<<std::endl;



        //sleep();

        //close(fd2[0]);
        //close(fd2[1]);
        //signal(SIGALRM, SIG_DFL);








        }

    }

    else

     if(pid2 ==  0){//proceso espera hijo 2 vaciada mesa




        /*read(fd3[0],arrived2,length);

        std::cout << "Hijo 2 func" << std::endl;
        signal(SIGALRM, handler2);

        alarm(10);
        pause();

        *buf2 = "a";
        write(fd4[1], buf4, length);*/

    }




    if(pid1 > 0 && pid2 > 0){



        //if(secGone == false){

           // if(graficos.tiempoRestante < 176){
            timeStamp = times;
            *buf = "b";
            write(fd[1], buf, length);
            secGone = true;
            if(graficos.TabureteVacio(0)){tabuAOcupar = 0;}else
            if(graficos.TabureteVacio(1)){tabuAOcupar = 1;}else
            if(graficos.TabureteVacio(2)){tabuAOcupar = 2;}
            //putPerson = true;
            //graficos.OcupaTaburete(tabuAOcupar);
       //     }
       // }

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

        // graficos.Timer(starting);

        //signal(SIGALRM, SIG_DFL);

        //alarm(1);
        //pause();


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
                graficos.DejaComida(COMIDA_VERDE);
                break;

                case 2:
                //depositar
                graficos.DejaComida(COMIDA_VERDE);
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


       /* if(graficos.tiempoRestante <= 174){
        read(fd2[0],buf2,length);
        //signal(SIGALRM, handler3);

        if(*buf2 == "a"){

        if(graficos.TabureteVacio(0)){tabuAOcupar = 0;}else
        if(graficos.TabureteVacio(1)){tabuAOcupar = 1;}else
        if(graficos.TabureteVacio(2)){tabuAOcupar = 2;}
         graficos.OcupaTaburete(tabuAOcupar);
        }


        *buf = "b";
        write(fd[1], buf, length);
        *buf2 == "0";

        }*/

        }


    }

    return 0;
}
