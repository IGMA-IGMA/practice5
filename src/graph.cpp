#include<graph.h>
#include <defines.h>

FuncGraph::FuncGraph(sf::RenderWindow *window, sf::Color color, double (*function)(double)){
    float step = 1e-2, current_pos = -10;
    this->graph = sf::VertexArray(sf::PrimitiveType::LineStrip, 2000);
    for (int i = 0; i < 2000; i++){
        this->graph[i].position = sf::Vector2f((current_pos + i * step) * MASHTAB + HALF_WINDOW_SIZE + SMESH, HALF_WINDOW_SIZE - function(current_pos + i * step) * MASHTAB + SMESH);
        this->graph[i].color = color;
    }
    this->window = window;
    this->function = function;
}

void FuncGraph::render(){
    this->window->draw(this->graph);
}