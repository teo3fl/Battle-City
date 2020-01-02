#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(uint16_t width, uint16_t height) :
	m_width(width), m_height(height)
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

	uint16_t border = m_upperLeftCorner.x;

	if (in.is_open())
	{
		uint8_t tileSize = 32;
		for (uint16_t y = 0; y < m_height; y++)
		{
			for (uint16_t x = 0; x < m_width; x++)

			{
				int tileType;
				in >> tileType;

				switch (tileType)
				{
				case 0: break;

				case 1:
				{
					m_map[x][y] = new Brick(x * tileSize + border, y * tileSize + border, m_textures["BRICK"]);
					break;
				}
				case 2:
				{
					m_map[x][y] = new Steel(x * tileSize + border, y * tileSize + border, m_textures["STEEL"]);
					break;
				}
				case 3:
				{
					m_map[x][y] = new Water(x * tileSize + border, y * tileSize + border, m_textures["WATER"]);
					break;
				}
				case 4:
				{
					m_map[x][y] = new Ice(x * tileSize + border, y * tileSize + border, m_textures["ICE"]);
					break;
				}
				case 5:
				{
					m_map[x][y] = new Trees(x * tileSize + border, y * tileSize + border, m_textures["TREES"]);
					break;
				}
				case 6:
				{
					m_map[x][y] = new Base(x * tileSize + border, y * tileSize + border, m_textures["BASE"]);
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
}

void TileMap::AddTexture(const std::string& textureName,const sf::Texture& texture)
{
	m_textures[textureName] = texture;
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

				if (m_map[x][y]->GetTankCollision() &&  wallBounds.intersects(nextPositionBounds))
				{
					//Bottom collision
					if (entityBounds.top < wallBounds.top
						&& entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						)
					{
						tank->StopVelocityY();
						tank->SetPosition(entityBounds.left, wallBounds.top - entityBounds.height);
					}

					//Top collision
					else if (entityBounds.top > wallBounds.top
						&& entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						)
					{
						tank->StopVelocityY();
						tank->SetPosition(entityBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					if (entityBounds.left < wallBounds.left
						&& entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						)
					{
						tank->StopVelocityX();
						tank->SetPosition(wallBounds.left - entityBounds.width, entityBounds.top);
					}

					//Left collision
					else if (entityBounds.left > wallBounds.left
						&& entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						)
					{
						tank->StopVelocityX();
						tank->SetPosition(wallBounds.left + wallBounds.width, entityBounds.top);
					}
				}
			}
}

void TileMap::UpdateTank(Tank* tank, const float& dt)
{
	UpdateTankBorderCollision(tank, dt);
	UpdateTankTileCollision(tank, dt);
}

void TileMap::UpdateBulletBorderCollision(Tank* tank, Bullet* bullet, const float& dt)
{
	if (bullet->GetPosition().x < m_upperLeftCorner.x)
	{
		tank->DestroyBullet();
		return;
	}

	if (bullet->GetPosition().x + bullet->GetGlobalBounds().width > m_lowerRightCorner.x)
	{
		tank->DestroyBullet();
		return;
	}

	if (bullet->GetPosition().y < m_upperLeftCorner.y)
	{
		tank->DestroyBullet();
		return;
	}

	if (bullet->GetPosition().y + bullet->GetGlobalBounds().height > m_lowerRightCorner.y)
	{
		tank->DestroyBullet();
		return;
	}
}

void TileMap::UpdateBulletTileCollision(Tank* tank, Bullet* bullet, const float& dt)
{
}

void TileMap::UpdateBullet(Tank* tank, Bullet* bullet, const float& dt)
{
	UpdateBulletBorderCollision(tank, bullet, dt);
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
