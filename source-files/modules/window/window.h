#include <SFML/Graphics.hpp>
#include "../../settings/window_settings.h"

class Window{
private:
	sf::RenderWindow window;
public:
	Window();
	bool is_closed();
	void display(Game &game);
};