#pragma once
class MovementComponent
{
public:
	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	const float& GetMaxVelocity() const;
	const sf::Vector2f& GetVelocity() const;

	void StopVelocity();
	void StopVelocityX();
	void StopVelocityY();

	void Move(const float x, const float y, const float& dt);
	void Update(const float& dt);

private:
	sf::Sprite& m_sprite;

	float m_maxVelocity;
	float m_acceleration;
	float m_deceleration;

	sf::Vector2f m_velocity;
};

