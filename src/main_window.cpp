#include<main_window.h>
#include<defines.h>

MainWindow::MainWindow(sf::RenderWindow *window){
    this->lines = sf::VertexArray(sf::PrimitiveType::Lines, 80);
    this->window = window;
    for (int i = 0; i < 40; i+=2){
        this->lines[i].position = sf::Vector2f(i * MASHTAB + SMESH, 0);
        this->lines[i+1].position = sf::Vector2f(i * MASHTAB + SMESH, WINDOW_SIZE + SMESH * 2);
        this->lines[i + 40].position = sf::Vector2f(0, i * MASHTAB + SMESH);
        this->lines[i+41].position = sf::Vector2f(WINDOW_SIZE + SMESH * 2, i * MASHTAB + SMESH);
    }
}

void MainWindow::render(){
    this->window->draw(this->lines);
}