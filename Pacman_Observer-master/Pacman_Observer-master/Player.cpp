#include "Player.hh"

/*
** To see all the elements of the class easly
*/
std::ostream& operator<<(std::ostream& os, const Player& player)
{
	static std::string const dir[4] = {"up", "right", "down", "left"};

  	os << player.getName() << " posX = " << player.getPosx() << " - posY = " << player.getPosy() << " - points = " << player.getNbPoints() << " direction = " << dir[player.getDirection()];
  	return os;
}

Player::Player(int posX, int posY, std::string const &image, std::string const &name, int points)
	: ACharacter(ACharacter::RIGHT)
{
	this->posX = posX;
	this->posY = posY;
	this->image = image;
	this->nbPoints = points;
	this->name = name;
	this->lifePoints = 1;
}

Player::~Player()
{
}

