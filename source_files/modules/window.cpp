#include <window.h>

#include <technical_settings.h>

Window::Window(): window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close){}

bool Window::isClosed(){
   sf::Event event;
   if (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
         window.close();
         return 1;
      }
   }
   return 0;
}

std::string Window::convertIntToString(int value){
   if (value == 0)
      return "0";
   bool minus = 0;
   if (value < 0){
      value = -value;
      minus = 1;
   }
   std::string str;
   while(value){
      str += '0' + value % 10;
      value /= 10;
   }
   if (minus)
      str += "-";
   reverse(str.begin(), str.end());
   return str;
}

void Window::displayText(std::string text, Vector position){
   sf::Font font;
   if (!font.loadFromFile(FONT_FILE_PATH)){
      return;
   }
   sf::Text sfml_text(text, font, 30);
   sfml_text.setFillColor(TEXT_COLOR);
   sfml_text.setPosition(position.x, position.y);
   sfml_text.setOrigin(18 * (double)text.size() / 2, 0);
   window.draw(sfml_text);
}

void Window::display(std::shared_ptr<Game> game){
   window.clear();

   for (auto& unit : game->enemy_units){
      unit->getShape()->setPosition(unit->getPosition().x, unit->getPosition().y);
      window.draw(*unit->getShape());
   }

   for (auto& enemy_unit_bullet : game->enemy_units_bullets){
      enemy_unit_bullet->shape->setPosition(enemy_unit_bullet->position.x, enemy_unit_bullet->position.y);
      window.draw(*enemy_unit_bullet->shape);
   }

   for (auto& hero_unit_bullet : game->hero_unit_bullets){
      hero_unit_bullet->shape->setPosition(hero_unit_bullet->position.x, hero_unit_bullet->position.y);
      window.draw(*hero_unit_bullet->shape);
   }

   game->hero_unit->getShape()->setPosition(game->hero_unit->getPosition().x, game->hero_unit->getPosition().y);
   window.draw(*game->hero_unit->getShape());

   displayText("Health points: " + convertIntToString(game->hero_unit->getHealth()), Vector((double)WINDOW_WIDTH / 2, 0));

   window.display();
}
