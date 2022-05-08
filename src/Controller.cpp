#include "Controller.h"


Controller::Controller():
	m_window(sf::VideoMode(950, 900), "Circle The Cat"),
	m_bgColor(sf::Color::White)

{}

void Controller::run()
{
	m_board.buildGame(m_window);

	buildResetButton();

	buildUndoButton();

	m_window.setFramerateLimit(120);

	while (m_window.isOpen())
	{
		m_window.clear(m_bgColor);
		
		m_board.drawGameMap(m_window);

		m_window.draw(m_resetButton);

		m_window.draw(m_undoButton);

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
					sf::Vector2f clickPoint(event.mouseButton.x, event.mouseButton.y);

					sf::Vector2i pressedPoint = m_window.mapCoordsToPixel(clickPoint);

					m_board.handelMouseClick(pressedPoint);
				}
				//else if (m_resetButton.getGlobalBounds().contains(x, y))
				//{

				//}
				//else if (m_undoButton.getGlobalBounds().contains(x, y))
				//{

				//}
				break;
			}
		}
	}
}

void Controller::buildResetButton()
{
	const auto windowSize = m_window.getSize();

	const sf::Vector2f buttonSize(static_cast<float>(windowSize.x) * 0.15f, static_cast<float>(windowSize.y) * 0.05f);

	const sf::Vector2f buttonOrigin(static_cast<float>(windowSize.x) * 0.03f, static_cast<float>(windowSize.y) * 0.94f);

	m_resetButton.setSize(buttonSize);
	m_resetButton.setOutlineThickness(8);
	m_resetButton.setOutlineColor(sf::Color::Cyan);
	m_resetButton.setFillColor(sf::Color::White);
	m_resetButton.setPosition(buttonOrigin);
}

void Controller::buildUndoButton()
{
	const auto windowSize = m_window.getSize();

	const sf::Vector2f buttonSize(static_cast<float>(windowSize.x) * 0.15f, static_cast<float>(windowSize.y) * 0.05f);

	const sf::Vector2f buttonOrigin(static_cast<float>(windowSize.x) * 0.82f, static_cast<float>(windowSize.y) * 0.94f);

	m_undoButton.setSize(buttonSize);
	m_undoButton.setOutlineThickness(8);
	m_undoButton.setOutlineColor(sf::Color::Cyan);
	m_undoButton.setFillColor(sf::Color::White);
	m_undoButton.setPosition(buttonOrigin);
}