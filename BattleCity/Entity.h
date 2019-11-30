#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <stack>
#include <vector>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class Entity{

	private:
	protected:
		sf::RectangleShape shape;
		float movementSpeed;

	public:
		Entity();
		virtual ~Entity();

		virtual void move(const float& dt,const float dir_x, const float dir_y);
		virtual void update(const float& dt);
		virtual void render(sf::RenderTarget& target);




};
