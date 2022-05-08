#include "Controller.h"


Controller::Controller():
	m_window(sf::VideoMode(950, 900), "Circle The Cat"),
	m_bgColor(sf::Color::White)

{}

void Controller::run()
{
	m_board.buildGame(m_window);

	m_window.setFramerateLimit(120);

	while (m_window.isOpen())
	{
		m_window.clear(m_bgColor);
		
		m_board.drawGameMap(m_window);

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
					sf::Vector2i pressedPoint = m_window.mapCoordsToPixel({ event.mouseButton.x, event.mouseButton.y });

					m_board.handelMouseClick(pressedPoint);
				}
				break;
			}
		}
	}
}