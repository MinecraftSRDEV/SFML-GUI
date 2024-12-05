namespace sfg
{
    // class Slider {
    // private:
    //     sf::RectangleShape track;
    //     sf::RectangleShape thumb;
    //     float minValue;
    //     float maxValue;
    //     float currentValue;
    //     bool isDragging;

    // public:
    //     Slider() {}

    //     void create(float x, float y, float width, float height, float minValue, float maxValue, float startValue, sf::Font& font, int fontsize, std::string inputLabel)
    //     {
    //         track.setSize(sf::Vector2f(width, height));
    //         track.setPosition(x, y);
    //         track.setFillColor(sf::Color::White);

    //         thumb.setSize(sf::Vector2f(height, height));
    //         thumb.setPosition(x, y);
    //         thumb.setFillColor(sf::Color::Red);
    //     }

    //     void render(sf::RenderWindow& window) {
    //         window.draw(track);
    //         window.draw(thumb);
    //     }

    //     void handleEvent(const sf::Event& event) {
    //         if (event.type == sf::Event::MouseButtonPressed) {
    //             if (thumb.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
    //                 isDragging = true;
    //                 thumb.setFillColor(sf::Color::Blue);
    //             }
    //         } else if (event.type == sf::Event::MouseButtonReleased) {
    //             isDragging = false;
    //             thumb.setFillColor(sf::Color::Red);
    //         } else if (event.type == sf::Event::MouseMoved) {
    //             if (isDragging) {
    //                 float newX = static_cast<float>(event.mouseMove.x) - thumb.getSize().x / 2;
    //                 float trackX = track.getPosition().x;
    //                 float trackWidth = track.getSize().x;
    //                 if (newX < trackX) newX = trackX;
    //                 if (newX > trackX + trackWidth - thumb.getSize().x) newX = trackX + trackWidth - thumb.getSize().x;
    //                 thumb.setPosition(newX, thumb.getPosition().y);
    //                 currentValue = minValue + (maxValue - minValue) * ((thumb.getPosition().x - trackX) / (trackWidth - thumb.getSize().x));
    //             }
    //         }
    //     }

    //     float getValue() const {
    //         return currentValue;
    //     }
    // };


    class Slider {
    public:
        void create(int pos_x, int pos_y, int size_x, int size_y, float minValue, float maxValue, float startValue, sf::Font& font, int fontsize, std::string inputLabel = "")
        {
            background.setFillColor(sf::Color::White);
            background.setOutlineColor(sf::Color::Black);
            background.setOutlineThickness(1);
            background.setPosition(pos_x, pos_y);
            background.setSize(sf::Vector2f(size_x, size_y));

            bgWidth = size_x;
            bgHeight = size_y;

            slider.setFillColor(sf::Color::White);
            slider.setOutlineColor(sf::Color::Black);
            slider.setOutlineThickness(3);
            slider.setSize(sf::Vector2f(7, size_y));
            setSliderPositionFromValue(startValue);

            label.setFont(font);
            label.setCharacterSize(fontsize);
            label.setFillColor(sf::Color::Black);

            labelText = inputLabel;

            changeText(labelText + ": " + formatValue());
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
                changeText(labelText + ": " + formatValue());
            }
        }

        void render(sf::RenderWindow& window) {
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
            changeText(labelText + ": " + formatValue());
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

        std::string formatValue()
        {
            // float currentValue = getValue();
            // float trackX = background.getPosition().x;
            // float trackWidth = background.getSize().x;
            // return std::to_string(currentValue = minValue + (maxValue - minValue) * ((slider.getPosition().x - trackX) / (trackWidth - slider.getSize().x)));
            int covert = getValue();
            std::string outout = std::to_string(covert);
            return outout;
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
}
