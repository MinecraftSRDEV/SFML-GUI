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
    window.create(sf::VideoMode(800, 600), "SFML-GUI Checkbox Example");
    sf::RectangleShape backgorund;
    backgorund.setFillColor(sf::Color::Green);
    backgorund.setSize(sf::Vector2f(800, 600));
    
    sf::Font font;

    font.loadFromFile("Arial.ttf");

    Checkbox myCheckbox;    // declarate checkbox
    myCheckbox.create(40, 40, 40, 40, "Label text", 26, font, false);    // create checkbox
    
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

        myCheckbox.update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));     // update checkbox mouse check algorithm by current mouse position

        bool checkbox_state = myCheckbox.getState();    // get checkbox state to booleean value

        switch (checkbox_state)
        {
            case true:
            {
                myCheckbox.changeText("This is the checked checkbox");
                break;
            }
            case false:
            {
                myCheckbox.changeText("This is the unchecked checkbox");
                break;
            }
        }
        
        window.clear();
        window.draw(backgorund);
        myCheckbox.render(window);    // render checkbox on SFML window
        window.display();
    }
    
    return 0;
}