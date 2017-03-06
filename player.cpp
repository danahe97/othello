#include "player.hpp"
#include <stdlib.h>
#include <time.h>
#include <vector>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    board = new Board();
    myside = side;
    if (myside == WHITE)
    	otherside = BLACK;
    else
    	otherside = WHITE;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

	// process opponenet's move
	board->doMove(opponentsMove, otherside);

	// create vector of all possible moves
	vector <Move*> possible;
	for (int i = 0; i < 8; i++)
	{ 
		for (int j = 0; j < 8; j++)
		{
			Move* move = new Move(i, j);
			if (board->checkMove(move, myside))
			{
				possible.push_back(move);
			}
		}
	}

	if (!board->hasMoves(myside))
	{
		return nullptr;
	}

	// heuristic function
	int maxscore = 0;
	Move* themove;
	for (unsigned int i = 0; i < possible.size(); i++)
	{
		int score = 0;
		if (possible[i]->x == 0)
		{
			if (possible[i]->y == 0 || possible[i]->y == 7)
			{
				score += 1;
			}
			if (possible[i]->y == 1 || possible[i]->y == 6)
			{
				score -= 1;
			}
		}
		if (possible[i]->x == 7)
		{
			if (possible[i]->y == 0 || possible[i]->y == 7)
			{
				score += 1;
			}
			if (possible[i]->y == 1 || possible[i]->y == 6)
			{
				score -= 1;
			}
		}
		if (possible[i]->x == 1)
		{
			if (possible[i]->y == 0 || possible[i]->y == 7)
			{
				score -= 1;
			}
			if (possible[i]->y == 1 || possible[i]->y == 6)
			{
				score -= 1;
			}
		}	
		if (possible[i]->x == 6)
		{
			if (possible[i]->y == 0 || possible[i]->y == 7)
			{
				score -= 1;
			}
			if (possible[i]->y == 1 || possible[i]->y == 6)
			{
				score -= 1;
			}
		}		
		if (score > maxscore || i == 0)
		{
			maxscore = score;
			themove = possible[i];
		}
	}

	board->doMove(themove, myside);
	return themove;
}