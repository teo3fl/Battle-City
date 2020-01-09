#include "stdafx.h"
#include "PowerUpSpawner.h"

PowerUpSpawner::PowerUpSpawner(const uint8_t& numberOfPowerUps) 
	: Spawner(numberOfPowerUps)
{
	GeneratePowerUps();
}

void PowerUpSpawner::GeneratePowerUps()
{
}

PowerUp* PowerUpSpawner::CreatePowerUp(uint8_t type)
{
	
}

uint8_t PowerUpSpawner::GetCurrentSpawningPoint()
{

}

void PowerUpSpawner::SetSpawnPoints()
{
}
