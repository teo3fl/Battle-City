#include "stdafx.h"
#include "Spawner.h"

Spawner::Spawner(const uint8_t& numberOfEnemies, const float& interval)
	: m_numberOfEnemies(numberOfEnemies), m_interval(interval)
{
	m_timer = 0.f;
	SetSpawnPoints();
}

Spawner::~Spawner()
{
	while (!m_enemies.empty())
	{
		delete m_enemies.front();
		m_enemies.pop();
	}
}

void Spawner::LoadFromFile(const std::string& fileName)
{
	std::ifstream in(fileName);

	if (in.is_open())
	{

		int number;
		int enemyType;

		while (in >> number >> enemyType)
			for (uint8_t i = 0; i < number; ++i)
				m_enemies.push(CreateTank(enemyType));
	}
	else
	{
		throw "ERROR::SPAWNER::COULD NOT LOAD FROM FILE::FILENAME: " + fileName;
	}

	in.close();
}

void Spawner::AddTexture(const sf::Texture& texture, const std::string& textureName)
{
	m_textures[textureName] = texture;
}

void Spawner::SetSpawnPoints()
{
	m_spawnPoints.resize(3);

	m_spawnPoints[0] = sf::Vector2f(470.f, 85.f);
	m_spawnPoints[1] = sf::Vector2f(855.f, 85.f);
	m_spawnPoints[2] = sf::Vector2f(85.f, 85.f);

	m_lastSpawningPoint = m_spawnPoints.size() - 1;
}

bool Spawner::IsEmpty()
{
	return m_enemies.empty();
}

Tank* Spawner::SpawnNext()
{
	Tank* tank = m_enemies.front();
	m_enemies.pop();

	sf::Vector2f currentSpawningPoint = m_spawnPoints[GetCurrentSpawningPoint()];
	tank->SetPosition(currentSpawningPoint.x, currentSpawningPoint.y);
	tank->SetTexture("DOWN");
	return tank;
}

bool Spawner::Update(const float& dt)
{
	m_timer += dt;
	if (m_timer >= m_interval)
	{
		m_timer = 0;
		return true;
	}
	return false;
}

Tank* Spawner::CreateTank(uint8_t type)
{
	std::string tankType;
	Tank* tank;

	switch (type)
	{
	case 0:
	{
		tank = new ArmorTank();
		tankType = "ARMOR_TANK";
		break;
	}
	case 1:
	{
		tank = new BasicTank();
		tankType = "BASIC_TANK";
		break;
	}
	case 2:
	{
		tank = new FastTank();
		tankType = "FAST_TANK";
		break;
	}
	case 3:
	{
		tank = new PowerTank();
		tankType = "POWER_TANK";
		break;
	}
	default:
		throw "SPAWNER::INVALID_ENEMY_TYPE";
	}

	tank->AddTexture(m_textures[tankType+"_UP"], "UP");
	tank->AddTexture(m_textures[tankType+"_DOWN"], "DOWN");
	tank->AddTexture(m_textures[tankType+"_LEFT"], "LEFT");
	tank->AddTexture(m_textures[tankType+"_RIGHT"], "RIGHT");

	tank->AddTexture(m_textures["BULLET_UP"], "BULLET_UP");
	tank->AddTexture(m_textures["BULLET_DOWN"], "BULLET_DOWN");
	tank->AddTexture(m_textures["BULLET_LEFT"], "BULLET_LEFT");
	tank->AddTexture(m_textures["BULLET_RIGHT"], "BULLET_RIGHT");

	return tank;
}

uint8_t Spawner::GetCurrentSpawningPoint()
{
	++m_lastSpawningPoint;
	m_lastSpawningPoint %= m_spawnPoints.size();

	return m_lastSpawningPoint;
}
