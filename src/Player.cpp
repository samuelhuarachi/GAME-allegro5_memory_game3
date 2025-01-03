#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::setName(const std::string& name)
{
    this->name = name;
}


std::string Player::getName() const
{
    return name;
}
