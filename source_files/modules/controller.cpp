#include <controller.h>

bool KeyboardController::isUpKeyPressed(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

bool KeyboardController::isDownKeyPressed(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}

bool KeyboardController::isLeftKeyPressed(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}

bool KeyboardController::isRightKeyPressed(){
	return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}