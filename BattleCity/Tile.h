#pragma once

#include "Hitbox.h"

class Tile
{
public:
	Tile(int x, int y, const sf::Texture& texture);

	void SetTexture(const sf::Texture& texture);
	void SetPosition(int x, int y);
	void CreateHitbox(sf::Sprite& sprite);

	virtual std::string& GetType();
	virtual const sf::FloatRect GetGlobalBounds() const;
	virtual const uint8_t GetHealth();
	virtual const bool Intersects(const sf::FloatRect bounds) const;

	virtual void Update(const float& dt);
	void Render(sf::RenderTarget* target);

	virtual bool GetTankCollision();
	virtual bool GetBulletCollision();

protected:
	std::string m_type;
	bool m_tankCollision:1;
	bool m_bulletCollision:1;
	sf::Sprite m_sprite;
	Hitbox* m_hitbox;

	uint8_t m_width;
	uint8_t m_height;
};
