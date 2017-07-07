#include <iostream>
#include <sstream>
#include <cstdio>
#include "unistd.h"
#include <cstdlib>
#include "ACharacter.hh"
#include "Cycle.hh"

static string intToString(int i)// convertir entero string
{
    stringstream ss;
    string s;
    ss << i;
    s = ss.str();

    return s;
}

Cycle::Cycle()
{
	this->_authorizedMoves['t'] = ACharacter::UP;
	this->_authorizedMoves['h'] = ACharacter::RIGHT;
	this->_authorizedMoves['g'] = ACharacter::DOWN;
	this->_authorizedMoves['f'] = ACharacter::LEFT;
}

void	Cycle::initialize(string map, int mapSizeX, int mapSizeY) {
	int			x = 0;
	int			y = 0;
	int			bonusId = 0;
	int			specialBonusId = 0;
	int			monsterId = 0;

	for (int i = 0; i < mapSizeX * mapSizeY; ++i) {
		x = i % mapSizeX;
		y = i / mapSizeX;
		if (map[i] == '.') {
			// Crear bonus
			_bonus.push_back(new Bonus(x, y, "", "Bonus " + intToString(bonusId)));
			map[i] = ' ';
			++bonusId;
		} else if (map[i] == 'o') {
			// Create special bonuses
			_bonus.push_back(new Bonus(x, y, "", "Special bonus " + intToString(specialBonusId), true, 20));
			map[i] = ' ';
			++specialBonusId;
		} else if (map[i] == 'M') {
			// Create monsters
			_monsters.push_back(new Monster(x, y, "", "Monster " + intToString(monsterId)));
			map[i] = ' ';
			++monsterId;
		} else if (map[i] == 'P') {
			// Create player
			_player = new Player(x, y, "", "Pacman");
			map[i] = ' ';
		}
	}
	// Create map
	_map = new Map(map, mapSizeX, mapSizeY);


}

Cycle::~Cycle()
{
    delete _map;
	delete _player;
	for (list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		delete *it;
	}
	for (list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
		delete *it;
	}
}

char Cycle::getUserInput() const
{
	bool found = false;
	char input;

	while (true)
	{
		found = false;
		input = getchar();
		//		system("clear");
		if (input == ' ' || input == 'q')
			return (input);

        if (!found)
			cout << "wrong command " << input << endl;
		for (map<char, ACharacter::Direction>::const_iterator it = this->_authorizedMoves.begin(); it != this->_authorizedMoves.end(); ++it)
		{
			if (it->first == input)
				{
					this->_player->changeDirection(it->second);
					found = true;
					break;
				}
		}

	}
	return ('\0');
}

void	Cycle::checkEatable()
{
	for (list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		if ((*it)->getEatable())
			(*it)->decrease();
	}
}

void	Cycle::cleanAll()
{
	// Check if a bonus is eaten, if so, detach player and (for special bonuses) monsters
	for (list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
		if ((*it)->getLifePoints() <= 0)
		{
			Bonus* tmp = *it;
			//(_player)->detach(*it);
			if ((*it)->isSpecial()) {
				for (list<Monster *>::iterator itMonster = _monsters.begin(); itMonster != _monsters.end(); ++itMonster) {
					//(*itMonster)->detach(*it);
				}
			}
			//(*it)->detach_all();
			it = _bonus.erase(it);
			delete tmp;
			if (it == _bonus.end())
			  break;
		}
	}
	// Check if monsters are eaten, if so, detach map and players
	for (list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		if ((*it)->getLifePoints() <= 0)
		{
			Monster* tmp = *it;
			//(_player)->detach(*it);
			for (list<Bonus *>::iterator itBonus = _bonus.begin(); itBonus != _bonus.end(); ++itBonus) {
				//if ((*itBonus)->isSpecial()) {
					//(*itBonus)->detach(*it);
				//}
			}

			//(*it)->detach_all();
			it = _monsters.erase(it);
			delete tmp;
			if (it == _monsters.end())
			  break;
		}
	}
	// Check if the player is eaten, if so, detach map, monsters and bonuses
	if (_player->getLifePoints() <= 0) {
		//_player->detach(_map);
		for (list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
			//(*it)->detach(_player);
		}
		for (list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
			//(*it)->detach(_player);
		}
		//_player->detach_all();
	}
}

void	Cycle::display() const {
	string	tmpMap(_map->getMap());
	// Add objects to the map
	for (list<Bonus *>::const_iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
		if ((*it)->isSpecial()) {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'o';
		} else {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = '.';
		}
	}
	for (list<Monster *>::const_iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		if ((*it)->getEatable()) {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'W';
		} else {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'M';
		}
	}
	tmpMap[_player->getPosx() + _player->getPosy() * _map->getWidth()] = 'P';
	// Display Map
	for (int y = 0; y < _map->getHeight(); y++) {
		for (int x= 0; x < _map->getWidth(); x++) {
			if (tmpMap[y * _map->getWidth() + x] == 'M') {
				cout << tmpMap[y * _map->getWidth() + x] ;
			} else if (tmpMap[y * _map->getWidth() + x] == 'W') {
				cout << tmpMap[y * _map->getWidth() + x] ;
			}  else if (tmpMap[y * _map->getWidth() + x] == 'P') {
				cout << tmpMap[y * _map->getWidth() + x] ;
			} else {
				cout << tmpMap[y * _map->getWidth() + x];
			}
		}
		cout << endl;
	}
}

void	Cycle::gameLoop()
{
	while (_player->getLifePoints() > 0)
	{
		display();
		if (_bonus.empty())
		{
			cout << "YOU WIN! You have " <<_player->getNbPoints() << " points" << endl;
			return ;
		}
		if (getUserInput() == 'q')
		{
			cout << "GOOD BYE! You have " <<_player->getNbPoints() << " points" << endl;
			return ;
		}
		system("clear");
		_player->move();
		if (_player->getLifePoints() <= 0)
		{
			cout << "YOU'RE DEAD! You have " <<_player->getNbPoints() << " points" << endl;
			return ;
		}
		for (list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
			cerr << "Moving monster " << (*it)->getName() << endl;
			(*it)->move();
			(*it)->decrease();
		}
		cleanAll();
	}
	cout << "YOU'RE DEAD! You have " <<_player->getNbPoints() << " points" << std::endl;
}
