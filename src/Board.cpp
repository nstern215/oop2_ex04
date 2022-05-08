#include "Board.h"

Board::Board()
{
	auto font = sf::Font();
	font.loadFromFile(FONT_PATH);
	sf::Text undoButton(std::to_string(0), font);
	undoButton.setFillColor(sf::Color::Black);

	m_firstPlay = true;
}


void Board::buildGameMap()
{
	int a = 0;

	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLS; j++)
		{
			bool isEdge = (i == 1) || (i == NUM_OF_ROWS) || (j == 1) || (j == NUM_OF_COLS);

			Circle c({ i,j }, isEdge);
			m_gameMap.insert({ i,j }, c);
		}
	}

	for (auto& cell : m_gameMap)
	{
		const auto mapSize = m_mapBorder.getSize();

		Coordinate cor = cell.data().getCoordinate();

		int x = (static_cast<float>(mapSize.x) * 0.06f) + (cell.data().getCoordinate().m_col * (cell.data().getRadius() * 2.1));

		int y = (static_cast<float>(mapSize.y) * 0.06f) + (cell.data().getCoordinate().m_row * (cell.data().getRadius() * 2));

		if (cor.m_row % 2 != 0)
			x += cell.data().getRadius();

		cell.data().setPosition(x, y);
	}
}

void Board::drawGameMap(sf::RenderWindow& window)
{
	window.draw(m_mapBorder);

	for (auto& cell : m_gameMap)
	{
		cell.data().draw(window);
	}

	m_gameCat.draw(window);
}

void Board::setCatPosition()
{
	Coordinate cor = m_gameMap[{6, 6}].data().getCoordinate();

	int x = cor.m_col * (m_gameCat.getRadius() * 2);
	int y = cor.m_row * (m_gameCat.getRadius() * 2);

	if (cor.m_row % 2 != 0)
		x += m_gameCat.getRadius();

	m_gameCat.setPosition(x, y);
}

void Board::buildGame(sf::RenderWindow& window)
{
	buildMapBoarder(window);
	buildGameMap();
	setCatPosition();
}

void Board::buildMapBoarder(sf::RenderWindow& window)
{
	const auto windowSize = window.getSize();

	const sf::Vector2f boardSize(static_cast<float>(windowSize.x) * 0.9f, static_cast<float>(windowSize.y) * 0.87f);

	const sf::Vector2f boardOrigin(static_cast<float>(windowSize.x) * 0.05f, static_cast<float>(windowSize.y) * 0.05f);

	m_mapBorder.setSize(boardSize - sf::Vector2f(3.f, 3.f));
	m_mapBorder.setOutlineThickness(8);
	m_mapBorder.setOutlineColor(sf::Color::Cyan);
	m_mapBorder.setFillColor(sf::Color::White);
	m_mapBorder.setPosition(boardOrigin);
}

void Board::handelMouseClick(sf::Vector2i pressedPoint)
{
	int x = pressedPoint.x;
	int y = pressedPoint.y;

	if (m_mapBorder.getGlobalBounds().contains(x,y));
	{
		for (auto& node : m_gameMap)
		{
			if (node.data().mouseClicked(pressedPoint))
			{
				break;
			}
		}
	}
}

bool Board::firstPlay()
{
	if (m_firstPlay)
	{
		m_firstPlay = false;
		return true;
	}

	return m_firstPlay;
}

void Board::newGame()
{
	m_firstPlay = true;

	while (!(m_gameMoveHistory.empty()))
	{
		m_gameMoveHistory.pop();
	}
}