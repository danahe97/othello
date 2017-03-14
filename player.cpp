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
	delete board;
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
vector <Move*> Player::makepossible(Side side, Board* board)
{
	vector <Move*> possible;
	for (int i = 0; i < 8; i++)
	{ 
		for (int j = 0; j < 8; j++)
		{
			Move* move = new Move(i, j);
			if (board->checkMove(move, side))
			{
				possible.push_back(move);
			}
			else
				delete move;
		}
	}
	return possible;
}
int findscore(Move* possible)
{
	int score = 0;
	// If corner, add one, if next to corner, subtract one
	if (possible->x == 0)
	{
		if (possible->y == 0 || possible->y == 7)
			score += 1;
		if (possible->y == 1 || possible->y == 6)
			score -= 1;
	}
	if (possible->x == 7)
	{
		if (possible->y == 0 || possible->y == 7)
			score += 1;
		if (possible->y == 1 || possible->y == 6)
			score -= 1;
	}
	if (possible->x == 1)
	{
		if (possible->y == 0 || possible->y == 7)
			score -= 1;
		if (possible->y == 1 || possible->y == 6)
			score -= 1;
	}	
	if (possible->x == 6)
	{
		if (possible->y == 0 || possible->y == 7)
			score -= 1;
		if (possible->y == 1 || possible->y == 6)
			score -= 1;
	}
	return score;
}
Move* bestmove(vector <Move*> possible)
{
	int maxscore = 0;
	int score = 0;
	Move* themove;
	for (unsigned int i = 0; i < possible.size(); i++)
	{
		score = findscore(possible[i]);
		// Continuously find best move		
		if (score > maxscore || i == 0)
		{
			maxscore = score;
			themove = possible[i];
		}
	}
	return themove;
}
Move* Player::minimove(vector<Move*>possible, Board* board)
{
	int lowscore = 0;
	Move* themove;
	for (unsigned int i = 0; i < possible.size(); i++)
	{
		Board *copy = board->copy();
		copy->doMove(possible[i], myside);
		vector <Move*> oppossible = makepossible(otherside, copy);
		if (oppossible.size() == 0)
			return possible[i];
		int score = findscore(bestmove(oppossible));
		if (score < lowscore || i == 0)
		{
			lowscore = score;
			themove = possible[i];
		}
		delete copy;
	}
	return themove;
}
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

	// process opponenet's move
	board->doMove(opponentsMove, otherside);

	if (!board->hasMoves(myside))
		return nullptr;
	//Find possible moves for us
	vector <Move*> possible = makepossible(myside, board);
	Move* mymove;
	mymove = minimove(possible, board);

	// heuristic function
//	if (testingMinimax == false)
//		themove = bestmove(possible);
//	else
//		themove = minimove(possible);
	board->doMove(mymove, myside);
	return mymove;
}