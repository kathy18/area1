#include "Bonus.hh"

Bonus::Bonus(int posX, int posY, std::string const &image, std::string const &name, bool special, int points)
: GameElement(name, points), _special(special)
{
	this->lifePoints = 1;
	this->posX = posX;
	this->posY = posY;
	this->image = image;
}

Bonus::~Bonus()
{
}
bool	Bonus::isSpecial() const
{
	return (this->_special);
}
