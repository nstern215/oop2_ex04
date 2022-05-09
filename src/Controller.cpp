#include "Controller.h"


Controller::Controller():
	m_window(sf::VideoMode(950, 900), "Circle The Cat"),
	m_bgColor(sf::Color(204, 207, 176)),
	m_resetButton("Reset"),
	m_undoButton("Undo")
{}

void Controller::run()
{
	m_board.buildGame(m_window);

	m_resetButton.buildButton(m_window);

	m_undoButton.buildButton(m_window);

	m_window.setFramerateLimit(120);

	while (m_window.isOpen())
	{
		m_window.clear(m_bgColor);

		m_board.drawGameMap(m_window);

		m_resetButton.draw(m_window);

		m_undoButton.draw(m_window);

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

					if (m_board.handelMouseClick(pressedPoint))
					{
						break;
					}
					else if (m_resetButton.handleMouseClick(pressedPoint))
					{
						resetGame();
					}
					else if (m_undoButton.handleMouseClick(pressedPoint))
					{
						undoMove();
					}
					break;
				}
			}
		}
	}
}

void Controller::resetGame()
{
	m_board.newGame();
}

void Controller::undoMove()
{
	m_board.undoMove();
}
