#pragma once

#include <SFML/Graphics.hpp>

#include <geometry.h>
#include <game.h>

#include <window_settings.h>

class Window{
private:
	sf::RenderWindow window;
	std::string convertNumberToString(int value);
	void drawText(std::string str, Vector position);

public:
	Window();
	bool isClosed();
	void display(std::shared_ptr<Game> game);
};
