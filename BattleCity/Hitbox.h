#pragma once

class Hitbox
{
public:
	Hitbox(sf::Sprite& sprite, float width, float height);

	~Hitbox();

	bool Intersects(const sf::FloatRect& frect);

	//Accessors
	const sf::Vector2f& GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;
	const sf::FloatRect& GetNextPosition(const sf::Vector2f& velocity);

	void Update();
	void Render(sf::RenderTarget* target = nullptr);

private:
	sf::Sprite& m_sprite;
	sf::RectangleShape m_hitbox;
	sf::FloatRect m_nextPosition;
};

