#pragma once

#include <SFML/Graphics.hpp>

class Controller{
public:
	virtual bool isUpKeyPressed() = 0;
	virtual bool isDownKeyPressed() = 0;
	virtual bool isLeftKeyPressed() = 0;
	virtual bool isRightKeyPressed() = 0;
	virtual bool isUpArrowKeyPressed() = 0;
	virtual bool isDownArrowKeyPressed() = 0;
	virtual bool isLeftArrowKeyPressed() = 0;
	virtual bool isRightArrowKeyPressed() = 0;
	virtual ~Controller(){}
};

class KeyboardController : public Controller{
public:
	bool isUpKeyPressed();
	bool isDownKeyPressed();
	bool isLeftKeyPressed();
	bool isRightKeyPressed();
	bool isUpArrowKeyPressed();
	bool isDownArrowKeyPressed();
	bool isLeftArrowKeyPressed();
	bool isRightArrowKeyPressed();
};
