#ifndef GAMEELEMENT_HH_
# define GAMEELEMENT_HH_

#include <string>
#include <iostream>

#include <map>
#include <list>
#include <iostream>


class GameElement //: public IObserver, public Subject
{
public:
	GameElement(std::string const &name = "Generic", int nbPoints = 0);
	virtual ~GameElement();

	int			getLifePoints() const;
	int			getNbPoints() const;
	int			getPosx() const;
	int			getPosy() const;
	std::string	const &getName() const;
	bool		getEatable() const;

protected:
	int			nbPoints;
	std::string	name;
	bool		eatable;
	int			lifePoints;
	std::string image;
	int 		posX;
	int 		posY;
};

#endif
