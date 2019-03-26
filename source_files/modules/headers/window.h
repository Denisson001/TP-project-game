#pragma once

#include <SFML/Graphics.hpp>

#include <game.h>
#include <window_settings.h>

class Window{
private:
	sf::RenderWindow window;
	
public:
	Window();
	bool isClosed();
	void display(const Game &game);
};