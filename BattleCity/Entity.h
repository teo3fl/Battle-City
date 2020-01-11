#pragma once

#include "Hitbox.h"
#include "MovementComponent.h"

class Entity{
	public:
		Entity();
		virtual ~Entity();

		void InitializeVariables();

		void AddTexture(const sf::Texture& texture, const std::string& textureName);
		void SetTexture(const sf::Texture& texture);

		virtual void SetTexture(const std::string& texture);
		virtual void SetPosition(const float x, const float y);
		void CreateHitbox(sf::Sprite& sprite, float width, float height);
		void CreateMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

		virtual const sf::Vector2f& GetPosition() const;
		const sf::FloatRect GetGlobalBounds() const;
		virtual const sf::FloatRect GetNextPositionBounds(const float& dt) const;

		virtual void Move(const float& dt,const float dirX, const float dirY);
		//virtual void StopVelocity();
		virtual void StopVelocityX();
		virtual void StopVelocityY();
		void Push(sf::Vector2f direction, const float& dt);
		void SetDeceleration(uint16_t deceleration);

		virtual void Update(const float& dt);
		virtual void Render(sf::RenderTarget* target = nullptr);
protected:
	sf::Sprite m_sprite;
	Hitbox* m_hitbox;
	MovementComponent* m_movementComponent;
	float m_movementSpeed;
	std::map<std::string, sf::Texture> m_textures;
};

