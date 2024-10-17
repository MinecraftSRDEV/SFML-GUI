namespace sfg
{
    class TransparrentBackground {
    public:
    TransparrentBackground () {}

    void create(int x, int y, int size_x, int size_y, bool outline = false, int color = ColorPalete::Bright)
    {
        bg.setSize(sf::Vector2f(size_x, size_y));
        bg.setPosition(x, y);
        
        outlined = outline;
        colorSet = color;
        setTheme(colorSet);
    }

    void setTheme(int color)
    {
        colorSet = color;
        bg.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::halftransparrent]);
        if (outlined == true)
        {
            bg.setOutlineColor(ColorPalete::Palete[colorSet][ColorPalete::outline]);
            bg.setOutlineThickness(1);
        }
    }

    void setColorPalete(int palete)
    {
        colorSet = palete;
    }

    void render(sf::RenderWindow& window)
    {
        window.draw(bg);
    }

    private:

    int colorSet;
    bool outlined;

    sf::RectangleShape bg;
    };
}
