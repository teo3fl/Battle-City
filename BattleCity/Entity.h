#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <stack>
#include <vector>
#include <fstream>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class Entity{
	public:
		Entity();
		virtual ~Entity();

		void SetTexture(sf::Texture& texture);
		virtual void SetPosition(const float x, const float y);

		virtual void move(const float& dt,const float dir_x, const float dir_y);
		virtual void update(const float& dt);
		virtual void render(sf::RenderTarget* target);
protected:
	sf::Sprite m_sprite;
	float m_movementSpeed;
};

