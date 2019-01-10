#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "Space Station Rescue" },
	m_exitGame{ false }, // When true game will exit
	player{sf::Vector2f(400,400)}
{
	view = sf::View(m_window.getView().getCenter(), m_window.getView().getSize());
	miniMap = sf::View(m_window.getView().getCenter(), m_window.getView().getSize());
	miniMap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	miniMap.zoom(2.0f);
	m_window.setView(view);


	if (!texture.loadFromFile("space.png"))
	{

	}
	background.setTexture(texture);
	background.setPosition(0, 0);
}


Game::~Game()
{

}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 960 fps
	while (m_window.isOpen())
	{
		processEvents(); // As many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // At least 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // As many as possible
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	else if (m_window.hasFocus()) // Ensure window is in focus before any action is taken
	{
		// Update...

		player.update(t_deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.increaseRotation();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.decreaseRotation();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.DecreaseSpeed();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.IncreaseSpeed();
		}
	}
	view.setCenter(player.getPosition());
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	// Draw...
	m_window.setView(view);
	//m_window.draw(background);
	player.draw(m_window);

	m_window.setView(miniMap);
	//m_window.draw(background);
	player.draw(m_window);


	m_window.display();
}
