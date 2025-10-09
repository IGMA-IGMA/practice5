#include <SFML/Graphics.hpp>
#include <graph.h>
#include <main_window.h>
#include <math.h>
#include <iostream>
#include <defines.h>

double graph_1(double x){
    return 0.1 * x * x - 4;
}
double graph_2(double x){
    return -abs(x);
}
double compress_coord(double coord){
    return (coord - SMESH - HALF_WINDOW_SIZE) / MASHTAB;
}

int main(){
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE + SMESH * 2, WINDOW_SIZE + SMESH * 2}), "SFML works!");
    sf::VertexArray graph(sf::PrimitiveType::LineStrip, 2000);
    MainWindow mw(&window);
    FuncGraph graph1(&window, sf::Color::Red, graph_1);
    FuncGraph graph2(&window, sf::Color::Blue, graph_2);
    double compressed_x, compressed_y, res1_y, res2_y;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonReleased>()){
                compressed_x = compress_coord(sf::Mouse::getPosition(window).x);
                compressed_y = -compress_coord(sf::Mouse::getPosition(window).y);
                std::cout <<compressed_x << ' ' << 
                    compressed_y << std::endl;
                res1_y = graph_1(compressed_x);
                res2_y = graph_2(compressed_x);
                if (compressed_y < res1_y){
                    if (compressed_y > res2_y) {
                        if (compressed_x > 0) std::cout << "zone 5";
                        else std::cout << "zone 4";
                    }
                    else std::cout << "zone 2";
                }
                else {
                    if (compressed_y < res2_y) std::cout << "zone 1";
                    else std::cout << "zone 3";
                }
                std::cout << std::endl;
            }
        }

        window.clear();
        mw.render();
        graph1.render();
        graph2.render();
        window.display();
    }
}