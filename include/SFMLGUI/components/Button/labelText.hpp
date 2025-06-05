namespace sfgComponents
{
    class ButtonLabelText
	{
		public:

		void init(sfgComponents::ButtonBody& btBody)
		{
			body = &btBody;
		}

        void setFont(sf::Font& font)
        {
            text.setFont(font);
        }

        void setAttributes(int fontSize, const std::string& inputText)
		{
			text.setCharacterSize(fontSize);
            text.setString(inputText);
            allignText();
		}

		sf::Text &getPointer()
		{
			return text;
		}

		void render(sf::RenderWindow& window)
		{
			window.draw(text);
		}

        void setColor(int color)
        {
            text.setFillColor(ColorPalete::Palete[color][ColorPalete::font]);
        }

		void allignText()
        {
            float scaleX = (body->width - 20) / text.getLocalBounds().width;
			float scaleY = (body->height - 20) / text.getLocalBounds().height;
			float scale = std::min(scaleX, scaleY);
			text.setScale(scale, scale);

			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

			float posX = body->getPointer().getPosition().x + body->width / 2.0f;
			float posY = body->getPointer().getPosition().y + body->height / 2.0f;
			text.setPosition(posX, posY);
        }

		private:

		ButtonBody* body;

        sf::Text text;
	};
}