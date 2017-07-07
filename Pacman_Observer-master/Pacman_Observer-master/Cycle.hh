#ifndef CYCLE_HH_
# define CYCLE_HH_

#include <vector>
#include <map>


#include <list>
#include <iostream>

#include "termios.h"
#include	"GameElement.hh"
#include "ACharacter.hh"
#include	"Map.hh"
#include	"Player.hh"
#include	"Monster.hh"
#include	"Bonus.hh"


class Cycle
{
public:
	Cycle();
	~Cycle();
	void	display() const;//mostrar
	void	checkEatable();//comida
	void	cleanAll();//limpia
	void	gameLoop();//bucle
	char	getUserInput() const;//teclas direccionales
	void	initialize(string map, int mapSizeX, int mapSizeY);//inicializar

private:
	map<char, ACharacter::Direction>	_authorizedMoves;
	Map *						_map;
	list<Bonus *>			_bonus;//comidas
	Player *					_player;
	list<Monster *>		_monsters;//ubicacion
};

#endif
