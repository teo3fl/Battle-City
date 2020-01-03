#pragma once

#include "ArmorTank.h"
#include "BasicTank.h"
#include "FastTank.h"
#include "PowerTank.h"

class Spawner
{
public:
	Spawner(const uint8_t& numberOfEnemies, const float& interval);
	~Spawner();

	void LoadFromFile(const std::string& fileName);
	void AddTexture(const sf::Texture& texture, const std::string& textureName);

	void SetSpawnPoints();

	bool IsEmpty();
	Tank* SpawnNext();
	bool Update(const float& dt);

private:
	Tank* CreateArmorTank();
	Tank* CreateBasicTank();
	Tank* CreateFastTank();
	Tank* CreatePowerTank();

	uint8_t GetCurrentSpawningPoint();

private:
	std::queue<Tank*> m_enemies;
	uint8_t m_numberOfEnemies;
	std::map<std::string, sf::Texture> m_textures;

	std::vector<sf::Vector2f> m_spawnPoints;
	uint8_t m_lastSpawningPoint;

	float m_interval;
	float m_timer;
};

