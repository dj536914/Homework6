// Commented by Griffin Jones
// dj536914@ohio.edu

// Brock Ferrell
// CS2401
// November 23, 2015
// Project7

#include "game.h"
#include "othello.h"
using namespace main_savitch_14;
///
/// Creates an Othello game, resets the board into the starting position,
/// and runs the game
///
int main()
{
	Othello theGame;
	theGame.restart();
	theGame.play();
}
