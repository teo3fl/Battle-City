#pragma once
#include "Tank.h"
#include "Entity.h"

class Player : public Tank
{
public:
	Player(const std::string& name, float x, float y);

	void IncreaseScore(uint16_t points);
	void IncreaseOffensivePower();
	void GiveExtraLife();
	void ResetOffensivePower();
	void UpdateOffensivePower();

	void Fire() override;

	void SetProtected();
	void SetTexture(const std::string& texture) override;

	const std::string GetName();
	const uint16_t GetLives();
	const uint32_t GetScore();
	bool CanFireSecondaryBullet();
	Bullet* GetSecondaryBullet() const;
	void DestroyBullet(Bullet* bullet) override;

	bool IsProtected();

	void UpdateProtection(const float& dt);
	void Update(const float& dt) override;

private:
	std::string m_name;
	uint16_t m_lives : 9;
	uint32_t m_score : 24;
	uint8_t m_health : 1;
	uint8_t m_offensivePower : 2;

	bool m_enableSecondBullet;
	Bullet* m_secondaryBullet;

	bool m_protected;
	float m_protectedTime;
	float m_maxProtectedTime;
};

