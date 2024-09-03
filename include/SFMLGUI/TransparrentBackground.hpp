class TransparrentBackground {
public:
TransparrentBackground () {}

void create(int x, int y, int size_x, int size_y, bool outline = false)
{
    bg.setSize(sf::Vector2f(size_x, size_y));
    bg.setPosition(x, y);
    bg.setFillColor(sf::Color(255,255,255, 128));

    if (outline == true)
    {
        bg.setOutlineColor(sf::Color::Black);
        bg.setOutlineThickness(1);
    }
}

void render(sf::RenderWindow& window)
{
    window.draw(bg);
}

private:

sf::RectangleShape bg;
};