#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    Board *board;
    Side myside;
    Side otherside;
    ~Player();
   	vector <Move*> makepossible(Side side, Board* board);

	Move *minimove(vector<Move*>possible, Board* board);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
