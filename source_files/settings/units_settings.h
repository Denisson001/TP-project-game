#pragma once

const double CIRCLE_WEAK_ENEMY_SHAPE_SIZE = 35;
const double CIRCLE_STRONG_ENEMY_SHAPE_SIZE = 40;
const double CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE = 45;

const double SQUARE_WEAK_ENEMY_SHAPE_SIZE = 28;
const double SQUARE_STRONG_ENEMY_SHAPE_SIZE = 33;
const double SQUARE_MIGHTY_ENEMY_SHAPE_SIZE = 38;

const sf::Color WEAK_ENEMY_SHAPE_COLOR = sf::Color::Red;
const sf::Color STRONG_ENEMY_SHAPE_COLOR = sf::Color::Green;
const sf::Color MIGHTY_ENEMY_SHAPE_COLOR = sf::Color::Cyan;

const double CIRCLE_WEAK_ENEMY_ATTACK_COOLDOWN = 1000;
const double CIRCLE_STRONG_ENEMY_ATTACK_COOLDOWN = 1250;
const double CIRCLE_MIGHTY_ENEMY_ATTACK_COOLDOWN = 1500;

const double SQUARE_WEAK_ENEMY_ATTACK_COOLDOWN = 1300;
const double SQUARE_STRONG_ENEMY_ATTACK_COOLDOWN = 1550;
const double SQUARE_MIGHTY_ENEMY_ATTACK_COOLDOWN = 1800;

const int CIRCLE_WEAK_ENEMY_DAMAGE = 1;
const int CIRCLE_STRONG_ENEMY_DAMAGE = 2;
const int CIRCLE_MIGHTY_ENEMY_DAMAGE = 3;

const int SQUARE_WEAK_ENEMY_DAMAGE = 2;
const int SQUARE_STRONG_ENEMY_DAMAGE = 3;
const int SQUARE_MIGHTY_ENEMY_DAMAGE = 4;

const double WEAK_ENEMY_ATTACK_RANGE = 480;
const double STRONG_ENEMY_ATTACK_RANGE = 530;
const double MIGHTY_ENEMY_ATTACK_RANGE = 580;

const int WEAK_ENEMY_HEALTH = 5;
const int STRONG_ENEMY_HEALTH = 10;
const int MIGHTY_ENEMY_HEALTH = 15;

const double ENEMY_MOVESPEED = 0.15;

const int WEAK_ENEMY_ADDITIONAL_HEALTH = 1;
const int WEAK_ENEMY_MAX_HEALTH = 10;

const double STRONG_ENEMY_ATTACK_COOLDOWN_REDUCTION_COEFFICIENT = 0.9;
const double STRONG_ENEMY_MIN_ATTACK_COOLDOWN = 250;

const double MIGHTY_ENEMY_ADDITIONAL_ATTACK_RANGE_COEFFICIENT = 1.05;
const double MIGHTY_ENEMY_MAX_ATTACK_RANGE = 1000;

const int SUPER_ATTACK_BULLETS_AMOUNT = 10;
const double SUPER_ATTACK_ADDITIONAL_ATTACK_COOLDOWN_COEFFICIENT = 1.5;

const double CIRCLE_HERO_SHAPE_SIZE = 40;
const double SQUARE_HERO_SHAPE_SIZE = 30;
const sf::Color HERO_SHAPE_COLOR = sf::Color::White;
const double HERO_MOVESPEED = 0.6;
const double CIRCLE_HERO_ATTACK_COOLDOWN = 200;
const double SQUARE_HERO_ATTACK_COOLDOWN = 300;
const double HERO_MINI_ATTACK_COOLDOWN = 60;
const int CIRCLE_HERO_DAMAGE = 2;
const int SQUARE_HERO_DAMAGE = 3;
const double HERO_ATTACK_RANGE = 600;
const int HERO_HEALTH = 100;

const double BULLET_SPEED = 1.1;
const double BULLET_DEFLECTION_ANGLE = 0.25;

constexpr double ENEMY_SHAPE_MAX_SIZE = 1.1 * std::max({
CIRCLE_WEAK_ENEMY_SHAPE_SIZE,
CIRCLE_STRONG_ENEMY_SHAPE_SIZE,
CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE,
SQUARE_WEAK_ENEMY_SHAPE_SIZE,
SQUARE_STRONG_ENEMY_SHAPE_SIZE,
SQUARE_MIGHTY_ENEMY_SHAPE_SIZE});

constexpr double HERO_SHAPE_MAX_SIZE = 1.1 * std::max({
CIRCLE_HERO_SHAPE_SIZE,
SQUARE_HERO_SHAPE_SIZE});
