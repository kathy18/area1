#ifndef ACHARACTER_HH_
# define ACHARACTER_HH_

#include "GameElement.hh"

class ACharacter: public GameElement
{
public:
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
    };

    ACharacter(Direction dir = LEFT) : direction(dir){}

	virtual ~ACharacter();


	void		changeDirection(Direction dir);
	void		move();
	Direction	getDirection() const;

protected:
	Direction	direction;
	void		updateNewPosition(Direction dir);

};

#endif
