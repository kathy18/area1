#include <stdexcept>
#include "Map.hh"

Map::Map(const std::string map, const int sizeX, const int sizeY)
	: _name("Map")
{
	initialize(map, sizeX, sizeY);
}

Map::~Map()
{
}

std::string const &Map::getName() const
{
	return (this->_name);
}
void	Map::initialize(const std::string map, const int sizeX, const int sizeY) {
	_map = std::string(map);
	_sizeX = sizeX;
	_sizeY = sizeY;
}


/*
 *	GETTERS
*/
const std::string	Map::getMap() const {
	return (_map);
}
char				Map::getCell(int x, int y) const {
	return (_map[y * _sizeX + x]);
}
int					Map::getWidth() const {
	return (_sizeX);
}
int					Map::getHeight() const {
	return (_sizeY);
}
