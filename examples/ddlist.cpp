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
    window.create(sf::VideoMode(800, 600), "SFML-GUI DropDown list Example");
    sf::RectangleShape backgorund;
    backgorund.setFillColor(sf::Color::Green);
    backgorund.setSize(sf::Vector2f(800, 600));
    
    sf::Font font;

    font.loadFromFile("Arial.ttf");

    sfg::DropDownList myDdlist;    // declarate ddl
    myDdlist.create(200, 50, 100, 100, {{"Option 1","Result 1"}, {"Option 2","Result 2"},{"Option 3","Result 3"}}, "Option 1", font, false);    // create ddl
    
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
        myDdlist.update(mousePos);     // update ddl mouse check algorithm by current mouse position
        
        window.clear();
        window.draw(backgorund);
        myDdlist.render(window);    // render ddl on SFML window
        window.display();
    }
    
    return 0;
}