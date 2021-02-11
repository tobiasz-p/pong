#include <SFML/Graphics.hpp>

void test(){
	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 600, 32), "Kurs SFML - http://cpp0x.pl");
	while (oknoAplikacji.isOpen())
	{
		sf::Event zdarzenie;
		while (oknoAplikacji.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
				oknoAplikacji.close();

		}
		oknoAplikacji.clear(sf::Color(255, 0, 0));
		oknoAplikacji.display();
	}
}

