#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

#include <SFMLGUI/Gui.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "SFML-GUI Button Example");
    sf::RectangleShape backgorund;
    backgorund.setFillColor(sf::Color::Green);
    backgorund.setSize(sf::Vector2f(800, 600));
    
    sf::Font font;

    font.loadFromFile("Arial.ttf");

    Slider mySlider;    // declarate slider
    mySlider.create(100, 100, 200, 20, 0, 100, 50, font, 26, "Value");    // create slider
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            mySlider.handleEvent(event);
        }
        
        window.clear();
        window.draw(backgorund);
        mySlider.render(window);    // render slider on SFML window
        window.display();
    }
    
    return 0;
}