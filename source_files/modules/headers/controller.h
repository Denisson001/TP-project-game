#pragma once

#include <SFML/Graphics.hpp>

class Controller{
public:
	virtual bool isUpKeyPressed() = 0;
	virtual bool isDownKeyPressed() = 0;
	virtual bool isLeftKeyPressed() = 0;
	virtual bool isRightKeyPressed() = 0;
	virtual ~Controller(){}
};

class KeyboardController : public Controller{
public:
	bool isUpKeyPressed();
	bool isDownKeyPressed();
	bool isLeftKeyPressed();
	bool isRightKeyPressed();
};