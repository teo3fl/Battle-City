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

void TileMap::UpdateBorderCollision(Entity* entity, const float& dt)
{
	if (entity->GetPosition().x < m_upperLeftCorner.x)
	{
		entity->SetPosition(m_upperLeftCorner.x, entity->GetPosition().y);
		entity->StopVelocityX();
	}
	else if (entity->GetPosition().x + entity->GetGlobalBounds().width > m_lowerRightCorner.x)
	{
		entity->SetPosition(m_lowerRightCorner.x - entity->GetGlobalBounds().width, entity->GetPosition().y);
		entity->StopVelocityX();
	}

	if (entity->GetPosition().y < m_upperLeftCorner.y)
	{
		entity->SetPosition(entity->GetPosition().x, m_upperLeftCorner.y);
		entity->StopVelocityY();
	}
	else if (entity->GetPosition().y + entity->GetGlobalBounds().height > m_lowerRightCorner.y)
	{
		entity->SetPosition(entity->GetPosition().x, m_lowerRightCorner.y - entity->GetGlobalBounds().height);
		entity->StopVelocityY();
	}
}

void TileMap::UpdateTileCollision(Entity* entity, const float& dt)
{
	for (uint16_t y = 0; y < m_width; ++y)
		for (uint16_t x = 0; x < m_height; ++x)
			if (m_map[x][y])
			{
				sf::FloatRect entityBounds = entity->GetGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->GetNextPositionBounds(dt);
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
						entity->StopVelocityY();
						entity->SetPosition(entityBounds.left, wallBounds.top - entityBounds.height);
					}

					//Top collision
					else if (entityBounds.top > wallBounds.top
						&& entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						)
					{
						entity->StopVelocityY();
						entity->SetPosition(entityBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					if (entityBounds.left < wallBounds.left
						&& entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						)
					{
						entity->StopVelocityX();
						entity->SetPosition(wallBounds.left - entityBounds.width, entityBounds.top);
					}

					//Left collision
					else if (entityBounds.left > wallBounds.left
						&& entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						)
					{
						entity->StopVelocityX();
						entity->SetPosition(wallBounds.left + wallBounds.width, entityBounds.top);
					}
				}
			}
}

void TileMap::Update(Entity* entity, const float& dt)
{
	UpdateBorderCollision(entity, dt);
	UpdateTileCollision(entity, dt);
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
