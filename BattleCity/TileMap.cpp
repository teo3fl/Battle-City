#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(uint16_t width, uint16_t height) :
	m_width(width), m_height(height), m_loaded(false)
{
	// the upper left corner coordinates of the map
	m_upperLeftCorner.x = 80;
	m_upperLeftCorner.y = 80;
	
	// the lower right corner coordinates of the map
	m_lowerRightCorner.x = m_upperLeftCorner.x + 832;
	m_lowerRightCorner.y = m_upperLeftCorner.y + 832;

	m_map.resize(m_height);
	for (int x = 0; x < m_height; x++)
		m_map[x].resize(m_width);

	m_aiMap = std::move(std::make_shared<AiMap>(AiMap (m_width, m_height)));

	m_shovelPowerUp = false;
	m_shovelTime = 0;
	m_shovelTimeMax = 20;
}

TileMap::~TileMap()
{
	Clear();
}

void TileMap::Clear()
{
	for (int x = 0; x < m_height; x++)
		for (int y = 0; y < m_width; y++)
			if (m_map[x][y])
				delete m_map[x][y];
}

void TileMap::LoadFromFile(const std::string& fileName)
{
	std::ifstream in (fileName);

	uint16_t borderX = m_upperLeftCorner.x;
	uint16_t borderY = m_upperLeftCorner.y;

	if (in.is_open())
	{
		uint8_t tileSize = 16;
		for (uint16_t y = 0; y < m_height; y++)
		{
			for (uint16_t x = 0; x < m_width; x++)

			{
				int tileType;
				in >> tileType;

				switch (tileType)
				{
				case 0: 
				{
					m_map[x][y] = nullptr;
					break;
				}

				case 1:
				{
					m_map[x][y] = new Brick(x * tileSize + borderX, y * tileSize + borderY, m_textures["BRICK"]);
					break;
				}
				case 2:
				{
					m_map[x][y] = new Steel(x * tileSize + borderX, y * tileSize + borderY, m_textures["STEEL"]);
					break;
				}
				case 3:
				{
					m_map[x][y] = new Water(x * tileSize + borderX, y * tileSize + borderY, m_textures["WATER"]);
					break;
				}
				case 4:
				{
					m_map[x][y] = new Ice(x * tileSize + borderX, y * tileSize + borderY, m_textures["ICE"]);
					break;
				}
				case 5:
				{
					m_map[x][y] = new Trees(x * tileSize + borderX, y * tileSize + borderY, m_textures["TREES"]);
					break;
				}
				case 6:
				{
					m_map[x][y] = new Base(x * tileSize + borderX, y * tileSize + borderY, m_textures["BASE"]);
					m_baseCoordinates.x = x;
					m_baseCoordinates.y = y;
					break;
				}
				default:
				{
					throw "ERROR::TILE_MAP::INVALID_TILE_TYPE";
					break;
				}
				}
			}
		}
	}
	else
	{
		throw "ERROR::TILE_MAP::COULD NOT LOAD FROM FILE::FILENAME: " + fileName;
	}

	in.close();

	m_loaded = true;
}

void TileMap::AddTexture(const std::string& textureName,const sf::Texture& texture)
{
	m_textures[textureName] = texture;
}

bool TileMap::GetBaseStatus()
{
	if (m_map[m_baseCoordinates.x][m_baseCoordinates.y])
		return true;
	return false;
}

bool TileMap::IsLoaded()
{
	return m_loaded;
}

void TileMap::ActivateShovelPowerUp()
{
	m_shovelPowerUp = true;
	FortifyBaseWalls();
}

void TileMap::FortifyBaseWalls()
{	
	std::array<sf::Vector2i, 8> coordinates =
	{ 
		sf::Vector2i(22,46),
		sf::Vector2i(24,46), 
		sf::Vector2i(26,46), 
		sf::Vector2i(28,46), 
		sf::Vector2i(22,48), 
		sf::Vector2i(22,50), 
		sf::Vector2i(28,48), 
		sf::Vector2i(28,50)
	};

	for (uint8_t i = 0; i < coordinates.size(); ++i)
	{
		int row = coordinates[i].x;
		int column = coordinates[i].y;

		// one Steel tile = 4 Brick tiles in 2x2 squares

		if (m_map[row][column] && m_map[row][column]->GetType() == "Brick") // upper left
		{
			delete m_map[row][column];
			m_map[row][column] = nullptr;
		}
		if (m_map[row][column + 1] && m_map[row][column+1]->GetType() == "Brick") // upper right
		{
			delete m_map[row][column+1];
			m_map[row][column+1] = nullptr;
		}

		if (m_map[row + 1][column] && m_map[row+1][column]->GetType() == "Brick") // lower left
		{
			delete m_map[row+1][column];
			m_map[row+1][column] = nullptr;
		}

		if (m_map[row + 1][column + 1] && m_map[row+1][column+1]->GetType() == "Brick") // lower right
		{
			delete m_map[row+1][column+1];
			m_map[row+1][column+1] = nullptr;
		}

		uint8_t tileSize = 16;
		uint16_t borderX = m_upperLeftCorner.x;
		uint16_t borderY = m_upperLeftCorner.y;

		m_map[row][column] = new Steel(row * tileSize + borderX, column * tileSize + borderY, m_textures["STEEL"]);
	}
}

void TileMap::RevertBaseWalls()
{
	std::array<sf::Vector2i, 8> coordinates =
	{
		sf::Vector2i(22,46),
		sf::Vector2i(24,46),
		sf::Vector2i(26,46),
		sf::Vector2i(28,46),
		sf::Vector2i(22,48),
		sf::Vector2i(22,50),
		sf::Vector2i(28,48),
		sf::Vector2i(28,50)
	};

	uint8_t tileSize = 16;
	uint16_t borderX = m_upperLeftCorner.x;
	uint16_t borderY = m_upperLeftCorner.y;

	for (uint8_t i = 0; i < coordinates.size(); ++i)
	{
		int row = coordinates[i].x;
		int column = coordinates[i].y;

		delete m_map[row][column];

		// one Steel tile = 4 Brick tiles in 2x2 squares

		// upper left
		m_map[row][column] = new Brick(row * tileSize + borderX, column * tileSize + borderY, m_textures["BRICK"]);


		// upper right
		m_map[row][column + 1] = new Brick(row * tileSize + borderX, (column + 1) * tileSize + borderY, m_textures["BRICK"]);

		// lower left
		m_map[row + 1][column] = new Brick((row + 1) * tileSize + borderX, column * tileSize + borderY, m_textures["BRICK"]);

		// lower right
		m_map[row + 1][column + 1] = new Brick((row + 1) * tileSize + borderX, (column + 1) * tileSize + borderY, m_textures["BRICK"]);
	}
}

void TileMap::UpdateTankBorderCollision(Tank* tank, const float& dt)
{
	if (tank->GetPosition().x < m_upperLeftCorner.x)
	{
		tank->SetPosition(m_upperLeftCorner.x, tank->GetPosition().y);
		tank->StopVelocityX();
	}
	else if (tank->GetPosition().x + tank->GetGlobalBounds().width > m_lowerRightCorner.x)
	{
		tank->SetPosition(m_lowerRightCorner.x - tank->GetGlobalBounds().width, tank->GetPosition().y);
		tank->StopVelocityX();
	}

	if (tank->GetPosition().y < m_upperLeftCorner.y)
	{
		tank->SetPosition(tank->GetPosition().x, m_upperLeftCorner.y);
		tank->StopVelocityY();
	}
	else if (tank->GetPosition().y + tank->GetGlobalBounds().height > m_lowerRightCorner.y)
	{
		tank->SetPosition(tank->GetPosition().x, m_lowerRightCorner.y - tank->GetGlobalBounds().height);
		tank->StopVelocityY();
	}
}

void TileMap::UpdateTankTileCollision(Tank* tank, const float& dt)
{
	for (uint16_t y = 0; y < m_width; ++y)
		for (uint16_t x = 0; x < m_height; ++x)
			if (m_map[x][y])
			{
				sf::FloatRect entityBounds = tank->GetGlobalBounds();
				sf::FloatRect nextPositionBounds = tank->GetNextPositionBounds(dt);
				sf::FloatRect wallBounds = m_map[x][y]->GetGlobalBounds();

				if (wallBounds.intersects(nextPositionBounds))
				{
					if (m_map[x][y]->GetTankCollision())
					{
						//Bottom collision
						if (entityBounds.top < wallBounds.top
							&& entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
							&& entityBounds.left < wallBounds.left + wallBounds.width
							&& entityBounds.left + entityBounds.width > wallBounds.left
							)
						{
							tank->StopVelocityY();
							tank->StopVelocityX();
							tank->Push(sf::Vector2f(0.f, -1.f), dt);
						}

						//Top collision
						else if (entityBounds.top > wallBounds.top
							&& entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
							&& entityBounds.left < wallBounds.left + wallBounds.width
							&& entityBounds.left + entityBounds.width > wallBounds.left
							)
						{
							tank->StopVelocityY();
							tank->StopVelocityX();
							tank->Push(sf::Vector2f(0.f, 1.f), dt);
						}

						//Right collision
						if (entityBounds.left < wallBounds.left
							&& entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
							&& entityBounds.top < wallBounds.top + wallBounds.height
							&& entityBounds.top + entityBounds.height > wallBounds.top
							)
						{
							tank->StopVelocityX();
							tank->StopVelocityY();
							tank->Push(sf::Vector2f(-1.f, 0.f), dt);
						}

						//Left collision
						else if (entityBounds.left > wallBounds.left
							&& entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
							&& entityBounds.top < wallBounds.top + wallBounds.height
							&& entityBounds.top + entityBounds.height > wallBounds.top
							)
						{
							tank->StopVelocityX();
							tank->StopVelocityY();
							tank->Push(sf::Vector2f(1.f, 0.f), dt);
						}
					}
					if (m_map[x][y]->GetType() == "Ice")
						tank->SetDeceleration(100.f);

					else
						tank->SetDeceleration(300.f);
				}
			}
}

void TileMap::UpdateTank(Tank* tank, const float& dt)
{
	UpdateTankBorderCollision(tank, dt);
	UpdateTankTileCollision(tank, dt);
}

void TileMap::UpdateShovelPowerUp(const float& dt)
{
	if (m_shovelPowerUp)
	{
		m_shovelTime += dt;
		if (m_shovelTime >= m_shovelTimeMax)
		{
			m_shovelPowerUp = false;
			m_shovelTime = 0;
			RevertBaseWalls();
		}
	}
}

bool TileMap::UpdateBulletBorderCollision(Tank* tank, Bullet* bullet, const float& dt)
{
	if (bullet->GetPosition().x < m_upperLeftCorner.x)
	{
		tank->DestroyBullet(bullet);
		return false;
	}

	if (bullet->GetPosition().x + bullet->GetGlobalBounds().width > m_lowerRightCorner.x)
	{
		tank->DestroyBullet(bullet);
		return false;
	}

	if (bullet->GetPosition().y < m_upperLeftCorner.y)
	{
		tank->DestroyBullet(bullet);
		return false;
	}

	if (bullet->GetPosition().y + bullet->GetGlobalBounds().height > m_lowerRightCorner.y)
	{
		tank->DestroyBullet(bullet);
		return false;
	}
	return true;
}

void TileMap::UpdateBulletTileCollision(Tank* tank, Bullet* bullet, const float& dt)
{
	for (uint16_t y = 0; y < m_width; ++y)
		for (uint16_t x = 0; x < m_height; ++x)
			if (m_map[x][y])
			{
				sf::FloatRect bulletBounds = bullet->GetGlobalBounds();
				sf::FloatRect nextPositionBounds = bullet->GetNextPositionBounds(dt);
				sf::FloatRect wallBounds = m_map[x][y]->GetGlobalBounds();

				uint8_t tileHealth = m_map[x][y]->GetHealth();
				uint8_t bulletHealth = bullet->GetHealth();

				if (m_map[x][y]->GetBulletCollision() && wallBounds.intersects(nextPositionBounds))
				{
					//Bottom collision
					if (bulletBounds.top < wallBounds.top
						&& bulletBounds.top + bulletBounds.height < wallBounds.top + wallBounds.height
						&& bulletBounds.left < wallBounds.left + wallBounds.width
						&& bulletBounds.left + bulletBounds.width > wallBounds.left
						)
					{
						switch (tileHealth - bulletHealth)
						{
						case 0:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							tank->DestroyBullet(bullet);
							break;
						}
						case 1:
						{
							tank->DestroyBullet(bullet);
							break;
						}
						case -1:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							bullet->DecreaseHealth(tileHealth);
							break;
						}
						}
						return;
					}

					//Top collision
					else if (bulletBounds.top > wallBounds.top
						&& bulletBounds.top + bulletBounds.height > wallBounds.top + wallBounds.height
						&& bulletBounds.left < wallBounds.left + wallBounds.width
						&& bulletBounds.left + bulletBounds.width > wallBounds.left
						)
					{
						switch (tileHealth - bulletHealth)
						{
						case 0:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							tank->DestroyBullet(bullet);
							break;
						}
						case 1:
						{
							tank->DestroyBullet(bullet);
							break;
						}
						case -1:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							bullet->DecreaseHealth(tileHealth);
							break;
						}
						}
						return;
					}

					//Right collision
					if (bulletBounds.left < wallBounds.left
						&& bulletBounds.left + bulletBounds.width < wallBounds.left + wallBounds.width
						&& bulletBounds.top < wallBounds.top + wallBounds.height
						&& bulletBounds.top + bulletBounds.height > wallBounds.top
						)
					{
						switch (tileHealth - bulletHealth)
						{
						case 0:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							tank->DestroyBullet(bullet);
							break;
						}
						case 1:
						{
							tank->DestroyBullet(bullet);
							break;
						}
						case -1:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							bullet->DecreaseHealth(tileHealth);
							break;
						}
						}
						return;
					}

					//Left collision
					else if (bulletBounds.left > wallBounds.left
						&& bulletBounds.left + bulletBounds.width > wallBounds.left + wallBounds.width
						&& bulletBounds.top < wallBounds.top + wallBounds.height
						&& bulletBounds.top + bulletBounds.height > wallBounds.top
						)
					{
						switch (tileHealth - bulletHealth)
						{
						case 0:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							tank->DestroyBullet(bullet);
							break;
						}
						case 1:
						{
							tank->DestroyBullet(bullet);
							break;
						}
						case -1:
						{
							delete m_map[x][y];
							m_map[x][y] = nullptr;
							m_aiMap->Clear(x, y);
							bullet->DecreaseHealth(tileHealth);
							break;
						}
						}
						return;
					}
				}
			}
}

void TileMap::UpdateBullet(Tank* tank, Bullet* bullet, const float& dt)
{
	if (UpdateBulletBorderCollision(tank, bullet, dt))
		UpdateBulletTileCollision(tank, bullet, dt);
}

void TileMap::RenderTilesAbove(sf::RenderTarget* target)
{
	for (uint16_t x = 0; x < m_height; ++x)
		for (uint16_t y = 0; y < m_width; ++y)
			if(m_map[x][y]!=NULL && m_map[x][y]->GetType() == "Trees")
				m_map[x][y]->Render(target);
}

void TileMap::RenderTilesBelow(sf::RenderTarget* target)
{
	for (uint16_t x = 0; x < m_height; ++x)
		for (uint16_t y = 0; y < m_width; ++y)
			if (m_map[x][y] != NULL && m_map[x][y]->GetType() != "Trees")
				m_map[x][y]->Render(target);
}