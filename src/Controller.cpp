#include "Controller.h"

Controller::Controller():
	m_window(sf::VideoMode(950, 900), "Circle The Cat"),
	m_bgColor(sf::Color(204, 207, 176)),
	m_resetButton("Reset"),
	m_undoButton("Undo"),
	m_moveNominator("MoveNominator")
{}

void Controller::run()
{
	buildAllElements();

	sf::Music music;

	music.openFromFile("C:/Users/nomedi1408/Source/Repos/oop2_ex04/resources/AnyConv.com__Fluffing-a-Duck.wav");
	music.setLoop(true);
	music.setVolume(35);

	music.play();

	m_window.setFramerateLimit(120);

	while (m_window.isOpen())
	{
		m_window.clear(m_bgColor);

		drawAllElements();

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
						if (isCatWin())
							resetGame();

						if (isCatLose())
							resetGame();
						
						break;
					}
					if (m_resetButton.handleMouseClick(pressedPoint))
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

bool Controller::isCatWin() const
{
	return m_board.IsCatInEdge();
}

bool Controller::isCatLose() const
{
	return m_board.IsCatBlocked();
}


void Controller::buildAllElements()
{
	m_board.buildGame(m_window);

	m_resetButton.buildButton(m_window);

	m_undoButton.buildButton(m_window);

	m_moveNominator.buildButton(m_window);
}

void Controller::drawAllElements()
{
	m_board.drawGameMap(m_window);

	m_resetButton.draw(m_window, 0);

	m_undoButton.draw(m_window, 0);

	m_moveNominator.draw(m_window, m_board.getMoveNumber());
}
