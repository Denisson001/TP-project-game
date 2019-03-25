#include <hero_unit.h>

void HeroUnit::checkBorder(){
	auto shape_bounds = shape->getLocalBounds();
	position.x = std::max(position.x, (double)shape_bounds.width / 2);
	position.y = std::max(position.y, (double)shape_bounds.height / 2);
	position.x = std::min(position.x, WINDOW_HEIGHT - (double)shape_bounds.height / 2);
	position.y = std::min(position.y, WINDOW_WIDTH - (double)shape_bounds.width / 2);
}

void HeroUnit::updateMovementModule(double time){
	int dx = 0, dy = 0;
	if (controller->isUpKeyPressed()) dy -= 1;
	if (controller->isDownKeyPressed()) dy += 1;
	if (controller->isLeftKeyPressed()) dx -= 1;
	if (controller->isRightKeyPressed()) dx += 1;

	double value = time * HERO_MOVE_SPEED;
	if (dx != 0 && dy != 0) value /= sqrt(2);

	position.x += dx * value;
	position.y += dy * value;
	checkBorder();
}

void HeroUnit::update(double time){
	updateMovementModule(time);
}