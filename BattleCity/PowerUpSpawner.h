#pragma once
#include "Spawner.h"
#include "PowerUp.h"
class PowerUpSpawner :
	public Spawner<PowerUp>
{
public:
	PowerUpSpawner(const uint8_t& numberOfPowerUps);

	void GeneratePowerUps();

private:
	PowerUp* CreatePowerUp(uint8_t type);
	virtual uint8_t GetCurrentSpawningPoint() override;
	void SetSpawnPoints() override;
};

