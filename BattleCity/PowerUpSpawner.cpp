#include "stdafx.h"
#include "PowerUpSpawner.h"

PowerUpSpawner::PowerUpSpawner(const uint8_t& numberOfPowerUps) 
	: Spawner(numberOfPowerUps)
{
	SetSpawnPoints();
	GeneratePowerUps();
}

void PowerUpSpawner::GeneratePowerUps()
{
	srand(time(NULL));
	uint8_t powerUpType;
	uint8_t typesOfPowerUp = 6;

	for (uint8_t i = 0; i < m_numberOfObjects; ++i)
	{
		powerUpType = rand() % typesOfPowerUp;

		m_objects.push(CreatePowerUp(powerUpType, GetCurrentSpawningPoint()));
	}
}

PowerUp* PowerUpSpawner::CreatePowerUp(uint8_t powerUpType, uint8_t spawnLocation)
{
	PowerUp* powerUp;
	PowerUpType type = static_cast<PowerUpType>(powerUpType);
	std::string texture;

	switch (powerUpType)
	{
	case 0:
	{
		texture = "GRENADE";
		break;
	}
	case 1:
	{
		texture = "HELMET";
		break;
	}
	case 2:
	{
		texture = "SHOVEL";
		break;
	}
	case 3:
	{
		texture = "STAR";
		break;
	}
	case 4:
	{
		texture = "TANK";
		break;
	}
	case 5:
	{
		texture = "TIMER";
		break;
	}
	default:
		throw "ERROR::POWER_UP_SPAWNER::INVALID_POWER_UP_TYPE";
	}

	powerUp = new PowerUp(m_spawnPoints[spawnLocation], m_textures[texture], type);
}

uint8_t PowerUpSpawner::GetCurrentSpawningPoint()
{
	srand(time(NULL));
	return rand() % m_spawnPoints.size();
}

void PowerUpSpawner::SetSpawnPoints()
{
	std::array<float, 4> coordinates = { 170.f, 350.f, 530.f, 710.f };

	for (uint8_t i = 0; i < coordinates.size(); ++i)
		for (uint8_t j = 0; j < coordinates.size(); ++j)
		{
			m_spawnPoints.push_back(sf::Vector2f(coordinates[i], coordinates[j]));
		}
}
