#pragma once

#include <controller.h>

class FakeController : public Controller{
private:
	bool up, down, left, right;
public:
	FakeController(bool up, bool down, bool left, bool right);
	bool isUpKeyPressed();
	bool isDownKeyPressed();
	bool isLeftKeyPressed();
	bool isRightKeyPressed();
};