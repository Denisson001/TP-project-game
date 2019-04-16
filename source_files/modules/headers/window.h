#pragma once

#include <SFML/Graphics.hpp>

#include <geometry.h>
#include <game.h>

#include <window_settings.h>

class Window{
private:
	sf::RenderWindow window;
	void displayText(std::string text, Vector position);
	std::string convertIntToString(int value);

public:
	Window();
	bool isClosed();
	void display(std::shared_ptr<Game> game);
};
