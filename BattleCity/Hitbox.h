#pragma once

class Hitbox
{
public:
	Hitbox(sf::Sprite& sprite,
		float x, float y,
		float width, float height);

	~Hitbox();

	bool Intersects(const sf::FloatRect& frect);

	//Accessors
	const sf::Vector2f& GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;

	void Update();
	void Render(sf::RenderTarget& target);

private:
	sf::Sprite& m_sprite;
	sf::RectangleShape m_hitbox;
	float m_x;
	float m_y;
};

