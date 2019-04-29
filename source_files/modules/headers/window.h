#pragma once

#include <SFML/Graphics.hpp>

#include <geometry.h>
#include <game.h>

#include <window_settings.h>

class Window{
private:
	sf::RenderWindow window;
	sf::Font font;
	void displayText(std::string text, Vector position);

public:
	Window();
	bool isClosed();
	void display(std::shared_ptr<Game> game);
};
