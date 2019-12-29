#pragma once

#include "Hitbox.h"

class Entity{
	public:
		Entity();
		virtual ~Entity();

		void AddTexture(const sf::Texture& texture, const std::string& textureName);

		void SetTexture(const std::string& texture);
		virtual void SetPosition(const float x, const float y);
		void CreateHitbox(sf::Sprite& sprite, float width, float height);

		virtual void Move(const float& dt,const float dir_x, const float dir_y);
		virtual void Update(const float& dt) = 0;
		virtual void Render(sf::RenderTarget* target = nullptr) = 0;
protected:
	sf::Sprite m_sprite;
	Hitbox* m_hitbox;

	float m_movementSpeed;
	std::map<std::string, sf::Texture> m_textures;
};

