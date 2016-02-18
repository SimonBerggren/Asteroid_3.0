#include "SFML\Graphics.hpp"
#include "GameSession.h"
#include "Window.h"

sf::RenderWindow* window;
GameSession* game;

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);
	game = new GameSession();

	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);	// updates per second

		// game loop
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			}
		}

		// update every 1/60 seconds
		while (deltaTime > ups)
		{
			deltaTime -= ups;

			game->Update(deltaTime.asSeconds());
		}

		window->clear();

		// draw
		game->Draw();

		window->display();

		deltaTime += clock.restart();
	}

	// clean up
	delete game;
	delete window;
	return EXIT_SUCCESS;
}