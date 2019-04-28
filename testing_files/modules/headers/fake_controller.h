#pragma once

#include <controller.h>

class FakeController : public Controller{
private:
	bool up, down, left, right;
	bool up_arrow, down_arrow, left_arrow, right_arrow;
public:
	FakeController(std::string mask);
	bool isUpKeyPressed();
	bool isDownKeyPressed();
	bool isLeftKeyPressed();
	bool isRightKeyPressed();
	bool isUpArrowKeyPressed();
	bool isDownArrowKeyPressed();
	bool isLeftArrowKeyPressed();
	bool isRightArrowKeyPressed();
};
