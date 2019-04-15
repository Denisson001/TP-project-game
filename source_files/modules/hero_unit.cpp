#include <units.h>

#include <game_proxy.h>

#include <math_settings.h>

void HeroUnit::checkBorder(){
	auto shape_bounds = shape->getLocalBounds();
	position.x = std::max(position.x, (double)shape_bounds.width / 2);
	position.y = std::max(position.y, (double)shape_bounds.height / 2);
	position.x = std::min(position.x, WINDOW_WIDTH - (double)shape_bounds.width / 2);
	position.y = std::min(position.y, WINDOW_HEIGHT - (double)shape_bounds.height / 2);
}

void HeroUnit::updateMovementModule(double time){
	int dx = 0, dy = 0;
	if (controller->isUpKeyPressed()) dy -= 1;
	if (controller->isDownKeyPressed()) dy += 1;
	if (controller->isLeftKeyPressed()) dx -= 1;
	if (controller->isRightKeyPressed()) dx += 1;

	if (dx != 0 || dy != 0){
		position += Vector(dx, dy).resize(HERO_MOVE_SPEED * time);
		if (!GameProxy::checkHeroUnitPosition())
			position -= Vector(dx, dy).resize(HERO_MOVE_SPEED * time);
	}

	checkBorder();
}

void HeroUnit::updateAttackModule(double time){
	current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

	if (current_attack_cooldown < EPS){
		int dx = 0, dy = 0;
		if (controller->isUpArrowKeyPressed()) dy -= 1;
		if (controller->isDownArrowKeyPressed()) dy += 1;
		if (controller->isLeftArrowKeyPressed()) dx -= 1;
		if (controller->isRightArrowKeyPressed()) dx += 1;

		if (dx != 0 || dy != 0){
			GameProxy::addHeroUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, Vector(dx, dy).resize(BULLET_SPEED), damage, attack_range));
			current_attack_cooldown = max_attack_cooldown;
		}
	}
}


std::shared_ptr<Controller>& HeroUnit::getController(){
	return controller;
}
