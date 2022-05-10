#include "Controller.h"

Controller::Controller() :
	m_window(sf::VideoMode(950, 900), "Circle The Cat"),
	m_bgColor(sf::Color(204, 207, 176)),
	m_resetButton("Reset"),
	m_undoButton("Undo"),
	m_moveNominator("MoveNominator")
{
	m_messageFont.loadFromFile("Daughter of Fortune.ttf");
}

void Controller::run()
{
	buildAllElements();

	LoadNextLevel();

	sf::Music music;

	music.openFromFile("AnyConv.com__Fluffing-a-Duck.wav");
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

					if (m_showMessage)
					{
						if (isCatWin() && m_undoButton.handleMouseClick(pressedPoint))
							undoMove();
						else if (isCatLose())
						{
							if (m_levelManager.getCurrentLevel() < m_levelManager.getNumOfLevels())
								LoadNextLevel();
							else
								exit(EXIT_SUCCESS);
						}
						else
							resetGame();

						m_showMessage = false;
					}
					else if (!m_showMessage && m_board.handelMouseClick(pressedPoint))
					{
						if (isCatWin())
							showLoseMessage();

						if (isCatLose())
							showWinMessage();

						break;
					}
					else if (m_resetButton.handleMouseClick(pressedPoint))
					{
						m_showMessage = false;
						resetGame();
					}
					else if (m_undoButton.handleMouseClick(pressedPoint))
					{
						m_showMessage = false;
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
	auto level = m_levelManager.LoadLevel(m_levelManager.getCurrentLevel());
	m_board.loadLevel(level);
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

	m_message.setFont(m_messageFont);
	m_message.setCharacterSize(72);
	m_message.setPosition({ static_cast<float>(m_window.getSize().x) / 4, static_cast<float>(m_window.getSize().y) / 4 });
	m_message.setFillColor(sf::Color(167, 232, 184));
	m_message.setOutlineThickness(3);
}

void Controller::drawAllElements()
{
	m_board.drawGameMap(m_window);

	m_resetButton.draw(m_window, 0);

	m_undoButton.draw(m_window, 0);

	m_moveNominator.draw(m_window, m_board.getMoveNumber());

	if (m_showMessage)
		m_window.draw(m_message);
}

void Controller::showWinMessage()
{
	m_showMessage = true;
	m_message.setString("You Win!\nClick for the next level");
}

void Controller::showLoseMessage()
{
	m_showMessage = true;
	m_message.setString("You Lose!\nyou can undo last move\nor click anywhere to reset");
}

void Controller::LoadNextLevel()
{
	auto level = m_levelManager.LoadNextLevel();
	m_board.loadLevel(level);
}
