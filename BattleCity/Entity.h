#pragma once

class Entity{
	public:
		Entity();
		virtual ~Entity();

		void AddTexture(const sf::Texture& texture, const std::string& textureName);

		void SetTexture(const std::string& texture);
		virtual void SetPosition(const float x, const float y);

		virtual void Move(const float& dt,const float dir_x, const float dir_y);
		virtual void Update(const float& dt);
		virtual void Render(sf::RenderTarget* target);
protected:
	sf::Sprite m_sprite;
	float m_movementSpeed;
	std::map<std::string, sf::Texture> m_textures;
};

