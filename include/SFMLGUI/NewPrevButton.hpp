namespace sfg
{
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
			labelText.setAttributes(24, inputText);
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
		void create(int posX, int posY, int sizeX, int sizeY, sf::Font& font, std::string input_text, bool block_state = false, int color = ColorPalete::Bright)
		{
			body.init();

			body.colorSet = color;

			body.setAttributes(sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY));

			labelText.init(body);
			
			labelText.setFont(font);
			
			setText(input_text);

			setBlockState(block_state);

			setTheme(body.colorSet);

			clickEvent.init(body);
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
			body.setAttributes(sf::Vector2f(posX, posY), sf::Vector2f(body.getPointer().getGlobalBounds().width, body.getPointer().getGlobalBounds().height));
			labelText.allignText();
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
			body.render(targetWindow);
			labelText.render(targetWindow);
		}

		void setTheme(int color)
		{
			body.setColor(color);
			labelText.setColor(color);
		}

		/**
		 * Updates the button's state based on mouse position and interaction.
		 * 
		 * This function detects mouse interactions, changes the button's appearance when hovered,
		 * and calls the bound function when clicked.
		 * 
		 * @param mouse_pos Current position of the mouse cursor as a vector.
		 * 
		 * @returns 0 = no mouse, 1 = mouse contains, 2 = mouse clicked
		 */
		int update(sf::Vector2f& mouse_pos)
		{
			return clickEvent.update(mouse_pos);
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
			return body.getPointer().getGlobalBounds();
		}
		
		/**
		 * Retrieves the current position of the button.
		 * 
		 * @return A Vector2f representing the button's position in the window.
		 */
		sf::Vector2f getPosition()
		{
			return body.getPointer().getPosition();
		}

		/**
		 * Sets the function to be called when the button is clicked.
		 * 
		 * This function binds a user-defined function to the button's click event.
		 * 
		 * @param function A pointer to the function to be executed on button click.
		 */
		void setFunction(sfgComponents::ButtonClickEvent::FunctionType function)
		{
			clickEvent.bindFunction(function);
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
			clickEvent.setBlockState(state);
		}
		
	private:
		sfgComponents::ButtonBody body;
		sfgComponents::ButtonClickEvent clickEvent;
		sfgComponents::ButtonLabelText labelText;
	};
}
