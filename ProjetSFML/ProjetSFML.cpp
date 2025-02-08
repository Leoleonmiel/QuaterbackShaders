
#include "common.h"
#include <vector>
#define S_WIDTH 1920
#define S_HEIGHT 1080

std::vector<sf::VertexArray> cells;
float tileWidth = 40;
float tileHeight = 40 / 2;

sf::Vector2f Screen2World(sf::Vector2f _screenPos)
{
	sf::Vector2f screenPos;
	screenPos.x = (_screenPos.x / static_cast<float>(tileWidth) / 1.75f) + (_screenPos.y / static_cast<float>(tileHeight));
	screenPos.y = (_screenPos.y / static_cast<float>(tileHeight) / 1.75f) - (_screenPos.x / static_cast<float>(tileWidth));

	return screenPos;
}

sf::Vector2f World2Screen(float _x, float _y, float _z)
{
	sf::Vector2f screenPos{ 0.f, 0.f };

	screenPos.x = (_x * (tileWidth)-_y * (tileWidth));
	screenPos.y = static_cast<float>(_x * (tileWidth / 2.f) + _y * (tileWidth / 2.f) - _z * tileWidth * 0.577f);

	return screenPos;
}
void tile(sf::Vector2f _p, int& index, int i, int j)
{
	 // Access vertices using the calculated index
	cells[index][0].position = sf::Vector2f(_p.x, _p.y - tileHeight);
	cells[index][1].position = sf::Vector2f(_p.x + tileWidth, _p.y);
	cells[index][2].position = sf::Vector2f(_p.x, _p.y + tileHeight);
	cells[index][3].position = sf::Vector2f(_p.x - tileWidth, _p.y);


	std::vector<sf::Color> colors;
	for (int k = 0; k < 4; ++k)
	{
		colors.push_back(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}

	// Set a new random color for the vertices
   //sf::Color randomColor(rand() % 255, rand() % 255, rand() % 255);

   //for (int k = 0; k < 4; ++k)
   //{
   //	cell[index + k].color = randomColor;
   //}


   // Set colors for the vertices based on the cell position
   //sf::Color color;
   //if ((i + j) % 2 == 0) {
   //	// Even-indexed cells have one color
   //	color = sf::Color::White; // Set your desired color here
   //}
   //else {
   //	// Odd-indexed cells have another color
   //	color = sf::Color(rand() % 255, rand() % 255, rand() % 255); // Set your desired color here
   //}

   //for (int k = 0; k < 4; ++k)
   //{
   //	cell[index + k].color = color;
   //}
}

void InitGrid(int rows, int cols, const sf::View& view, sf::RenderWindow& _window)
{
	float startX = 3;
	float startY = 0;
	cells.resize(rows * cols, sf::VertexArray(sf::Quads, 4)); // Each cell has 4 vertices

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			float worldX = 20 + i;
			float worldY = 10 - j;
			float worldZ = 0.0f; 

			sf::Vector2f screenPos = World2Screen(worldX, worldY, worldZ);

			int index = (i * cols + j);
			tile(screenPos, index, i, j);
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
	sf::View camera;
	float zoomLevel = -2.f; 
	camera.zoom(zoomLevel);

	sf::Vector2f cameraPosition(0.f, 0.f);
	camera.setCenter(cameraPosition);

	int rows = 7;
	int cols = 20;

	InitGrid(rows, cols, window.getView(), window);
	std::cout << "SIZE:" << cells.size() << std::endl;

	float zoomSpeed = 0.1f; 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int i = 0; i < cells.size(); ++i)
		{
			for (int k = 0; k < 4; ++k)
			{
				sf::Color& currentColor = cells[i][k].color;

				// Update red component
				if (currentColor.r == 255)
				{
					currentColor.r -= 1;
				}
				else if (currentColor.r == 0)
				{
					currentColor.r += 1;
				}
				else
				{
					currentColor.r += (rand() % 2 == 0) ? 1 : -1;
				}

				// Update green component
				if (currentColor.g == 255)
				{
					currentColor.g -= 2;
				}
				else if (currentColor.g == 0)
				{
					currentColor.g += 2;
				}
				else
				{
					currentColor.g += (rand() % 2 == 0) ? 2 : -2;
				}

				// Update blue component
				if (currentColor.b == 255)
				{
					currentColor.b -= 3;
				}
				else if (currentColor.b == 0)
				{
					currentColor.b += 3;
				}
				else
				{
					currentColor.b += (rand() % 2 == 0) ? 3 : -3;
				}
			}
		}
		window.clear();

		for (const auto& cell : cells)
		{
			window.draw(cell);
		}

		window.display();
	}

	return 0;
}

