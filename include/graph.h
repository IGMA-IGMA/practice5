#ifndef GRAPH_H
#define GRAPH_H

#include<SFML/Graphics.hpp>

class FuncGraph{
    public:
        FuncGraph(sf::RenderWindow *window, sf::Color color, double (*function)(double));
        void render();
    private:
        sf::VertexArray graph;
        double (*function)(double);
        sf::RenderWindow *window;
};

#endif