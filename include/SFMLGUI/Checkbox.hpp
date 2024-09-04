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
	
	void create (int sizeX, int sizeY, int posX, int posY, std::string text, int fontsize, sf::Font& font, bool defaultState)
	{	
		squareBox.setOutlineColor(sf::Color(0,0,0));
		squareBox.setOutlineThickness(1);
		
		if (defaultState == false) {
			squareBox.setFillColor(sf::Color(255,255,255));
		} else {
			squareBox.setFillColor(sf::Color(0,0,255));
		}
		chk_state = defaultState;
		
		squareBox.setSize(sf::Vector2f(sizeX, sizeY));
		squareBox.setPosition(posX, posY);
		
		textBox.setCharacterSize(fontsize);
		textBox.setFillColor(sf::Color::Black);
		textBox.setFont(font);

		changeText(text);
	}
	
	void render (sf::RenderWindow& targetWindow)
	{
		targetWindow.draw(squareBox);
		targetWindow.draw(textBox);
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
				squareBox.setFillColor(sf::Color(0,0,255));
				break;
			}
			case true: {
				chk_state = false;
				squareBox.setFillColor(sf::Color(255,255,255));
				break;
			}
		}
	}

	void setState(bool state)
	{
		chk_state = state;
		switch (chk_state)
		{
			case false: {
				squareBox.setFillColor(sf::Color(0,0,255));
				break;
			}
			case true: {
				squareBox.setFillColor(sf::Color(255,255,255));
				break;
			}
		}
	}

	void update(sf::Vector2f mouse_pos)
	{
		switch (chk_state)
		{
			case true:
			{
				if (hitbox().contains(mouse_pos) or hitboxText().contains(mouse_pos))
				{
					squareBox.setFillColor(sf::Color(0,0,255, 128));

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mouse_state = true;

						if (mouse_release == false)
						{
							mouse_release = true;
							squareBox.setFillColor(sf::Color(0,0,255, 64));
							changeState();	
						}
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
					squareBox.setFillColor(sf::Color(0,0,255, 255));
					mouse_state = false;
				}
				break;
			}
			case false:
			{
				if (hitbox().contains(mouse_pos) or hitboxText().contains(mouse_pos))
				{
					squareBox.setFillColor(sf::Color(255,255,255, 128));

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mouse_state = true;

						if (mouse_release == false)
						{
							mouse_release = true;
							squareBox.setFillColor(sf::Color(255,255,255, 64));
							changeState();	
						}	
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
					squareBox.setFillColor(sf::Color(255,255,255, 255));
					mouse_state = false;
				}
				break;
			}
		}
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

private:
	sf::RectangleShape squareBox;
	sf::Text textBox;
	bool chk_state;

	bool mouse_state = false;
	bool mouse_release = false;
};
