#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

#include <SFMLGUI/Gui.hpp>

using namespace std;

void buttonFunction()   // function executed if button clicked
{
    std::cout << "Button was clicked" << std::endl;
}

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "SFML-GUI Button Example");
    sf::RectangleShape backgorund;
    backgorund.setFillColor(sf::Color::Green);
    backgorund.setSize(sf::Vector2f(800, 600));
    
    sf::Font font;

    font.loadFromFile("Arial.ttf");

    sfg::Button myButton;    // declarate button
    myButton.create(100, 100, 200, 50, font, "Click me", false);    // create button

    myButton.setFunction(buttonFunction);   // set function to button
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        myButton.update(mousePos);     // update button mouse check algorithm by current mouse position
        
        window.clear();
        window.draw(backgorund);
        myButton.render(window);    // render button on SFML window
        window.display();
    }
    
    return 0;
}