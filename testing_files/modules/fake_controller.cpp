#include <fake_controller.h>

FakeController::FakeController(bool up, bool down, bool left, bool right): up(up), down(down), left(left), right(right){}

bool FakeController::isUpKeyPressed(){
	return up;
}

bool FakeController::isDownKeyPressed(){
	return down;
}

bool FakeController::isLeftKeyPressed(){
	return left;
}

bool FakeController::isRightKeyPressed(){
	return right;
}

bool FakeController::isUpArrowKeyPressed(){}
bool FakeController::isDownArrowKeyPressed(){}
bool FakeController::isLeftArrowKeyPressed(){}
bool FakeController::isRightArrowKeyPressed(){}
