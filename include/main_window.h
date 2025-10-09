#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include<SFML/Graphics.hpp>

class MainWindow{
    public:
        MainWindow(sf::RenderWindow *window);
        void render();
    private:
        sf::VertexArray lines;
        sf::RenderWindow *window;
};

#endif