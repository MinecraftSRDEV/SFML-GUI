namespace sfg
{
	class DropDownList {
	public:
		DropDownList () {}
		
		/**
		 * Adds an option to the dropdown list.
		 * This function generates a texture for the option text and maps it to the corresponding result.
		 * 
		 * @param optionText The text displayed for the option.
		 * @param result The value associated with the option.
		 */
		void addOption(std::string optionText,std::string result)
		{
			genTexture(optionText, sizeX_global, sizeY_global, optionText, texturesMap);
			option.setTexture(texturesMap[optionText]);
			
			options_list[optionText] = option;
			results_list[optionText] = result;

			options_added.emplace_back(optionText, result);
		}
		
		/**
		 * Changes the currently selected option in the dropdown list.
		 * The function updates the displayed texture to match the selected option.
		 * 
		 * @param optionChoosed The text of the option to select.
		 */
		void changeSelection(std::string optionChoosed)
		{
			dropped = false;
			selectedOpiton.setTexture(*options_list[optionChoosed].getTexture());
			selected_option = results_list[optionChoosed];
		}

		/**
		 * Adds multiple options to the dropdown list.
		 * 
		 * @param options A map of option texts to their corresponding results {option, result}.
		 */
		void add_options(std::map <std::string, std::string>options)
		{
			for (const auto& pair : options) {
				addOption(pair.first, pair.second);
				options_list[pair.first].setPosition(posX_global, lastY += sizeY_global);
			}
		}

		/**
		 * Sets the block state of the dropdown list.
		 * When blocked, the dropdown list is disabled and cannot be interacted with.
		 * 
		 * @param state The block state, true for blocked and false for unblocked.
		 */
		void setBlockState(bool state)
		{
			blocked = state;
		}

		/**
		 * Creates and initializes the dropdown list.
		 * Sets up the dropdown button, default selected option, and adds all provided options.
		 * 
		 * @param sizeX The width of the dropdown list.
		 * @param sizeY The height of the dropdown list.
		 * @param posX The X position of the dropdown list on the window.
		 * @param posY The Y position of the dropdown list on the window.
		 * @param options A map of option texts to their corresponding results.
		 * @param default_selected The text of the option to be selected by default (option -> default result).
		 * @param font The font to be used for the option texts.
		 * @param block_state Initial block state, true for blocked and false for unblocked.
		 */
		void create(int sizeX, int sizeY, int posX, int posY, std::map <std::string, std::string>options, std::string default_selected, sf::Font& font, bool block_state = false, int color = ColorPalete::Bright)
		{
			colorSet = color;

			defaultFont = font;

			defaultOption = default_selected;
			
			int posY2 = posY;
			selectedOpiton.setPosition(posX, posY2);
			
			sizeX_global = sizeX;
			sizeY_global = sizeY;
			posX_global = posX;
			posY_global = posY;
			lastY = posY_global;
			add_options(options);

			setTheme(color);
			
			selectedOpiton.setTexture(*options_list[default_selected].getTexture());
			
			dropButton.setPosition(posX + sizeX, posY);
			
			blocked = block_state;
		}

		void setTheme(int color)
		{
			colorSet = color;
			lastY = posY_global;

			genTexture("\\/", 20, sizeY_global, "Drop", texturesMap);
			dropButton.setTexture(texturesMap["Drop"]);

			std::vector <std::pair <std::string, std::string>> options_added_temp = options_added;
			options_added.clear();
			for (const auto& pair : options_added_temp)
			{
				std::map <std::string, std::string> tempmap;
				tempmap[pair.first] = pair.second;
				add_options(tempmap);
			}
		}
		
		/**
		 * Renders the dropdown list on the specified window.
		 * Displays the drop button, selected option, and all dropdown options if the list is dropped.
		 * 
		 * @param targetWindow The render window where the dropdown list will be displayed.
		 */
		void render(sf::RenderWindow& targetWindow)
		{
			windowsize = targetWindow.getSize();
			if (dropped == true)
			{
				for (const auto& pair : options_list) {
					if (pair.second.getPosition().y > selectedOpiton.getPosition().y)
					{
						targetWindow.draw(pair.second);	
					}
				}	
			}
			
			targetWindow.draw(dropButton);
			targetWindow.draw(selectedOpiton);
		}
		
		/**
		 * Toggles the dropped state of the dropdown list.
		 * Opens or closes the dropdown list based on its current state.
		 */
		void toggle()
		{
			if (blocked == false)
			{
				switch (dropped)
				{
					case true: {
						dropped = false;
						break;
					}
					case false: {
						dropped = true;
						break;
					}
				}	
			}
			else
			{
				dropped = false;
			}
		}

		/**
		 * Updates the dropdown list based on the mouse position.
		 * Handles interactions like opening/closing the list, selecting options, and changing button colors.
		 * 
		 * @param mouse The current mouse position.
		 */
		void update(sf::Vector2f& mouse)
		{
			options_list.erase("");

			if (blocked == false)
			{
				if (dropHitbox().contains(mouse))
				{
					dropButton.setColor(ColorPalete::Palete[colorSet][ColorPalete::onmouse]);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mouse_state = true;
						mouse_release = true;

						dropButton.setColor(ColorPalete::Palete[colorSet][ColorPalete::active]);
					}
					else
					{
						mouse_state = false;
						if (mouse_release == true)
						{
							mouse_release = false;

							toggle();
						}
					}
				}
				else
				{
					dropButton.setColor(sf::Color(255,255,255));
					mouse_state = false;
				}

				if (selectedOpiton.getGlobalBounds().contains(mouse))
				{
					selectedOpiton.setColor(ColorPalete::Palete[colorSet][ColorPalete::onmouse]);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mouse_state = true;
						mouse_release = true;

						selectedOpiton.setColor(ColorPalete::Palete[colorSet][ColorPalete::active]);
					}
					else
					{
						mouse_state = false;
						if (mouse_release == true)
						{
							mouse_release = false;

							toggle();
						}
					}
				}
				else
				{
					selectedOpiton.setColor(sf::Color(255,255,255));
					mouse_state = false;
				}

				if (dropped == true)
				{
					for (const auto& pair : options_list)
					{
						options_list[pair.first].setColor(sf::Color(255,255,255));
					}

					std::string sprite_under_mouse = getSpriteUnderMouse(mouse);

					if (options_list[sprite_under_mouse].getGlobalBounds().contains(mouse))
					{
						options_list[sprite_under_mouse].setColor(ColorPalete::Palete[colorSet][ColorPalete::onmouse]);

						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							mouse_state = true;
							mouse_release = true;

							options_list[sprite_under_mouse].setColor(ColorPalete::Palete[colorSet][ColorPalete::active]);
						}
						else
						{
							mouse_state = false;
							if (mouse_release == true)
							{
								mouse_release = false;

								setFromResult(results_list[sprite_under_mouse]);
								if (cachedFunction != nullptr)
								{
									cachedFunction();	
								}
							}
						}
					}
					else
					{
						options_list[sprite_under_mouse].setColor(sf::Color(255,255,255));
						mouse_state = false;
					}
				}	
			}
			else
			{
				dropped = false;
				dropButton.setColor(ColorPalete::Palete[colorSet][ColorPalete::blocked]);
				selectedOpiton.setColor(ColorPalete::Palete[colorSet][ColorPalete::blocked]);
			}
		}

		/**
		 * Handles scroll events for the dropdown list.
		 * Allows scrolling through the list of options when the list is dropped.
		 * 
		 * @param event The scroll event captured by the window.
		 */
		void scrollEvent(sf::Event event)
		{
			if (event.type == sf::Event::MouseWheelMoved)
			{
				int mouse_scroll = event.mouseWheel.delta;

				if (mouse_scroll > 0)
				{
					auto firstElement = options_added.begin();
					firstKey = firstElement->first;
					int mp = event.mouseWheel.delta;
                    while (mp > 0)
                    {
						if (options_list[firstKey].getPosition().y < selectedOpiton.getPosition().y + sizeY_global)
						{
							for (const auto& pair : options_list)
							{
								options_list[pair.first].setPosition(options_list[pair.first].getPosition().x, options_list[pair.first].getPosition().y + sizeY_global);
							}	
						}    
                        mp--;
                    }
				}
				else
				{
					auto lastElement = std::prev(options_added.end());
					int mp = event.mouseWheel.delta;
                    while (mp < 0)
                    {
						if (options_list[lastElement->first].getPosition().y + options_list[lastElement->first].getGlobalBounds().width < windowsize.y - sizeY_global);
						{
							for (const auto& pair : options_list)
							{
								options_list[pair.first].setPosition(options_list[pair.first].getPosition().x, options_list[pair.first].getPosition().y - sizeY_global);
							}  	
						}
                        mp++;
                    }
				}
			}
		}
		
		/**
		 * Returns the bounding box of the drop button.
		 * Used to detect if the mouse is hovering over the drop button.
		 * 
		 * @return A `sf::FloatRect` representing the bounds of the drop button.
		 */
		sf::FloatRect dropHitbox()
		{
			return dropButton.getGlobalBounds();
		}
		
		/**
		 * Gets the result associated with the currently selected option.
		 * 
		 * @return The result string of the currently selected option.
		 */
		std::string getResult()
		{
			return results_list[selected_option];
		}

		std::string getOResult()
		{
			for (const auto& pair : results_list)
			{
				if (pair.second == selected_option)
				{
					return pair.first;
				}
			}
			return "";
		}

		std::string getRResult()
		{
			for (const auto& pair : results_list)
			{
				if (pair.second == selected_option)
				{
					return pair.second;
				}
			}
			return "";
		}
		
		/**
		 * Sets the selected option based on the given result.
		 * 
		 * @param input The result string to select.
		 * @return The option text corresponding to the selected result.
		 */
		std::string setFromResult(std::string input)
		{
			for (const auto& pair : results_list) {
				std::string key = pair.second;
				if (key == input)
				{
					changeSelection(pair.first);
					return pair.first;
				}
			}
			return "";
		}
		
		/**
		 * Gets the dropped state of the dropdown list.
		 * 
		 * @return True if the list is dropped, false otherwise.
		 */
		bool getState()
		{
			return dropped;
		}

		typedef void (*FunctionType)();

		void setFunction(FunctionType function)
		{
			cachedFunction = function;
		}

	private:

		/**
		 * Returns the text of the option under the mouse cursor.
		 * 
		 * @param mousePosition The current mouse position.
		 * @return The option text under the mouse cursor, or an empty string if none.
		 */
		std::string getSpriteUnderMouse(sf::Vector2f mousePosition)
		{
			for (const auto& pair : options_list)
			{
				sf::Sprite sprite = pair.second;
				if (sprite.getGlobalBounds().contains(mousePosition))
				{
					return pair.first;
				}
			}
			return "";
		}

		/**
		 * Generates a texture for the given text and stores it in the textures map.
		 * The texture is used to render the text on the dropdown list.
		 * 
		 * @param text The text to render.
		 * @param width The width of the texture.
		 * @param height The height of the texture.
		 * @param key The key for the texture in the textures map.
		 * @param texturesMap The map to store the generated texture.
		 */
		void genTexture(std::string text, int width, int height, std::string key, std::map<std::string, sf::Texture>& texturesMap)
		{
		
			sf::RenderTexture renderTexture;
			if (!renderTexture.create(width, height)) {
				std::cerr << "Error creating render texture" << std::endl;
				return;
			}

			sf::RectangleShape border(sf::Vector2f(width - 2, height - 2));
			border.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::inactive]);
			border.setOutlineThickness(1);
			border.setOutlineColor(ColorPalete::Palete[colorSet][ColorPalete::outline]);
			border.setPosition(1, 1);
			renderTexture.draw(border);

			sf::Text sfmlText;
			sfmlText.setFont(defaultFont);
			sfmlText.setString(text);
			sfmlText.setCharacterSize(24);

			float scaleX = (width - 20) / sfmlText.getLocalBounds().width;
			float scaleY = (height - 20) / sfmlText.getLocalBounds().height;
			float scale = std::min(scaleX, scaleY);
			sfmlText.setScale(scale, scale);

			sf::FloatRect textRect = sfmlText.getLocalBounds();
			sfmlText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			sfmlText.setPosition(width / 2.0f, height / 2.0f);

			sfmlText.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);
			sfmlText.setOutlineThickness(0);
			sfmlText.setOutlineColor(sf::Color::Transparent);
			sfmlText.setStyle(sf::Text::Regular);
			sfmlText.setScale(scale, scale);

			if (key == "Drop")
			{
				sfmlText.setScale(1.0f, 1.0f);
				sfmlText.setPosition(10, 17);
			}

			renderTexture.draw(sfmlText);

			renderTexture.display();

			sf::Texture texture = renderTexture.getTexture();
			texturesMap[key] = texture;
		}

		std::map <std::string, sf::Sprite> options_list;
		std::map <std::string, std::string> results_list;
		std::map <std::string, sf::Texture>texturesMap;
		std::vector <std::pair <std::string, std::string>> options_added;
		sf::Sprite dropButton;
		sf::Sprite selectedOpiton;
		sf::Sprite option;
		sf::Texture outputTexture;
		bool dropped = false;

		std::string selected_option;
		std::string defaultOption;
		std::string firstKey;

		bool mouse_state = false;
		bool mouse_release = false;

		bool blocked = false;

		sf::Font defaultFont;
		
		int sizeX_global;
		int sizeY_global;

		int posX_global;
		int posY_global;
		int lastY;

		int colorSet;

		FunctionType cachedFunction = nullptr;

		sf::Vector2u windowsize;
	};
}