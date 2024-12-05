namespace sfg
{
    class Textfield {
        public:

        Textfield ()
        {
            blockQueue = true;
        }

        void create(int x, int y, int size_x, int size_y, sf::Font& fontset, int color = ColorPalete::Bright)
        {
            font = fontset;

            background.setPosition(x,y);
            background.setSize(sf::Vector2f(size_x, size_y));

            x_global = x;
            y_global = y;

            setTheme(color);
        }

        void handleEvent(sf::Event& event)
        {
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta > 0)
                {
                    int mp = event.mouseWheel.delta;
                    while (mp > 0)
                    {
                        scorllUp();
                        mp--;
                    }
                }
                else
                {
                    int mp = event.mouseWheel.delta;
                    while (mp < 0)
                    {
                        scrollDown();
                        mp++;
                    }
                }
            }
        }

        void setTheme(int color)
        {
            colorSet = color;

            background.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::halftransparrent]);
        }

        void render(sf::RenderWindow& targetWindow)
        {
            targetWindow.draw(background);

            for (auto& it : textContent)
            {
                if (it.getPosition().y > y_global)
                {
                    if (it.getPosition().y < y_global + (background.getGlobalBounds().height - 20))
                    {
                        targetWindow.draw(it);
                    }
                }
            }
        }

        void applyTextColor(int color)
        {
            for (auto& it : textContent)
            {
                if (it.getFillColor() == sf::Color::Black or it.getFillColor() == sf::Color::White)
                {
                    it.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);    
                }
            }
        }

        void addText(const std::string& str)
        {
            if (blockQueue == false)
            {
                if (textqueue.size() > 0)
                {
                    printQueue();
                }

                buildText(ColorPalete::Palete[colorSet][ColorPalete::font], str);
            }
            else
            {
                addToQueue(str);
            }
        }

        void addColoredText(const std::string& str)
        {
            std::string target = "\e";
            size_t found = str.find(target);

            try
            {
                size_t start = str.find('[', found);
                if (start != std::string::npos)
                {
                    start++;
                    size_t end = str.find('m', start);
                    if (end != std::string::npos)
                    {
                        std::string ANSIcolor = str.substr(start, end - start);
                        std::string text = str.substr(end) + "\n";

                        sf::Text textAdd;

                        textAdd.setCharacterSize(16);
                        textAdd.setFont(font);
                        textAdd.setFillColor(ColorPalete::Palete[colorSet][ColorPalete::font]);
                        auto last = std::prev(textContent.end());
                        textAdd.setPosition(last->getPosition().x, last->getPosition().y + 16);
                        textAdd.setString(text);
                        textContent.emplace_back(textAdd);
                    }
                }
            }
            catch (std::out_of_range e)
            {
            }
        }

        void addToQueue(const std::string& msg)
        {
            if (blockQueue == true)
            {
                textqueue.emplace_back(msg);
            }
        }

        void printQueue()
        {
            if (blockQueue == true)
            {
                for (auto it : textqueue)
                {
                    addText(it);
                }
                textqueue.clear();    
            }
        }

        void unlockQueue()
        {
            blockQueue = false;
        }

        void lockQueue()
        {
            blockQueue = true;
        }

        void clearText()
        {
            textContent.clear();
        }

        void toDown()
        {
            for (auto last = std::prev(textContent.end()); last->getPosition().y > (y_global + background.getGlobalBounds().height - 20);)
            {
                scrollDown();
            }
        }

        void toUp()
        {
            for (auto first = textContent.begin(); first->getPosition().y < y_global + 10;)
            {
                scorllUp();
            }
        }

        private:

        void scrollDown()
        {
            auto last = std::prev(textContent.end());
            // auto prelast = std::prev(textContent.end() - 1);
            if (last->getPosition().y > (y_global + background.getGlobalBounds().height - 20))
            {
                for (auto& it : textContent)
                {
                    it.setPosition(it.getPosition().x, it.getPosition().y - 16);
                }
            }
        }

        void scorllUp()
        {
            auto first = textContent.begin();
            if (first->getPosition().y < y_global + 10)
            {
                for (auto& it : textContent)
                {
                    it.setPosition(it.getPosition().x, it.getPosition().y + 16);
                }
            }
        }

        void buildText(sf::Color color, std::string msg)
        {
            sf::Text textAdd;

            textAdd.setCharacterSize(16);
            textAdd.setFont(font);
            textAdd.setFillColor(color);
            if (textContent.size() > 0)
            {
                auto last = std::prev(textContent.end());
                textAdd.setPosition(last->getPosition().x, last->getPosition().y + 16);
            }
            else
            {
                textAdd.setPosition(x_global + 10, y_global + 10);
            }

            // for (auto& it : wrapText(msg))
            // {
            //     textAdd.setString(it);    
            // }
            textAdd.setString(msg);
            
            textContent.emplace_back(textAdd);

            for (auto last = std::prev(textContent.end()); last->getPosition().y > (y_global + background.getGlobalBounds().height - 20);)
            {
                scrollDown();
            }
        }

        std::vector <std::string> wrapText(const std::string& msg)
        {
            std::vector <std::string> output;
            
            sf::Text sample;
            auto first = textContent.begin();
            
            sample.setFont(font);
            sample.setCharacterSize(16);
            sample.setPosition(x_global + 10, y_global + 10);
            sample.setString(msg);

            std::string textline = msg;
            std::string outputtext;
            size_t pos = textline.length();
            size_t last_pos = 0;
            while (pos > 0)
            {
                sample.setString(textline);
                if (sample.getLocalBounds().width < background.getGlobalBounds().width - 20)
                {
                    output.emplace_back(msg);
                    break;
                }
                while (sample.getLocalBounds().width > background.getGlobalBounds().width - 20)
                {
                    sample.setString(textline);
                    if (pos > 0)
                    {
                        pos--;
                        outputtext = textline.substr(last_pos, pos);
                        textline = outputtext;
                        std::cout << "output: " << textline << std::endl;
                    }
                    else
                    {
                        break;
                    }
                }
                last_pos = pos;
                output.emplace_back(outputtext);
                pos = textline.length();
            }

            return output;
        }

        int colorSet;

        int x_global;
        int y_global;

        bool blockQueue = false;

        sf::Font font;
        sf::RectangleShape background;
        sf::Text text;

        std::vector <std::string> textqueue;
        
        std::vector <sf::Text> textContent;
    };
}