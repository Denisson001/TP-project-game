#include <window.h>

#include <game_proxy.h>
#include <text_helper.h>

#include <technical_settings.h>

Window::Window(): window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close){
    font.loadFromFile(FONT_FILE_PATH);
}

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

void Window::displayText(std::string text, Vector position){
    sf::Text sfml_text(text, font, 30);
    sfml_text.setFillColor(sf::Color::Black);
    sfml_text.setOutlineColor(sf::Color::White);
    sfml_text.setOutlineThickness(3);
    sfml_text.setPosition(position.x, position.y);
    sfml_text.setOrigin(sfml_text.getLocalBounds().width / 2, 0);
    window.draw(sfml_text);
}

void Window::display(){
    std::shared_ptr<Game> game = GameProxy::getGameInstance();
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

    displayText("Health points: " + TextHelper::convertIntToString(game->hero_unit->getHealth()), Vector((double)WINDOW_WIDTH / 2, 0));

    window.display();
}
