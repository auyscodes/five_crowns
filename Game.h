//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_GAME_H
#define FIVECROWNS_GAME_H


#include "Player.h"
#include "DataLayer.h"
#include "ISave.cpp"
#include <map>

/*
	Entry point for game.

*/
class Game: public Save{
public:
	Game();
    void start();
	bool saveGame(string filename);
	bool startNew();
	bool loadGame(string filename, DataLayer* dataLayer);
	~Game();
private:
    const int numRounds = 11;
    DataLayer* dataLayer; 
    vector<Player*>* createPlayers(int& startPlayerIndex, int&humanPlayerIndex, int&computerPlayerIndex);
	void displayWinnerAndLoserScore();
	int toss(int humanPlayerIndex, int computerPlayerIndex);
	bool execute();
};


#endif //FIVECROWNS_GAME_H
