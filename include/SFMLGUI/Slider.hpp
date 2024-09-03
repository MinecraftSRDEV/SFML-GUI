class Slider {
public:
    void create(int pos_x, int pos_y, int size_x, int size_y, float minValue, float maxValue, float startValue,sf::Font& font, int fontsize, std::string inputLabel = "") {

        background.setFillColor(sf::Color::White);
        background.setOutlineColor(sf::Color::Black);
        background.setOutlineThickness(1);
        background.setPosition(pos_x, pos_y);

        bgWidth = size_x;
        bgHeight = size_y;

        slider.setFillColor(sf::Color::White);
        slider.setOutlineColor(sf::Color::Black);
        slider.setOutlineThickness(1);
        setSliderPositionFromValue(startValue);

        label.setFont(font);
        label.setCharacterSize(fontsize);
        label.setFillColor(sf::Color::Black);

        changeText(labelText + ": " + formatValue(getValue()));
    }

    float getValue()
    {
        float sliderPosition = slider.getPosition().x - (background.getPosition().x);
        float range = bgWidth - slider.getGlobalBounds().width;
        return minValue + ((sliderPosition / range) * (maxValue - minValue));
    }

    void changeText(std::string newText) {
        label.setString(newText);
        positionText();
    }

    void handleEvent(const sf::Event& event,sf::RenderWindow& window) {
        switch (event.type) {
            case sf::Event::MouseMoved:
                updateHoverState(window);
                break;
            case sf::Event::MouseButtonPressed:
                handleMousePress(event.mouseButton, window);
                break;
            case sf::Event::MouseButtonReleased:
                isDragging = false;
                break;
            case sf::Event::MouseWheelScrolled:
                handleScroll(event.mouseWheelScroll);
                break;
            default:
                break;
        }

        if (isDragging && event.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            float newPos = mousePos.x - dragOffset;
            moveSliderTo(newPos);
            changeText(labelText + ": " + formatValue(getValue()));
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(slider);
        window.draw(label);
    }

private:
    sf::Vector2f position;
    sf::RectangleShape background;
    sf::RectangleShape slider;
    sf::Text label;

    std::string labelText;

    float minValue;
    float maxValue;
    bool isDragging;
    float dragOffset;
    bool isOnMouse;
    int bgWidth;
    int bgHeight;

    void updateHoverState(sf::RenderWindow& window)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (background.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isOnMouse = true;
        }
        else
        {
            isOnMouse = false;
        }

        if (slider.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            slider.setOutlineColor(sf::Color::Blue);
        }
        else
        {
            slider.setOutlineColor(sf::Color::Black);
        }
    }

    void handleMousePress(const sf::Event::MouseButtonEvent& mouseEvent,sf::RenderWindow& window)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (slider.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            isDragging = true;
            dragOffset = mousePos.x - slider.getPosition().x;
        }
    }

    void handleScroll(const sf::Event::MouseWheelScrollEvent& scrollEvent)
    {
        if (isOnMouse == true)
        {
            moveSlider(scrollEvent.delta * 10);    
        }
        
    }

    void moveSlider(float offset) {
        float newPos = slider.getPosition().x + offset;
        moveSliderTo(newPos);
        changeText(labelText + ": " + formatValue(getValue()));
    }

    void moveSliderTo(float positionX) {
        float leftLimit = background.getPosition().x;
        float rightLimit = background.getPosition().x + background.getSize().x - slider.getGlobalBounds().width;

        if (positionX < leftLimit)
        {
            positionX = leftLimit;
        }
        else if (positionX > rightLimit)
        {
            positionX = rightLimit;
        }

        slider.setPosition(positionX, background.getPosition().y);
    }

    void positionText() {
        label.setPosition(background.getPosition().x + background.getSize().x / 2 - label.getLocalBounds().width / 2, background.getPosition().y + background.getSize().y + 5 - label.getLocalBounds().height / 2);
    }

    std::string formatValue(float value)
    {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(0) << value;
        return stream.str();
    }

    void setSliderPositionFromValue(float value) {
        float range = maxValue - minValue;
        float positionRatio = (value - minValue) / range;

        float leftLimit = background.getPosition().x;
        float rightLimit = background.getPosition().x + background.getSize().x - slider.getGlobalBounds().width;
        float positionX = leftLimit + positionRatio * (rightLimit - leftLimit);

        slider.setPosition(positionX, background.getPosition().y + (background.getSize().y - slider.getGlobalBounds().height) / 2);
    }
};