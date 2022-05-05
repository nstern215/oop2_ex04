#include "Controller.h"


Controller::Controller():
	m_window(sf::VideoMode(1000, 800), "Circle The Cat"),
	m_bgColor(0, 0, 100, 0)

{}

void Controller::run()
{
	m_manager.buildGameMap();

	m_window.setFramerateLimit(120);

	while (m_window.isOpen())
	{
		m_window.clear(m_bgColor);

		m_manager.drawGameMap(m_window);

		m_window.display();

		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type) {

			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					break;
				}
			}
		}
	}
}

void Controller::handelClick()
{
//	if (m_shape.getGlobalBounds().contains(
//		m_window.mapPixelToCoords({ event.x, event.y })))
//	{
//		
//	}
}
