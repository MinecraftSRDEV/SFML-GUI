namespace sfg
{
	class Checkbox{

	public:

		Checkbox () {}
		
		void textAlign(int sizeX)
		{
			sf::FloatRect rectangleBounds = squareBox.getGlobalBounds();
			sf::FloatRect textBounds = textBox.getLocalBounds();
		
			float textX = rectangleBounds.left + sizeX + 5;
			float textY = rectangleBounds.top + (rectangleBounds.height - textBounds.height) / 2 - textBounds.top;
			
			textBox.setPosition(textX, textY);
		}

		void setTheme(int color)
		{
			colorSet = color;
			squareBox.setOutlineColor(ColorPalete::Palete[color][ColorPalete::outline]);

			if (chk_state == false) {
				squareBox.setFillColor(ColorPalete::Palete[color][ColorPalete::inactive]);
			} else {
				squareBox.setFillColor(ColorPalete::Palete[color][ColorPalete::checkbox_inactive]);
			}

			textBox.setFillColor(ColorPalete::Palete[color][ColorPalete::font]);
		}
		
		void create (int sizeX, int sizeY, int posX, int posY, std::string text, int fontsize, sf::Font& font, bool defaultState, int color = ColorPalete::Bright)
		{	
			colorSet = color;

			squareBox.setOutlineThickness(1);
			
			chk_state = defaultState;

			setTheme(color);
			
			squareBox.setSize(sf::Vector2f(sizeX, sizeY));
			squareBox.setPosition(posX, posY);
			
			textBox.setCharacterSize(fontsize);
			textBox.setFont(font);

			changeText(text);
		}
		
		void render (sf::RenderWindow& targetWindow)
		{
			targetWindow.draw(squareBox);
			targetWindow.draw(textBox);
		}

		void changePosition(int posX, int posY)
		{
			squareBox.setPosition(posX, posY);
			textAlign(squareBox.getSize().x);
		}
		
		void changeText(std::string input)
		{
			textBox.setString(input);
			textAlign(squareBox.getSize().x);
		}
		
		void changeState()
		{
			switch (chk_state)
			{
				case false: {
					chk_state = true;
					// *binded_varriable = chk_state;
					squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::checkbox_inactive]);
					break;
				}
				case true: {
					chk_state = false;
					// *binded_varriable = chk_state;
					squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::inactive]);
					break;
				}
			}
			if (cachedFunction != nullptr)
			{
				cachedFunction();	
			}
		}

		void setState(bool state)
		{
			chk_state = state;
			// *binded_varriable = chk_state;
			switch (chk_state)
			{
				case false: {
					squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::checkbox_inactive]);
					break;
				}
				case true: {
					squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::inactive]);
					break;
				}
			}
		}

		int update(sf::Vector2f mouse_pos)
		{
			if (blocked == false)
			{
				switch (chk_state)
				{
					case true:
					{
						if (hitbox().contains(mouse_pos))
						{
							squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::checkbox_onmouse]);

							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								mouse_state = true;

								if (mouse_release == false)
								{
									mouse_release = true;
									squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::checkbox_active]);
									changeState();
									return sfgComponents::States::isMouseClicked;
								}
								return sfgComponents::States::onMouse;
							}
							else
							{
								mouse_state = false;
								if (mouse_release == true)
								{
									mouse_release = false;
								}
							}
						}
						else
						{
							squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::checkbox_inactive]);
							mouse_state = false;
						}
						break;
					}
					case false:
					{
						if (hitbox().contains(mouse_pos))
						{
							squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::onmouse]);

							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								mouse_state = true;

								if (mouse_release == false)
								{
									mouse_release = true;
									squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::active]);
									changeState();
									return sfgComponents::States::isMouseClicked;
								}	
								return sfgComponents::States::onMouse;
							}
							else
							{
								mouse_state = false;
								if (mouse_release == true)
								{
									mouse_release = false;
								}
							}
						}
						else
						{
							squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::inactive]);
							mouse_state = false;
						}
						break;
					}
				}	
			}
			else
			{
				squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::inactive]);
			}
			return sfgComponents::States::noMouse;
		}

		void setColorPalete(int palete)
		{
			colorSet = palete;
		}
		
		sf::FloatRect hitbox()
		{
			return squareBox.getGlobalBounds();
		}
		sf::FloatRect hitboxText()
		{
			return textBox.getLocalBounds();
		}
		
		bool getState()
		{
			return chk_state;
		}

		typedef void (*FunctionType)();

		void setFunction(FunctionType function)
		{
			cachedFunction = function;
		}

		void setBlockState(bool state)
		{
			blocked = state;
			squareBox.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::blocked]);
		}

	private:
		sf::RectangleShape squareBox;
		sf::Text textBox;
		bool chk_state;

		int colorSet;

		bool mouse_state = false;
		bool mouse_release = false;

		bool blocked = false;

		FunctionType cachedFunction = nullptr;
	};
}
