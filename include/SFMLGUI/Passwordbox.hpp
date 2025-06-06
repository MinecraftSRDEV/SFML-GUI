namespace sfg
{
    class Passwordbox {
    public:
        Passwordbox () {}

        /**
         * Creates and initializes the password box with specified parameters.
         *
         * @param x The x-coordinate of the password box.
         * @param y The y-coordinate of the password box.
         * @param size_x The width of the password box.
         * @param size_y The height of the password box.
         * @param active_value Initial active state of the password box.
         * @param cursorVisible_value Initial visibility state of the cursor.
         * @param font The font used for the text.
         * @param fontSize The size of the font.
         * @param defaultText The default text displayed in the password box.
         * @param readonly_default Initial read-only state.
         * @param label_text Text to be used as the label for the password box.
         */
        void create(int x, int y, int size_x, int size_y, bool active_value, bool cursorVisible_value, sf::Font& font, int fontSize, std::string defaultText = "", bool readonly_default = false, std::string label_text = "", int color = ColorPalete::Bright)
        {
            colorSet = color;

            if (size_x < 50)
            {
                size_x = 50;
            }

            background.setSize(sf::Vector2f((size_x - 50), size_y));
            backgroundSize = background.getSize();
            background.setOutlineThickness(1);

            text.setFont(font);
            text.setCharacterSize(fontSize);

            sampleText.setFont(font);
            sampleText.setCharacterSize(fontSize);
            
            cursor.setSize(sf::Vector2f(2.0f, fontSize));

            labelText.setFont(font);
            labelText.setCharacterSize(fontSize);
            labelText.setString(label_text);

            invisibleText.setFont(font);
            invisibleText.setCharacterSize(fontSize);

            labelText.setPosition(x + (background.getGlobalBounds().width / 2) - (labelText.getLocalBounds().width / 2), y);
            
            if (label_text == "")
            {
                background.setPosition(x, y);
            }
            else
            {
                background.setPosition(x, y + fontSize + 5);
            }

            showPasswordButton.create(0, 0, 50, size_y, font, "Show", false, color);
            
            updateTextPosition();

            showPasswordButton.changePosition(background.getPosition().x + background.getGlobalBounds().width, background.getPosition().y);

            read_only = readonly_default;
            setReadOnlyMode(read_only);
        }

        void setTheme(int color)
        {
            colorSet = color;

            background.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::inactive]);
            background.setOutlineColor(ColorPalete::Palete[colorSet][ColorPalete::outline]);
            text.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);
            sampleText.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);
            cursor.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);
            labelText.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);
            invisibleText.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);
            showPasswordButton.setTheme(colorSet);
        }

        /**
         * Sets the position of the password box on the window.
         *
         * @param position A vector representing the new position of the password box.
         */
        void setPosition(sf::Vector2f position) {
            background.setPosition(position);
            showPasswordButton.changePosition(background.getPosition().x + background.getGlobalBounds().width, background.getPosition().y);
            updateTextPosition();
        }

        /**
         * Sets the text inside the password box.
         *
         * @param inputText The text to be displayed in the password box.
         */
        void setText(std::string inputText)
        {
            if (read_only == false)
            {
                enteredText = inputText;
                text.setString(enteredText);
                character_position = enteredText.length();
                updateTextPosition();    
            }
        }

        /**
         * Handles events such as text input, key presses, and mouse clicks for the password box.
         *
         * @param event The event to handle.
         */
        void handleEvent(const sf::Event& event) {
            if (read_only == false)
            {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (background.getGlobalBounds().contains(mouse_position)) {
                        background.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::onmouse]);
                        active = true;
                        cursorClock.restart();
                    } else {
                        active = false;
                        background.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::inactive]);
                    }
                }

                if (active && event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8) { // Backspace key
                        if (!enteredText.empty()) {
                            std::string textFromTo = enteredText.substr(0, character_position);
                            textFromTo.pop_back();
                            textFromTo += enteredText.substr(character_position);
                            enteredText = textFromTo;
                            character_position--;
                        }
                    } else if (event.text.unicode < 128) {
                        if (text.getLocalBounds().width < background.getGlobalBounds().width)
                        {
                            std::string textFromTo = enteredText.substr(0, character_position);
                            textFromTo += static_cast<char>(event.text.unicode);
                            textFromTo += enteredText.substr(character_position);
                            enteredText = textFromTo;
                            character_position++;    
                        }
                    }
                    text.setString(enteredText);
                    updateTextPosition();
                }

                if (active && event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        if (character_position > 0)
                        {
                            character_position--;
                            updateTextPosition();
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Right)
                    {
                        character_position++;
                        updateTextPosition();
                    }
                    else if (event.key.code == sf::Keyboard::End)
                    {
                        character_position = enteredText.length();
                        updateTextPosition();
                    }
                    else if (event.key.code == sf::Keyboard::Home)
                    {
                        character_position = 0;
                        updateTextPosition();
                    }
                    else if (event.key.code == sf::Keyboard::Delete)
                    {
                        if (!enteredText.empty()) {
                            if (enteredText.length() >= character_position + 1)
                            {
                                std::string textFromTo = enteredText.substr(0, character_position + 1);
                                textFromTo.pop_back();
                                textFromTo += enteredText.substr(character_position + 1);
                                enteredText = textFromTo;
                                text.setString(enteredText);
                                updateTextPosition();    
                            }
                        }
                    }
                }
            }
        }

        /**
         * Updates the state of the password box, particularly the blinking cursor.
         */
        void update(sf::Vector2f& mouse) {
            mouse_position = mouse;
            if (active && cursorClock.getElapsedTime() >= cursorBlinkTime) {
                cursorVisible = !cursorVisible;
                cursorClock.restart();
                mouse_position = mouse;
            }

            if (cachedFunction != nullptr)
            {
                if (onChange_clock.getElapsedTime() > onChantge_detectTime)
                {
                    if (onchange_runned == false)
                    cachedFunction();
                    onchange_runned = true;
                }
            }

            showPassword = showPasswordButton.update(mouse);
        }

        /**
         * Renders the password box and its components (masked text, cursor, etc.) to the window.
         *
         * @param window The render window where the password box will be drawn.
         */
        void render(sf::RenderWindow& window) {
            window.draw(labelText);
            window.draw(background);

            if (showPassword == sfgComponents::States::noMouse)
            {
                window.draw(invisibleText);
            }
            else if (showPassword == sfgComponents::States::onMouse)
            {
                window.draw(text);    
            }

            if (active && cursorVisible && showPassword == sfgComponents::States::noMouse) {
                if (read_only == false)
                {
                    window.draw(cursor);
                }
                
            }

            showPasswordButton.render(window);
        }

        /**
         * Sets the read-only mode for the password box.
         * When in read-only mode, the password box cannot be edited.
         *
         * @param state True to enable read-only mode, false to disable it.
         */
        void setReadOnlyMode(bool state)
        {
            read_only = state;

            if (state == true)
            {
                background.setOutlineColor(ColorPalete::Palete[colorSet][ColorPalete::blocked]);
            }
            else
            {
                background.setOutlineColor(ColorPalete::Palete[colorSet][ColorPalete::outline]);
            }
        }

        /**
         * Gets the current text entered in the password box.
         *
         * @return The text currently in the password box.
         */
        std::string getText()
        {
            return enteredText;
        }

        sf::Vector2f getBoxPosition()
        {
            return background.getPosition();
        }

        typedef void (*FunctionType)();
        void setOnChangeFunction(FunctionType function)
		{
			cachedFunction = function;
		}

    private:
        /**
         * Updates the position of the text and cursor within the password box.
         * Masks the text with asterisks for privacy.
         */
        void updateTextPosition() {
            try
            {
                sf::FloatRect textBounds = text.getLocalBounds();
                float x = background.getPosition().x + 10.0f;
                float y = background.getPosition().y + (backgroundSize.y - textBounds.height) / 2 - textBounds.top;
                text.setPosition(x, y);
                invisibleText.setPosition(x, y);

                int charcount = enteredText.length();
                std::string invtext;
                for (charcount > 0; charcount--;)
                {
                    invtext += "*"; 
                }
                invisibleText.setString(invtext);

                sampleText.setPosition(text.getPosition());

                sampleText.setString(invtext.substr(0, character_position));

                // cursor.setPosition(x + textBounds.width + 5.0f, y);
                cursorVisible = true;
                cursorClock.restart();
                cursor.setPosition(x + sampleText.getLocalBounds().width, y); 

                onChange_clock.restart();
                onchange_runned = false;   
            }
            catch (std::exception e)
            {
                character_position++;
            }
        }

        sf::RectangleShape background;
        sf::Vector2f backgroundSize;
        sf::Text text;
        sf::Text invisibleText;
        sf::Text sampleText;
        sf::Text labelText;
        sf::RectangleShape cursor;
        sf::Vector2f mouse_position;
        bool active;
        bool cursorVisible;
        bool read_only;
        bool showPassword = false;
        int character_position = 0;
        int colorSet;
        sf::Clock cursorClock;
        sf::Time cursorBlinkTime = sf::seconds(0.5f);
        std::string enteredText;
        sf::Time onChantge_detectTime = sf::seconds(2);
        sf::Clock onChange_clock;
        bool onchange_runned = true;

        Button showPasswordButton;

        FunctionType cachedFunction = nullptr;
    };    
}