#include "Board.h"
#include "Moves.h"

Board::Board()
{
	m_firstPlay = true;
}


void Board::buildGameMap()
{
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLS; j++)
		{
			const bool isEdge = (i == 1) || (i == NUM_OF_ROWS) || (j == 1) || (j == NUM_OF_COLS);

			Circle c({ i,j }, isEdge);
			m_gameMap.insert({ i,j }, c);
		}
	}

	const auto mapSize = m_mapBorder.getSize();
	
	for (auto& cell : m_gameMap)
	{
		const Coordinate cor = cell.data().getCoordinate();

		int x = (static_cast<float>(mapSize.x) * 0.06f) + (cor.m_col * (cell.data().getRadius() * 2.1));

		const int y = (static_cast<float>(mapSize.y) * 0.06f) + (cor.m_row * (cell.data().getRadius() * 2));

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
	const auto mapSize = m_mapBorder.getSize();

	const Coordinate cordi = m_gameCat.getCoordinate();

	int x = (static_cast<float>(mapSize.x) * 0.06f) + (cordi.m_col * (m_gameCat.getRadius() * 2.1));

	const int y = (static_cast<float>(mapSize.y) * 0.06f) + (cordi.m_row * (m_gameCat.getRadius() * 2));

	if (cordi.m_row % 2 != 0)
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
	m_mapBorder.setOutlineColor(sf::Color(204, 207, 176));
	m_mapBorder.setFillColor(sf::Color(204, 207, 176));
	m_mapBorder.setPosition(boardOrigin);
}

bool Board::handelMouseClick(sf::Vector2i pressedPoint)
{
	const int x = pressedPoint.x;
	const int y = pressedPoint.y;

	if (m_mapBorder.getGlobalBounds().contains(x,y));
	{
		for (auto& node : m_gameMap)
		{
			if (node.data().mouseClicked(pressedPoint))
			{
				Moves move;

				move.catCor = m_gameCat.getCoordinate();
				move.pressedCircleCor = node.data().getCoordinate();

				m_gameMoveHistory.push(move);

				moveCat();

				return true;
			}
		}
	}

	return false;
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
	while (!(m_gameMoveHistory.empty()))
	{
		undoMove();
	}

	m_firstPlay = true;
}

void Board::undoMove()
{

	m_gameMap[{m_gameMoveHistory.top().pressedCircleCor.m_row, m_gameMoveHistory.top().pressedCircleCor.m_col}].data().activateCircle();
	
	m_gameCat.setCoordinants(m_gameMoveHistory.top().catCor.m_col, m_gameMoveHistory.top().catCor.m_row);
	setCatPosition();

	m_gameMoveHistory.pop();
}

void Board::moveCat()
{
	for (auto& node : m_gameMap) 
	{
		if ((m_gameCat.getCoordinate().m_col == node.data().getCoordinate().m_col) &&
				(m_gameCat.getCoordinate().m_row == node.data().getCoordinate().m_row))
		{
			m_gameCat.setCoordinants(m_gameCat.getCoordinate().m_col + 1, m_gameCat.getCoordinate().m_row);
			break;
		}
	}
	setCatPosition();
}
