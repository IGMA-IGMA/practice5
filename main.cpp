#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <string>
#include <iostream>

float f1(float x) { return 0.1f * x * x - 4.0f; }
float f2(float x) { return -std::fabs(x); }

void drawGraph(sf::RenderWindow& window,
    std::function<float(float)> func,
    float xMin, float xMax,
    float scaleX, float scaleY,
    sf::Color color)
{
    sf::VertexArray graph;
    graph.setPrimitiveType(sf::PrimitiveType::LineStrip);
    for (float x = xMin; x <= xMax; x += 0.01f) {
        float y = func(x);
        float sx = 400.f + x * scaleX;
        float sy = 300.f - y * scaleY;
        graph.append({ {sx, sy}, color });
    }
    window.draw(graph);
}

std::string determineZone(float x, float y) {
    float y1 = f1(x), y2 = f2(x);
    const float eps = 1e-3f;
    if (std::fabs(y - y1) < eps || std::fabs(y - y2) < eps) return "Boundary";

    if (y1 < y  && y2 > y) return "Zone1";

    if (y1 > y && y2 > y) return "Zone2";

    if (y > y1 && y > y2) return "Zone3";

    if (x > 0 && y < y1 && y > y2) return "Zone5";

    return "Zone4";
}

void drawGrid(sf::RenderWindow& window, float stepX, float stepY, float scaleX, float scaleY) {
    sf::Vector2u ws = window.getSize();
    float w = (float)ws.x, h = (float)ws.y;
    sf::VertexArray lines;
    lines.setPrimitiveType(sf::PrimitiveType::Lines);

    float maxUnitsX = w / (2.f * scaleX);
    for (float x = -maxUnitsX; x <= maxUnitsX; x += stepX) {
        float sx = 400.f + x * scaleX;
        lines.append({ {sx, 0.f}, sf::Color(120, 120, 120) });
        lines.append({ {sx, h}, sf::Color(120, 120, 120) });
    }
    float maxUnitsY = h / (2.f * scaleY);
    for (float y = -maxUnitsY; y <= maxUnitsY; y += stepY) {
        float sy = 300.f - y * scaleY;
        lines.append({ {0.f, sy}, sf::Color(120, 120, 120) });
        lines.append({ {w, sy}, sf::Color(120, 120, 120) });
    }

    window.draw(lines);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "Graphs: y=0.1*x^2 - 4 & y=-|x|");
    window.setFramerateLimit(60);

    sf::CircleShape userPoint(5.f);
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error: could not load font arial.ttf" << std::endl;
    }

    sf::Text coordText(font, "", 20);
    coordText.setFillColor(sf::Color::White);
    coordText.setPosition({ 10.f, 10.f });

    const float scaleX = 30.f;
    const float scaleY = 30.f;

    while (window.isOpen()) {
        while (auto evOpt = window.pollEvent()) {
            const sf::Event& ev = *evOpt;
            if (ev.is<sf::Event::Closed>()) {
                window.close();
            }
            if (auto* mb = ev.getIf<sf::Event::MouseButtonPressed>()) {
                if (mb->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mpos = sf::Mouse::getPosition(window);
                    float mathX = (mpos.x - 400.f) / scaleX;
                    float mathY = -(mpos.y - 300.f) / scaleY;

                    userPoint.setPosition({ mpos.x - userPoint.getRadius(),
                                            mpos.y - userPoint.getRadius() });
                    userPointExists = true;

                    std::string zone = determineZone(mathX, mathY);
                    char buf[100];
                    std::snprintf(buf, sizeof(buf), "x=%.2f y=%.2f\n%s", mathX, mathY, zone.c_str());
                    coordText.setString(buf);

                    std::cout << "Click: mathX=" << mathX << ", mathY=" << mathY
                        << ", zone=" << zone << std::endl;
                }
            }
        }

        window.clear(sf::Color(10, 10, 40));

        drawGrid(window, 1.f, 1.f, scaleX, scaleY);

        // draw axes
        sf::VertexArray xAxis(sf::PrimitiveType::Lines);
        xAxis.append({ {0.f, 300.f}, sf::Color::White });
        xAxis.append({ {800.f, 300.f}, sf::Color::White });
        sf::VertexArray yAxis(sf::PrimitiveType::Lines);
        yAxis.append({ {400.f, 0.f}, sf::Color::White });
        yAxis.append({ {400.f, 600.f}, sf::Color::White });
        window.draw(xAxis);
        window.draw(yAxis);

        drawGraph(window, f1, -(400.f / scaleX), (400.f / scaleX), scaleX, scaleY, sf::Color::Red);
        drawGraph(window, f2, -(400.f / scaleX), (400.f / scaleX), scaleX, scaleY, sf::Color::Cyan);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordText);
        }

        window.display();
    }

    return 0;
}
