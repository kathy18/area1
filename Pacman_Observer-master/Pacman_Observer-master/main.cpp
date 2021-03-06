#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>      // std::srand
#include "GameElement.hh"
#include "Bonus.hh"
#include "Map.hh"
#include "Player.hh"
#include "Monster.hh"
#include "Cycle.hh"

using namespace std;

int main( )
{
    srand(unsigned(time(0)));

	string mapa = "#############################M...........##...........M##.####.#####.##.#####.####.##o####.#####.##.#####.####o##.####.#####.##.#####.####.##..........................##.####.##.########.##.####.##.####.##.########.##.####.##......##....##....##......#######.##### ## #####.############.##### ## #####.########.....##    P     ##.....####.###.## ######## ##.###.####.###.## #      # ##.###.####o....   #      #   ....o####.###.## #      # ##.###.####.###.## ######## ##.###.####.....##          ##.....########.## ######## ##.############.## ######## ##.#######............##............##.####.#####.##.#####.####.##.####.#####.##.#####.####.##o..##................##..o####.##.##.########.##.##.######.##.##.########.##.##.####......##....##....##......##.##########.##.##########.##.##########.##.##########.##M........................M#############################";
	int			tamX = 28;
	int			tamY = 31;

	Cycle	c;
	c.initialize(mapa, tamX, tamY);
	c.gameLoop();
	return (0);
}
