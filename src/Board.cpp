#include "Board.h"

#include "CatAlgorithm.h"
#include "Moves.h"
#include "GraphAlgorithm.h"

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
			const bool isEdge = (i == 0) || (i == NUM_OF_ROWS-1) || (j == 0) || (j == NUM_OF_COLS-1);

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

	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_COLS; j++)
		{
			const auto current = std::make_pair<int, int>(std::move(i), std::move(j));

			std::list<std::pair<int, int>> neighbors = { {i, j - 1},{i, j + 1},{i - 1, j},{i + 1,j} };

			if (i % 2 == 0)
			{
				neighbors.emplace_back(std::make_pair<int, int>( i - 1, j - 1 ));
				neighbors.emplace_back(std::make_pair<int, int>( i + 1, j - 1 ));
			}
			else
			{
				neighbors.emplace_back(std::make_pair<int, int>( i - 1, j + 1 ));
				neighbors.emplace_back(std::make_pair<int, int>( i + 1, j + 1 ));
			}

			for (std::list<std::pair<int, int>>::value_type neighbor : neighbors)
			{
				m_gameMap.addEdge(current, neighbor);
			}
		}
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

	if (m_mapBorder.getGlobalBounds().contains(x, y));
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
	if (m_gameMoveHistory.empty())
		return;

	m_gameMap[{m_gameMoveHistory.top().pressedCircleCor.m_row, m_gameMoveHistory.top().pressedCircleCor.m_col}].data().activateCircle();

	m_gameCat.setCoordinants(m_gameMoveHistory.top().catCor.m_col, m_gameMoveHistory.top().catCor.m_row);
	setCatPosition();

	m_gameMoveHistory.pop();
}

void Board::moveCat()
{
	const auto catCor = m_gameCat.getCoordinate();
	Node<Circle>* catNode = &m_gameMap[{catCor.m_row, catCor.m_col}];

	m_gameCat.move(m_gameMap.begin(), m_gameMap.end(), catNode);	
	
	setCatPosition();
}

bool Board::IsCatBlocked() const
{
	const auto catCor = m_gameCat.getCoordinate();

	for (const auto& node : m_gameMap[{catCor.m_col, catCor.m_row}])
		if (!node.data().isBlocked())
			return false;

	return true;
}

bool Board::IsCatInEdge() const
{
	const auto catCor = m_gameCat.getCoordinate();
	return m_gameMap[{catCor.m_col, catCor.m_row}].data().isEdge();
}
