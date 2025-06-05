namespace sfgComponents
{
    class ButtonClickEvent
	{
		public:

		typedef void (*FunctionType)();

		void init(sfgComponents::ButtonBody& btBody)
		{
			body = &btBody;
		}

		void setBlockState(bool block)
		{
			blocked = block;
		}

		void bindFunction(FunctionType function)
		{
			cachedFunction = function;
		}

		int update(sf::Vector2f& mouse_pos)
		{
			if (blocked == false)
			{
				if (body->getPointer().getGlobalBounds().contains(mouse_pos))
				{
					body->getPointer().setFillColor(ColorPalete::Palete[body->colorSet][ColorPalete::onmouse]);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mouse_state = true;
						mouse_release = true;

						body->getPointer().setFillColor(ColorPalete::Palete[body->colorSet][ColorPalete::active]);
						return sfgComponents::States::onMouse;
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
							return sfgComponents::States::isMouseClicked;
						}
					}
				}
				else
				{
					body->getPointer().setFillColor(ColorPalete::Palete[body->colorSet][ColorPalete::inactive]);
					mouse_state = false;
				}	
			}
			else
			{
				body->getPointer().setFillColor(ColorPalete::Palete[body->colorSet][ColorPalete::blocked]);
			}
			return sfgComponents::States::noMouse;
		}

		bool mouse_state = false;
		bool mouse_release = false;

		bool blocked = false;

		private:

		FunctionType cachedFunction = nullptr;

		ButtonBody* body;
	};
}