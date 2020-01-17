#pragma once

#include "ArmorTank.h"
#include "BasicTank.h"
#include "FastTank.h"
#include "PowerTank.h"

#include "Spawner.h"

class TankSpawner :
	public Spawner<Tank>
{
public:
	TankSpawner(const uint8_t& numberOfEnemies, const float& interval);

	void LoadFromFile(const std::string& fileName);

	bool Update(const float& dt);

private:
	Tank* CreateTank(uint8_t type);
	virtual uint8_t GetCurrentSpawningPoint() override;
	void SetSpawnPoints() override;

private:
	uint8_t m_lastSpawningPoint;

	float m_interval;
	float m_timer;

public:
	std::shared_ptr<AiMap> m_aiMap;
};

