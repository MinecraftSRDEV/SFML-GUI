namespace sfgComponents
{
    class ButtonBody
	{
		public:

		void init()
		{
			body.setOutlineThickness(1);
		}

		void setAttributes(const sf::Vector2f& position, const sf::Vector2f& size)
		{
			body.setSize(size);
			body.setPosition(position);

            width = size.x;
            height = size.y;
		}

		void setColor(int color)
		{
			colorSet = color;
			body.setOutlineColor(ColorPalete::Palete[color][ColorPalete::outline]);
			body.setFillColor(ColorPalete::Palete[color][ColorPalete::inactive]);
		}

        void setPosition(sf::Vector2f& position)
        {
            body.setPosition(position);
        }

		sf::RectangleShape &getPointer()
		{
			return body;
		}

		void render(sf::RenderWindow& window)
		{
			window.draw(body);
		}

		int colorSet;
        int width;
        int height;

		private:

		sf::RectangleShape body;
	};	
}