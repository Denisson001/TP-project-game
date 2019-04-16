#include <units.h>

#include <hero_unit_attack_module.h>
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
      position += Vector(dx, dy).resize(HERO_MOVESPEED * time);
      if (!GameProxy::checkHeroUnitPosition())
         position -= Vector(dx, dy).resize(HERO_MOVESPEED * time);
   }

   checkBorder();
}

void HeroUnit::updateAttackModule(double time){
   attack_module->update(time, this);
}

void HeroUnit::changeAttackModule(){
   current_attack_module_index++;
   if (current_attack_module_index == attack_modules.size())
      current_attack_module_index = 0;
   attack_module = attack_modules[current_attack_module_index];
   attack_module->initialize();
}

std::shared_ptr<Controller>& HeroUnit::getController(){
   return controller;
}
