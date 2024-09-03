/**
 * Simple SFML clickable object with a one-time bound function that is executed upon clicking.
 * 
 * Use the "create" function to add button parameters.
 * 
 * To work correctly, the following functions need to be added to the main loop:
 * - render(pointer to window) for displaying on the window.
 * - update(pointer to Vector2f with mouse position) for click detection.
 * 
 * To bind a function, use setFunction(function name).
 */
class Button {
public:
	Button () {}
	
	/**
     * Sets the text displayed on the button.
     * 
     * The text is automatically centered within the button.
     * 
     * @param inputText The string to be displayed on the button.
     */
	void setText(std::string inputText)
	{
		buttonText.setCharacterSize(24);
		buttonText.setString(inputText);
		allingText();
	}
	
	/**
     * Initializes the button's properties including size, position, font, and text.
     * 
     * @param posX X-coordinate of the button's position on the window.
     * @param posY Y-coordinate of the button's position on the window.
     * @param sizeX Width of the button.
     * @param sizeY Height of the button.
     * @param font Reference to the font used for the button text.
     * @param input_text The text to be displayed on the button.
     * @param block_state Optional parameter to set the button's initial blocked state (default is false).
     */
	void create(int posX, int posY, int sizeX, int sizeY, sf::Font& font, std::string input_text, bool block_state = false)
	{
		width = sizeX;
		height = sizeY;
		
		button.setOutlineColor(sf::Color::Black);
		button.setOutlineThickness(1);
		
		button.setFillColor(sf::Color(255,255,255));
		
		button.setSize(sf::Vector2f(sizeX, sizeY));
		button.setPosition(posX, posY);
		
		buttonText.setFont(font);
		buttonText.setFillColor(sf::Color::Black);
		setText(input_text);

		blocked = block_state;
	}

	/**
     * Changes the position of the button.
     * 
     * This function updates the button's position on the window.
     * 
     * @param posX New X-coordinate of the button's position.
     * @param posY New Y-coordinate of the button's position.
     * 
     * Accepts only constant variables.
     */
	void changePosition(int posX, int posY)
	{
		button.setPosition(posX, posY);
		allingText();
	}
	
	/**
     * Renders the button and its text onto the given window.
     * 
     * This function should be called in the main rendering loop to display the button.
     * 
     * @param targetWindow The SFML window where the button will be drawn.
     */
	void render(sf::RenderWindow& targetWindow)
	{
		targetWindow.draw(button);
		targetWindow.draw(buttonText);
	}

	/**
     * Updates the button's state based on mouse position and interaction.
     * 
     * This function detects mouse interactions, changes the button's appearance when hovered,
     * and calls the bound function when clicked.
     * 
     * @param mouse_pos Current position of the mouse cursor as a vector.
     */
	void update(sf::Vector2f mouse_pos)
	{
		if (blocked == false)
		{
			if (hitbox().contains(mouse_pos))
			{
				button.setFillColor(sf::Color(255,255,255, 128));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					mouse_state = true;
					mouse_release = true;

					button.setFillColor(sf::Color(255,255,255, 64));
				}
				else
				{
					mouse_state = false;
					if (mouse_release == true)
					{
						mouse_release = false;

						if (cachedFunction)
						{
							cachedFunction();
						}
					}
				}
			}
			else
			{
				button.setFillColor(sf::Color(255,255,255, 255));
				mouse_state = false;
			}	
		}
		else
		{
			button.setFillColor(sf::Color(176,176,176));
		}
	}
	
	/**
     * Returns the button's hitbox as a rectangle.
     * 
     * This is used for detecting mouse interactions with the button.
     * 
     * @return A FloatRect representing the button's bounding box.
     */
	sf::FloatRect hitbox()
	{
		return button.getGlobalBounds();
	}
	
	/**
     * Retrieves the current position of the button.
     * 
     * @return A Vector2f representing the button's position in the window.
     */
	sf::Vector2f getPosition()
	{
		return button.getPosition();
	}

	typedef void (*FunctionType)();

	/**
     * Sets the function to be called when the button is clicked.
     * 
     * This function binds a user-defined function to the button's click event.
     * 
     * @param function A pointer to the function to be executed on button click.
     */
	void setFunction(FunctionType function)
	{
		cachedFunction = function;
	}

	/**
     * Sets the blocked state of the button.
     * 
     * When blocked, the button does not respond to mouse interactions.
     * 
     * @param state The new blocked state of the button (true or false).
     */
	void setBlockState(bool state)
	{
		blocked = state;
	}
	
private:

	/**
     * Centers the text within the button.
     * 
     * This method adjusts the scale and position of the text to ensure
     * it is displayed in the center of the button.
     */
	void allingText()
	{
		float scaleX = (width - 20) / buttonText.getLocalBounds().width;
        float scaleY = (height - 20) / buttonText.getLocalBounds().height;
        float scale = std::min(scaleX, scaleY);
        buttonText.setScale(scale, scale);

        sf::FloatRect textRect = buttonText.getLocalBounds();
        buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        float posX = button.getPosition().x + width / 2.0f;
        float posY = button.getPosition().y + height / 2.0f;
        buttonText.setPosition(posX, posY);
	}

	sf::RectangleShape button;
	sf::Text buttonText;
	int width;
	int height;

	bool mouse_state = false;
	bool mouse_release = false;

	bool blocked = false;

	FunctionType cachedFunction = nullptr;
};
