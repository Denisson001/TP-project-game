#include <fake_controller.h>

FakeController::FakeController(std::string mask){
    up = mask[0] == '1';
    down = mask[1] == '1';
    left = mask[2] == '1';
    right = mask[3] == '1';
    up_arrow = mask[4] == '1';
    down_arrow = mask[5] == '1';
    left_arrow = mask[6] == '1';
    right_arrow = mask[7] == '1';
}

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

bool FakeController::isUpArrowKeyPressed(){
    return up_arrow;
}

bool FakeController::isDownArrowKeyPressed(){
    return down_arrow;
}

bool FakeController::isLeftArrowKeyPressed(){
    return left_arrow;
}

bool FakeController::isRightArrowKeyPressed(){
    return right_arrow;
}
